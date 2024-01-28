//
// Created by yuant on 1/26/2024.
//

#ifndef PCB_H
#define PCB_H

#include <list>
#include <algorithm>
#include <iostream>
#include "rl.h"
#include "types.h"
#include "utils.h"

enum PCBState{
    Ready = 0,
    Blocked,
    Unallocated
};

class PCB {
public:
    PCB(); // The os process initialization
    void setParent(PID pid);
    PID getParent();
    void setPriority(Priority priority);
    Priority getPriority();
    void ready();
    void block();
    void addChild(PID pid);
    RC deleteChild(PID pid);
    void printPCB();
private:
    PCBState _state;
    PID _parent;
    std::list<PID> _children;
    std::list<RID> _resources;
    Priority _priority;
};


#endif //PCB_H
