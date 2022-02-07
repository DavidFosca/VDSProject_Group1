//
// Created by tobias on 29.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

class ReachabilityConstructorTest : public testing::Test {
public:

    Reachability reachabilityTest = Reachability( 2 );

};

class IsReachable2Bits : public testing::Test {
public:

    Reachability reachabilityTest = Reachability( 2 );

    std::vector<bool> stateVector;
    std::vector<BDD_ID> transitionFunctions;
    std::vector<bool> test1;
    std::vector<bool> test2;
    std::vector<bool> test3;
    std::vector<bool> test4;
};

class IsReachable3Bits : public testing::Test {
public:

    Reachability reachabilityTest = Reachability( 3 );

    std::vector<bool> stateVector;
    std::vector<BDD_ID> transitionFunctions;
    std::vector<bool> test1;
    std::vector<bool> test2;
    std::vector<bool> test3;
    std::vector<bool> test4;
    std::vector<bool> test5;
    std::vector<bool> test6;
    std::vector<bool> test7;
    std::vector<bool> test8;
};

class ReachabilityExceptions : public testing::Test {
public:
    Reachability reachabilityTest = Reachability( 4 );

    std::vector<bool> stateVector;
    std::vector<BDD_ID> transitionFunctions;
    std::vector<bool> test1;
};

#endif
