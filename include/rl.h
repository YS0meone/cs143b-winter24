//
// Created by yuant on 1/26/2024.
//

#ifndef PRM_RL_H
#define PRM_RL_H

#include <list>
#include "types.h"
#include <algorithm>
#include <iostream>
#include "utils.h"
#include <map>


class ReadyList {
public:
    void addToRL(Priority priority, PID pid);
    RC removeFromRL(PID pid, Priority priority);
    PID popFromRL();
    bool hasPID(PID pid, Priority priority);
    PID peekTop();
    void printRL();
    void moveProcessToEnd(PID pid);
private:
    std::list<PID> _highPriorityRL{};
    std::list<PID> _midPriorityRL{};
    std::list<PID> _lowPriorityRL{};
};


#endif //PRM_RL_H
