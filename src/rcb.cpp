//
// Created by yuant on 1/26/2024.
//

#include "../include/rcb.h"

RCB::RCB()
    : _inventory(0), _state(0), waitList({}){
}

void RCB::addRequest(PID pid, unsigned int units) {
    PRP newRequest(pid, units);
    waitList.push_back(newRequest);
}

RC RCB::removeFromWaitList(PID pid) {
    for (auto it = waitList.begin(); it != waitList.end(); ++it) {
        if (it->first == pid) {
            waitList.erase(it);
            return 0;
        }
    }
    std::cerr << "Process not found in the wait list!" << std::endl;
    return -1;
}


PRP RCB::getNextRequest() {
    return waitList.front();
}

bool RCB::isWaitListEmpty() {
    return waitList.empty();
}

void RCB::setInventory(unsigned int units) {
    _inventory = units;
}

void RCB::initializeState() {
    _state = _inventory;
}

void RCB::printRCB() {
    std::cout << "Inventory: " << _inventory  << std::endl;
    std::cout << "Units left: " << _state << std::endl;
    std::cout << "Wait List PIDs: ";
    printPairList(waitList);
    std::cout << std::endl;
}

bool RCB::canHandle(unsigned int units) const {
    return _state >= units;
}

void RCB::allocateUnits(unsigned int units) {
    _state -= units;
}


unsigned RCB::getInventory() const {
    return _inventory;
}

void RCB::returnUnits(unsigned int units) {
    _state += units;
}
