//
// Created by yuant on 1/26/2024.
//

#include "../include/prm.h"

ProcessResourceManager ProcessResourceManager::instance() {
    static ProcessResourceManager _prm_ = ProcessResourceManager();
    return _prm_;
}

ProcessResourceManager::ProcessResourceManager() {
    // initializer should initialize the PRMs and RL and RCBs and calls activateShell to allow for user interaction

}

void ProcessResourceManager::activateShell() {

}

ProcessResourceManager &ProcessResourceManager::operator=(const ProcessResourceManager &other) = default;

ProcessResourceManager::~ProcessResourceManager() = default;

ProcessResourceManager::ProcessResourceManager(const ProcessResourceManager &other) =default;
