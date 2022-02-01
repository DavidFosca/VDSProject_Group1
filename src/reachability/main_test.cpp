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

/// Reachability IsReachable TESTS - Based on the Part3 pdf Example:
TEST_F(IsReachable, constructor_sizeok){

    BDD_ID table_size = reachabilityTest.unique_table.size();
    bool found;

    stateVector.push_back(0);
    stateVector.push_back(0);
    reachabilityTest.setInitState(stateVector);

    transitionFunctions.push_back(reachabilityTest.neg(2));
    transitionFunctions.push_back(reachabilityTest.neg(3));

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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}