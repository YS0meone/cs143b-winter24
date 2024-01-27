//
// Created by yuant on 1/26/2024.
//

// PRM should have
#ifndef PRM_H
#define PRM_H

#include "pcb.h"
#include "rcb.h"
#include "rl.h"
#include <iostream>

// There should be only one instance of a PRM in the system
// The only way to interact with the PRM should be done thru the shell thus all functions should be made private
class ProcessResourceManager {
public:
    static ProcessResourceManager instance();
protected:
    ProcessResourceManager();
    ProcessResourceManager(const ProcessResourceManager& other);
    ~ProcessResourceManager();
    ProcessResourceManager& operator=(const ProcessResourceManager& other);
private:
    void activateShell();
};


#endif //PRM_H
