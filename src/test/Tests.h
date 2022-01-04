//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"
#include "BDD_node.h"

using namespace ClassProject;

class constructorTest : public testing::Test {
public:

    Manager managerTest;

};

class TableSizeTest : public testing::Test {
public:

    Manager managerTest;

};

class UniqueTableTests : public testing::Test {
public:

    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
    }
};

class RecursiveTest1 : public testing::Test {
public:

    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        std::string m="a+b";
        managerTest.addNode(4,1 ,3, 2,m);

    }
};

class CoFactorsTest : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
        std::string label_a_or_b="a+b";
        managerTest.addNode(6,1 ,3, 2,label_a_or_b);
        std::string label_c_and_d="c*d";
        managerTest.addNode(7,5 ,0, 4,label_c_and_d);
    }
};

class IteTest : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");

    }
};

class NegGate : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
    }
};

class ORGate : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
    }
};

class ANDGate : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
    }
};

class NORGate : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
    }
};

class NORGate_Node : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
        std::string label_a_or_b="a+b";
        managerTest.addNode(6,1 ,3, 2,label_a_or_b);
        std::string label_c_and_d="c*d";
        managerTest.addNode(7,5 ,0, 4,label_c_and_d);
    }
};

class NANDGate : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
    }
};

class NANDGate_Node : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
        std::string label_a_or_b="a+b";
        managerTest.addNode(6,1 ,3, 2,label_a_or_b);
        std::string label_c_and_d="c*d";
        managerTest.addNode(7,5 ,0, 4,label_c_and_d);
    }
};

class XORGate : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
    }
};

class XORGate_Node : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
        std::string label_a_or_b="a+b";
        managerTest.addNode(6,1 ,3, 2,label_a_or_b);
        std::string label_c_and_d="c*d";
        managerTest.addNode(7,5 ,0, 4,label_c_and_d);
    }
};

class XNORGate : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
    }
};

class XNORGate_Node : public testing::Test {
public:
    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
        std::string label_a_or_b="a+b";
        managerTest.addNode(6,1 ,3, 2,label_a_or_b);
        std::string label_c_and_d="c*d";
        managerTest.addNode(7,5 ,0, 4,label_c_and_d);
    }
};

#endif