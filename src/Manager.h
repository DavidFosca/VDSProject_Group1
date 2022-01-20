// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include "BDD_node.h"
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <string.h>

namespace ClassProject {

    class Manager : public ManagerInterface {

    public:
        std::vector<BDD_node> unique_table;
        std::unordered_map<std::string, BDD_ID> computed_table;
        std::unordered_map<std::string, BDD_ID> reverse_computed_table;
        /**
         *   Manager Constructor Definition.
         *   The unique table object is initialized with two default entries, False and True nodes.
        */
        Manager();

        /**
         *   Create Variable Function Definition.
         *   @param[in] label Name of the label of the new variable.
        */
        BDD_ID createVar(const std::string &label) override;

        /**
         *   UniqueTableSize Definition.
         *   Returns the number of nodes currently existing in the unique table of the Manager class.
        */
        size_t uniqueTableSize() override;

        /**
        *   IsTrue Function.
        *   Returns True if the node is True.
       */
        const BDD_ID &True() override;

        /**
        *   IsFalse Function.
        *   Returns True if the node is False.
       */
        const BDD_ID &False() override;

        /**
        *   Top Variable Function.
        *   Returns the ID of a node's top variable.
        */
        BDD_ID topVar(BDD_ID f) override;

        /**
          *   isVariable Function.
          *   Returns True if the node represents a variable.
         */
        bool isVariable(BDD_ID x) override;

        /**
          *   getTopVarName.
          *   Returns the name of the rop variable for a given node.
         */
        std::string getTopVarName(const BDD_ID &root) override;

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

	    bool isConstant(BDD_ID f) override;

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorTrue(BDD_ID f) override;

        BDD_ID coFactorFalse(BDD_ID f) override;

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;

        BDD_ID neg(BDD_ID a) override;

        BDD_ID or2(BDD_ID a, BDD_ID b) override;

        BDD_ID and2(BDD_ID a, BDD_ID b) override;

        BDD_ID nor2(BDD_ID a, BDD_ID b) override;

        BDD_ID nand2(BDD_ID a, BDD_ID b) override;

        BDD_ID xor2(BDD_ID a, BDD_ID b) override;

        BDD_ID xnor2(BDD_ID a, BDD_ID b) override;

        /**
         *   AddNode.
         *  add a node to our table with a given id, true node, false node,topVariable, label
         *  this function is used during the tests.
        */
        void addNode(BDD_ID p_id, BDD_ID p_high, BDD_ID p_low, BDD_ID p_topvar, std::string &p_label);

        void printUniqueTable( void );

        BDD_ID checkExistance(std::string Node_string);

        bool ite_in_computed_table(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID* id_ptr);

        void update_computed_table(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID r);
    };

};

#endif
