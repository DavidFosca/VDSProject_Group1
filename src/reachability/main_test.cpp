//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"

/// Reachability Constructor TESTS:
TEST_F(ReachabilityConstructorTest, constructor_sizeok){

    BDD_ID table_size = reachabilityTest.unique_table.size();
    //reachabilityTest.printUniqueTable();
    EXPECT_EQ(table_size, 20);
}

/// Reachability default_transition_function TESTS:
TEST_F(IsReachable2Bits, default_transition_function){
    bool found;

    stateVector.push_back(0);
    stateVector.push_back(0);
    //reachabilityTest.setInitState(stateVector);

    reachabilityTest.printUniqueTable();

    test1.push_back(0);
    test1.push_back(0);

    test2.push_back(1);
    test2.push_back(1);

    test3.push_back(0);
    test3.push_back(1);

    test4.push_back(1);
    test4.push_back(0);

    found = reachabilityTest.isReachable(test1);
    EXPECT_EQ(found, true);

    found = reachabilityTest.isReachable(test2);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test3);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test4);
    EXPECT_EQ(found, false);
}

/// Reachability setting_transition_function TESTS - Based on the Part3 pdf Example:
TEST_F(IsReachable2Bits, setting_transition_function){
    bool found;
    std::vector<BDD_ID> states_bdd_id;

    stateVector.push_back(0);
    stateVector.push_back(0);
    reachabilityTest.setInitState(stateVector);

    states_bdd_id = reachabilityTest.getStates();

    transitionFunctions.push_back(reachabilityTest.neg(states_bdd_id[0]));
    transitionFunctions.push_back(reachabilityTest.neg(states_bdd_id[1]));

    reachabilityTest.setTransitionFunctions(transitionFunctions);

    test1.push_back(0);
    test1.push_back(0);

    test2.push_back(1);
    test2.push_back(1);

    test3.push_back(0);
    test3.push_back(1);

    test4.push_back(1);
    test4.push_back(0);

    found = reachabilityTest.isReachable(test1);
    EXPECT_EQ(found, true);

    found = reachabilityTest.isReachable(test2);
    EXPECT_EQ(found, true);

    found = reachabilityTest.isReachable(test3);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test4);
    EXPECT_EQ(found, false);

    //reachabilityTest.printUniqueTable();
}

/// Reachability setting_transition_function TESTS - Based on the Part3 pdf Example:
TEST_F(IsReachable3Bits, reachable_3bits){
    bool found;
    std::vector<BDD_ID> states_bdd_id;

    stateVector.push_back(0);
    stateVector.push_back(1);
    stateVector.push_back(0);
    reachabilityTest.setInitState(stateVector);

    states_bdd_id = reachabilityTest.getStates();

    transitionFunctions.push_back(states_bdd_id[0]);
    transitionFunctions.push_back(reachabilityTest.neg(states_bdd_id[1]));
    transitionFunctions.push_back(reachabilityTest.neg(states_bdd_id[2]));

    //reachabilityTest.setTransitionFunctions(transitionFunctions);

    test1.push_back(0);
    test1.push_back(0);
    test1.push_back(0);

    test2.push_back(0);
    test2.push_back(0);
    test2.push_back(1);

    test3.push_back(0);
    test3.push_back(1);
    test3.push_back(0);

    test4.push_back(0);
    test4.push_back(1);
    test4.push_back(1);

    test5.push_back(1);
    test5.push_back(0);
    test5.push_back(0);

    test6.push_back(1);
    test6.push_back(0);
    test6.push_back(1);

    test7.push_back(1);
    test7.push_back(1);
    test7.push_back(0);

    test8.push_back(1);
    test8.push_back(1);
    test8.push_back(1);

    found = reachabilityTest.isReachable(test1);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test2);
    EXPECT_EQ(found, true);

    found = reachabilityTest.isReachable(test3);
    EXPECT_EQ(found, true);

    found = reachabilityTest.isReachable(test4);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test5);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test6);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test7);
    EXPECT_EQ(found, false);

    found = reachabilityTest.isReachable(test8);
    EXPECT_EQ(found, false);

    //reachabilityTest.printUniqueTable();
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}