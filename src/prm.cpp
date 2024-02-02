//
// Created by yuant on 1/26/2024.
//

#include "../include/prm.h"


ProcessResourceManager& ProcessResourceManager::instance(const std::string& filePath) {
    static ProcessResourceManager _prm_ = ProcessResourceManager(filePath);
    return _prm_;
}

ProcessResourceManager::ProcessResourceManager(const std::string& filePath)
    : pcbNum(0), rl({}), pcbs{}, rcbs{}, runningPID(-1), filePath(filePath){
    // initializer should initialize the PRMs and RL and RCBs and calls activateShell to allow for user interaction
    activateShell();
}

void ProcessResourceManager::activateShell() {
    if (!filePath.empty()){
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Unable to open file!" <<std::endl;
            return;
        }
        std::string command;
        while (std::getline(file,command)) {
            std::vector<std::string> args = parseCommand(command);
//        printVector(args);
            executeCommand(args);
        }
    }
    else {
        while (true) {
            std::cout << "> ";
            std::string command;
            std::getline(std::cin, command);
            std::vector<std::string> args = parseCommand(command);
            //        printVector(args);
            if (command == "exit") {
                break;
            }
            executeCommand(args);
        }
    }
}

std::vector<std::string> ProcessResourceManager::parseCommand(const std::string &command) {
    std::istringstream iss(command);
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return args;
}

void ProcessResourceManager::executeCommand(const std::vector<std::string> &args) {
    if (args.empty()) {
        return;
    }
    const std::string& function = args[0];
    RC returnCode = 0;
    if (function == "cr") {
        if (args.size() != 2) {
            std::cerr << "cr command used with wrong number of arguments!" << std::endl;
            returnCode = -1;
        }
        else {
            auto priority = static_cast<Priority>(std::stoi(args[1]));
            returnCode = create(priority);
        }
    }
    else if (function == "in") {
        if (args.size() != 1) {
            std::cerr << "in command used with wrong number of arguments!" << std::endl;
            returnCode = -1;
        }
        else {
            init();
        }
    }
    else if(function == "de") {
        if (args.size() != 2) {
            std::cerr << "de command used with wrong number of arguments!" << std::endl;
            returnCode = -1;
        }
        else {
            PID pid = std::stoi(args[1]);
            PCB& pcb = pcbs[runningPID];
            if (pid != runningPID && !pcb.hasChild(pid)) {
                std::cerr << "Destroying the process that is not itself or its child!" << std::endl;
                returnCode = -1;
            }
            else{
                returnCode = destroy(pid);
                scheduler();
            }

        }
    }
    else if(function == "rq") {
        if (args.size() != 3) {
            std::cerr << "rq command used with wrong number of arguments!" << std::endl;
            returnCode = -1;
        }
        else {
            RID rid = std::stoi(args[1]);
            unsigned units = std::stoi(args[2]);
            returnCode = request(rid, units);
        }
    }
    else if(function == "rl") {
        if (args.size() != 3) {
            std::cerr << "rl command used with wrong number of arguments!" << std::endl;
        }
        else {
            RID rid = std::stoi(args[1]);
            unsigned units = std::stoi(args[2]);
            returnCode = release(rid, units);
        }
    }
    else if(function == "to") {
        if (args.size() != 1) {
            std::cerr << "to command used with wrong number of arguments!" << std::endl;
        }
        else {
            timeout();
        }
    }
    else if(function == "pr") {
        if (args.size() != 1) {
            std::cerr << "pr command used with wrong number of arguments!" << std::endl;
        }
        else {
            printStat();
        }
    }
    else{
        std::cerr << "Unknown command!" << std::endl;
    }
    if (returnCode != 0) {
        std::cout << -1 << " ";
    }
    if (filePath.empty()) {
        std::cout << std::endl;
    }
}

void ProcessResourceManager::init() {
    // erase all content of PCB
    for (auto & pcb : pcbs) {
        pcb = PCB();
    }
    // initialize RCBS with corresponding inventory and state
    for (int i = 0; i < RCB_COUNTS; ++i) {
        rcbs[i] = RCB();
        if (i == 0 || i == 1) {
            rcbs[i].setInventory(1);
            rcbs[i].initializeState();
        }
        else {
            rcbs[i].setInventory(i);
            rcbs[i].initializeState();
        }
//        std::cout << "RCB " << i << ": " << std::endl;
//        rcbs[i].printRCB();
    }
    rl = ReadyList();
    pcbs[0].setParent(0);
    pcbs[0].setPriority(Low);
    pcbs[0].ready();
//    pcbs[0].printPCB();
    pcbNum = 1;
    rl.addToRL(Low, 0);
    std::cout << std::endl;
    scheduler();
//    rl.printRL();
}

RC ProcessResourceManager::create(Priority priority) {
    if (pcbNum >= PCB_COUNTS) {
        std::cerr << "Creating more than " << PCB_COUNTS << " PCBS!" << std::endl;
        return -1;
    }
    auto pid = static_cast<PID>(getUnallocatedPCB());
    if (pid == -1) {
        std::cerr << "Error when creating a process: there is no available PCB!" << std::endl;
        return -1;
    }
    pcbs[pid].ready();
    PID parent = runningPID;
    pcbs[parent].addChild(pid);
    pcbs[pid].setParent(parent);
    pcbs[pid].setPriority(priority);
    rl.addToRL(priority, pid);
    pcbNum += 1;
//    std::cout << "process " << pid << " created" << std::endl;
//    pcbs[pid].printPCB();
//    rl.printRL();
    scheduler();
    return 0;
}

PID ProcessResourceManager::getUnallocatedPCB() {
    for (PID i = 0; i < PCB_COUNTS; ++i) {
        if (!pcbs[i].isAllocated()) {
            return i;
        }
    }
    return -1; //
}

void ProcessResourceManager::scheduler() {
    PID candidate = rl.peekTop();
    runningPID = candidate; // even if it returns -1
    std::cout << runningPID << " ";
//    std::cout << "process " << runningPID << " running" << std::endl;
}

RC ProcessResourceManager::request(RID rid, unsigned int units) {
    if (rid < 0 || rid >= 4) {
        std::cerr << "Requested rid does not exist!" << std::endl;
        return -1;
    }
    RCB& rcb = rcbs[rid];
    PCB& pcb = pcbs[runningPID];
    unsigned maxUnits = rcb.getInventory();
    if (maxUnits < units + pcb.getUnits(rid)) {
        std::cerr << "Requested more than resource can possible have!" << std::endl;
        return -1;
    }
    // check if the request is more than
    if (rcb.canHandle(units)) {
        rcb.allocateUnits(units);
        pcb.insertResource(rid, units);
//        std::cout << units << " of resource " << rid << " allocated" << std::endl;
    }
    else {
        pcb.block();
        rl.removeFromRL(runningPID, pcb.getPriority());
//        rl.printRL();
        rcb.addRequest(runningPID, units);
    }
    scheduler();
//    pcb = pcbs[runningPID];
//    pcb.printPCB();
//    rcb.printRCB();
    return 0;
}

RC ProcessResourceManager::release(PID pid, RID rid, unsigned int units) {
    PCB& pcb = pcbs[pid];
    RCB& rcb = rcbs[rid];
    if (!pcb.hasResource(rid, units)) {
        std::cerr << "Error: releasing an resource that does not belong to the process!" << std::endl;
        return -1;
    }
    pcb.removeResource(rid, units);
    rcb.returnUnits(units);
//    pcb.printPCB();
//    rcb.printRCB();
//    rl.printRL();
    while (!rcb.isWaitListEmpty() && rcb.canHandle(1)) {
        PRP prp = rcb.getNextRequest();
        PID waitingPID = prp.first;
        unsigned requestedUnits = prp.second;
        PCB& waitingPCB = pcbs[waitingPID];
        if (rcb.canHandle(requestedUnits)) {
            // make sure the request is valid
            if (waitingPCB.isAllocated()) {
                rcb.allocateUnits(requestedUnits);
                waitingPCB.insertResource(rid, requestedUnits);
                waitingPCB.ready();
                rcb.removeFromWaitList(waitingPID);
                rl.addToRL(waitingPCB.getPriority(), waitingPID);
//                rl.printRL();
            }
            else {
                rcb.removeFromWaitList(waitingPID);
            }
        }
        else {
            break;
        }
    }
//    rcb.printRCB();
    return 0;
}

RC ProcessResourceManager::destroy(PID pid) {
    PCB& pcb = pcbs[pid];
    PCB& parent = pcbs[pcb.getParent()];
    auto childrenCopy = pcb.children;
    for (auto& childPID: childrenCopy) {
        destroy(childPID);
    }
    parent.deleteChild(pid);
    Priority priority = pcb.getPriority();
//    rl.printRL();
    if (rl.hasPID(pid, priority)) {
        rl.removeFromRL(pid, priority);
    }
    RID rid;
    unsigned units;
    auto resourceCopy = pcb.resources;
    for (auto& pair: resourceCopy) {
//        pcb.printPCB();
        rid = pair.first;
        units = pair.second;
        pcb.unallocate();
        release(pid, rid, units);
    }
    // we should destroy all invalid requests from in all RCBs
    for (auto & rcb : rcbs) {
        auto waitListCopy = rcb.waitList;
        for (const auto& pair: waitListCopy) {
            PID requestPid = pair.first;
            if (!pcbs[requestPid].isAllocated()) {
                rcb.removeFromWaitList(requestPid);
            }
        }
    }
    pcbs[pid] = PCB();
    pcbNum -= 1;
    return 0;
}

void ProcessResourceManager::timeout() {
    rl.moveProcessToEnd(runningPID);
    scheduler();
}

void ProcessResourceManager::printStat() {
    for (unsigned i = 0; i < PCB_COUNTS; ++i) {
        std::cout << "PCB " << i << ":" << std::endl;
        pcbs[i].printPCB();
    }
    for (unsigned i = 0; i < RCB_COUNTS; ++i) {
        std::cout << "RCB " << i << ":" << std::endl;
        rcbs[i].printRCB();
    }
    std::cout << "Ready List: " << std::endl;
    rl.printRL();

}

RC ProcessResourceManager::release(RID rid, unsigned int units) {
    PCB& pcb = pcbs[runningPID];
    RCB& rcb = rcbs[rid];
    if (!pcb.hasResource(rid, units)) {
        std::cerr << "Error: releasing an resource that does not belong to the process!" << std::endl;
        return -1;
    }
    pcb.removeResource(rid, units);
    rcb.returnUnits(units);
//    pcb.printPCB();
//    rcb.printRCB();
//    rl.printRL();
    while (!rcb.isWaitListEmpty() && rcb.canHandle(1)) {
        PRP prp = rcb.getNextRequest();
        PID waitingPID = prp.first;
        unsigned requestedUnits = prp.second;
        PCB& waitingPCB = pcbs[waitingPID];
        if (rcb.canHandle(requestedUnits)) {
            // make sure the request is valid
            if (waitingPCB.isAllocated()) {
                rcb.allocateUnits(requestedUnits);
                waitingPCB.insertResource(rid, requestedUnits);
                waitingPCB.ready();
                rcb.removeFromWaitList(waitingPID);
                rl.addToRL(waitingPCB.getPriority(), waitingPID);
//                rl.printRL();
            }
            else {
                rcb.removeFromWaitList(waitingPID);
            }
        }
        else {
            break;
        }
    }
    scheduler();
//    rcb.printRCB();
    return 0;
}

ProcessResourceManager::~ProcessResourceManager() = default;

ProcessResourceManager &ProcessResourceManager::operator=(const ProcessResourceManager &other) = default;

ProcessResourceManager::ProcessResourceManager(const ProcessResourceManager &other) =default;
