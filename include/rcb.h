//
// Created by yuant on 1/26/2024.
//

#ifndef RCB_H
#define RCB_H

#include "types.h"
#include <list>
#include <algorithm>
#include <iostream>
#include "utils.h"

class RCB {

public:
    RCB();
    void addRequest(PID pid, unsigned int units);
    RC removeFromWaitList(PID pid);
    PID getNextWaitingProcess();
    unsigned getInventory();
    bool isWaitListEmpty();
    void allocateUnits(unsigned int units);
    bool canHandle(unsigned int units);
    void setInventory(unsigned int units);
    void initializeState();
    void printRCB();

private:
    int _inventory;
    int _state;
    std::list<PRP> _waitList;
};


#endif //RCB_H
