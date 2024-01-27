#include <iostream>
#include "pcb.h"
// There should be a PCB class which can acquire resource, release resource
// destroyProcess, createProcess
// RCB class should have getter and setter function for _state and waitlist

int main(){
    PCB pcb = PCB();
    std::cout << pcb.getPriority() << std::endl;
    pcb.setPriority(High);
    std::cout << pcb.getPriority() << std::endl;
    pcb.addChild(1);
    pcb.addChild(2);
    pcb.addChild(3);
    pcb.printChildren();
    std::cout << "PCB's parent is: " << pcb.getParent() << std::endl;
    pcb.setParent(4);
    std::cout << "PCB's parent after modification is : " << pcb.getParent() << std::endl;
    return 0;
}