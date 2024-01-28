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
    void addToWaitList(PID pid);
    RC removeFromWaitList(PID pid);
    PID peekWaitList();
    bool isWaitListEmpty();
    void setInventory(int units);
    void initializeState();
    void printRCB();

private:
    int _inventory;
    int _state;
    std::list<PID> _waitList;
};


#endif //RCB_H
