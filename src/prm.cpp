//
// Created by yuant on 1/26/2024.
//

#include "../include/prm.h"


ProcessResourceManager& ProcessResourceManager::instance() {
    static ProcessResourceManager _prm_ = ProcessResourceManager();
    return _prm_;
}

ProcessResourceManager::ProcessResourceManager()
    : pcbNum(0), rl({}), pcbs{}, rcbs{}{
    // initializer should initialize the PRMs and RL and RCBs and calls activateShell to allow for user interaction
    activateShell();
}

void ProcessResourceManager::activateShell() {
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
    const std::string& function = args[0];
    RC returnCode;
    if (function == "cr") {
        if (args.size() != 2) {
            std::cerr << "cr command used with wrong number of arguments!" << std::endl;
        }
        else {
            auto priority = static_cast<Priority>(std::stoi(args[1]));
            returnCode = create(priority);
        }
    }
    else if (function == "in") {
        if (args.size() != 1) {
            std::cerr << "in command used with wrong number of arguments!" << std::endl;
        }
        else {
            init();
        }
    }
//    else if(function == "de") {
//        if (args.size() != 2) {
//            std::cerr << "de command used with wrong number of arguments!" << std::endl;
//        }
//        else {
//            PID pid = std::stoi(args[1]);
//            returnCode = destroy(pid);
//        }
//    }
//    else if(function == "rq") {
//        if (args.size() != 3) {
//            std::cerr << "rq command used with wrong number o arguments!" << std::endl;
//        }
//        else {
//            RID rid = std::stoi(args[1]);
//            unsigned units = std::stoi(args[2]);
//            returnCode = request(rid, units);
//        }
//    }
//    else if(function == "rl") {
//        if (args.size() != 3) {
//            std::cerr << "rl command used with wrong number o arguments!" << std::endl;
//        }
//        else {
//            RID rid = std::stoi(args[1]);
//            unsigned units = std::stoi(args[2]);
//            returnCode = release(rid, units);
//        }
//    }
//    else if(function == "to") {
//        if (args.size() != 1) {
//            std::cerr << "to command used with wrong number o arguments!" << std::endl;
//        }
//        else {
//            timeout();
//        }
//    }
    else{
        std::cerr << "Unknown command!" << std::endl;\
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
        std::cout << "RCB " << i << ": " << std::endl;
        rcbs[i].printRCB();
    }
    rl = ReadyList();
    pcbs[0].setParent(0);
    pcbs[0].setPriority(Low);
    pcbs[0].ready();
    pcbs[0].printPCB();
    pcbNum = 0;
    rl.addToRL(Low, 0);
    rl.printRL();
}

RC ProcessResourceManager::create(Priority priority) {
    if (pcbNum >= PCB_COUNTS) {
        std::cerr << "Creating more than " << PCB_COUNTS << " PCBS!" << std::endl;
        return -1;
    }
    PID pid = pcbNum;
    pcbs[pid].ready();

    rl.addToRL(priority, pcbNum);
    return 0;
}

ProcessResourceManager::~ProcessResourceManager() = default;

ProcessResourceManager &ProcessResourceManager::operator=(const ProcessResourceManager &other) = default;

ProcessResourceManager::ProcessResourceManager(const ProcessResourceManager &other) =default;
