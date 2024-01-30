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
    std::list<PRP> waitList;
    void addRequest(PID pid, unsigned int units);
    RC removeFromWaitList(PID pid);
    PRP getNextRequest();
    unsigned getInventory() const;
    bool isWaitListEmpty();
    void allocateUnits(unsigned int units);
    void returnUnits(unsigned int units);
    bool canHandle(unsigned int units) const;
    void setInventory(unsigned int units);
    void initializeState();
    void printRCB();

private:
    int _inventory;
    int _state;

};


#endif //RCB_H
