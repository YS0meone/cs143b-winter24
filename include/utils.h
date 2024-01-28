//
// Created by yuant on 1/27/2024.
//

#ifndef PRM_UTILS_H
#define PRM_UTILS_H
#include <list>
#include <iostream>
#include <vector>


template<typename T>
void printList(const std::list<T>& list) {
    for (const auto& ele: list) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

template<typename T1, typename T2>
void printPairList(const std::list<std::pair<T1, T2>> list) {
    for (const auto& pair: list) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << " ";
    }
    std::cout << std::endl;
}

template<class T>
void printVector(const std::vector<T> &vec) {
    for (const T& ele: vec) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

#endif //PRM_UTILS_H
