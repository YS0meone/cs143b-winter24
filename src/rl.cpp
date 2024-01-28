//
// Created by yuant on 1/26/2024.
//

#include "rl.h"

void ReadyList::addToRL(Priority priority, PID pid) {
    switch (priority) {
        case High:
            _highPriorityRL.push_back(pid);
            break;
        case Mid:
            _midPriorityRL.push_back(pid);
            break;
        case Low:
            _lowPriorityRL.push_back(pid);
            break;
    }
}

PID ReadyList::popFromRL() {
    PID ret;
    if (!_highPriorityRL.empty()) {
        ret = _highPriorityRL.front();
        _highPriorityRL.pop_front();
    }
    else if(!_midPriorityRL.empty()) {
        ret = _midPriorityRL.front();
        _midPriorityRL.pop_front();
    }
    else if(!_lowPriorityRL.empty()) {
        ret = _lowPriorityRL.front();
        _lowPriorityRL.pop_front();
    }
    else {
        ret = -1;
    }
    return ret;
}

RC ReadyList::removeFromRL(PID pid, Priority priority) {
    std::list<PID>::iterator it;
    switch (priority) {
        case High:
            it = std::find(_highPriorityRL.begin(), _highPriorityRL.end(), pid);
            if (it != _highPriorityRL.end()) {
                _highPriorityRL.erase(it);
                return 0;
            }
            else {
                std::cerr << "Process is not present in the corresponding ready list!" << std::endl;
                return -1;
            }
            break;
        case Mid:
            it = std::find(_midPriorityRL.begin(), _midPriorityRL.end(), pid);
            if (it != _midPriorityRL.end()) {
                _midPriorityRL.erase(it);
                return 0;
            }
            else {
                std::cerr << "Process is not present in the corresponding ready list!" << std::endl;
                return -1;
            }
            break;
        case Low:
            it = std::find(_lowPriorityRL.begin(), _lowPriorityRL.end(), pid);
            if (it != _lowPriorityRL.end()) {
                _lowPriorityRL.erase(it);
                return 0;
            }
            else {
                std::cerr << "Process is not present in the corresponding ready list!" << std::endl;
                return -1;
            }
            break;
    }
    return 0;
}

void ReadyList::printRL() {
    std::cout << "High Priority RL: ";
    printList(_highPriorityRL);
    std::cout << "Mid Priority RL: ";
    printList(_midPriorityRL);
    std::cout << "Low Priority RL: ";
    printList(_lowPriorityRL);
}

PID ReadyList::peekTop() {
    if (!_highPriorityRL.empty()) {
        return _highPriorityRL.front();
    }
    else if (!_midPriorityRL.empty()) {
        return _midPriorityRL.front();
    }
    else {
        return _lowPriorityRL.front();
    }
}

void ReadyList::moveProcessToEnd(PID pid) {
    if (pid != _highPriorityRL.front() && pid != _midPriorityRL.front() && pid != _lowPriorityRL.front()) {
        std::cerr << "Timeour error, the process is not at the front!" << std::endl;
    }
    if (pid == _highPriorityRL.front()) {
        _highPriorityRL.pop_front();
        _highPriorityRL.push_back(pid);
    }
    else if (pid == _midPriorityRL.front()) {
        _midPriorityRL.pop_front();
        _midPriorityRL.push_back(pid);
    }
    else {
        _lowPriorityRL.pop_front();
        _lowPriorityRL.push_back(pid);
    }
}

