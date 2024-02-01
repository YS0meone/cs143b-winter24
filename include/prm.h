//
// Created by yuant on 1/26/2024.
//

// PRM should have
#ifndef PRM_H
#define PRM_H

#include "pcb.h"
#include "rcb.h"
#include "rl.h"
#include "types.h"
#include <iostream>
#include <vector>
#include <sstream>

#define PCB_COUNTS 16
#define RCB_COUNTS 4
// There should be only one instance of a PRM in the system
// The only way to interact with the PRM should be done thru the shell thus all functions should be made private
class ProcessResourceManager {
public:
    static ProcessResourceManager& instance(bool isFileInput=false);
protected:
    explicit ProcessResourceManager(bool isFileInput=false);
    ~ProcessResourceManager();
    ProcessResourceManager(const ProcessResourceManager& other);
    ProcessResourceManager& operator=(const ProcessResourceManager& other);
private:
    unsigned pcbNum;
    PID runningPID;
    PCB pcbs[PCB_COUNTS];
    RCB rcbs[RCB_COUNTS];
    ReadyList rl;
    bool isFileInput;

    void activateShell();
    std::vector<std::string> parseCommand(const std::string& command);
    void scheduler();
    void init();
    int getUnallocatedPCB();
    RC create(Priority priority);
    RC destroy(PID pid);
    RC request(RID rid, unsigned units);
    RC release(RID rid, unsigned int units);
    RC release(PID pid, RID rid, unsigned int units);
    void timeout();
    void executeCommand(const std::vector<std::string>& args);
    void printStat();

};



#endif //PRM_H
