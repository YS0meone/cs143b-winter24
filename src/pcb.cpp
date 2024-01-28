//
// Created by yuant on 1/26/2024.
//

#include "../include/pcb.h"

PCB::PCB()
    : _state(Unallocated), _parent(-1), _priority(Low), children({}), resources({}){
}

void PCB::setParent(PID pid) {
    _parent = pid;
}

void PCB::setPriority(Priority priority) {
    _priority = priority;
}

void PCB::block() {
    _state = Blocked;
}

Priority PCB::getPriority() {
    return _priority;
}

PID PCB::getParent() {
    return _parent;
}

void PCB::ready() {
    _state = Ready;
}

void PCB::addChild(PID pid) {
    children.push_back(pid);
}

RC PCB::deleteChild(PID pid) {
    auto it = std::find(children.begin(), children.end(), pid);
    if (it != children.end()) {
        children.erase(it);
    }
    else {
        return -1; // return -1 for error code if the child does not exist
    }
    return 0;
}

void PCB::printPCB() {
    std::cout << "State: " << _state << std::endl;
    std::cout << "Priority: " << _priority << std::endl;
    std::cout << "Parent PID: " << _parent << std::endl;
    std::cout << "Children PIDs: ";
    printList(children);
    std::cout << "Resources RIDs: ";
    printPairList(resources);
    std::cout << std::endl;
}

bool PCB::isAllocated() {
    return _state != Unallocated;
}

void PCB::insertResource(RID rid, unsigned int units) {
    RUP rup(rid, units);
    resources.push_back(rup);
}

void PCB::removeResource(RID rid) {
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->first == rid) {
            resources.erase(it);
            return;
        }
    }
    std::cerr << "Error: removing a resource that does not belong to the process!" << std::endl;
}

bool PCB::hasResource(RID rid) {
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->first == rid) {
            return true;
        }
    }
    return false;
}







