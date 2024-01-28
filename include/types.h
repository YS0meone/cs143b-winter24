//
// Created by yuant on 1/26/2024.
//

#ifndef TYPES_H
#define TYPES_H

#include <utility>
typedef int PID;
typedef int RID;
typedef int RC; // return code
typedef std::pair<PID, unsigned> PRP;
typedef std::pair<RID, unsigned> RUP;

enum Priority{
    Low = 0,
    Mid,
    High
};

#endif //TYPES_H
