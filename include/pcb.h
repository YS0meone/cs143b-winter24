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
    std::list<PID> children;
    std::list<RUP> resources;
    void setParent(PID pid);
    PID getParent();
    void setPriority(Priority priority);
    Priority getPriority();
    void ready();
    void block();
    bool isAllocated();
    void addChild(PID pid);
    RC deleteChild(PID pid);
    void insertResource(RID rid, unsigned units);
    void removeResource(RID rid, unsigned units);
    void printPCB() const;
    bool hasResource(RID rid, unsigned units);
    void unallocate();
    unsigned getUnits(RID rid);
private:
    PCBState _state;
    PID _parent;
    Priority _priority;
};


#endif //PCB_H
