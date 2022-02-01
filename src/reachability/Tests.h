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

class IsReachable : public testing::Test {
public:

    Reachability reachabilityTest = Reachability( 2 );

    std::vector<bool> stateVector;
    std::vector<BDD_ID> transitionFunctions;
    std::vector<bool> test1;
    std::vector<bool> test2;
    std::vector<bool> test3;
    std::vector<bool> test4;
};

#endif
