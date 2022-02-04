//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"
#include <iostream>

using namespace ClassProject;

Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize){

    std::string state_name, next_state_name;
    BDD_ID bddIDVariable;

    if (stateSize==0) {
        throw std::runtime_error("Runtime_error if stateSize is zero!");
    }

    for (int i=0; i < stateSize; i++) {
        state_name = "s" + std::to_string(i);
        init_state.push_back(0);
        bddIDVariable = inputVar(state_name);
        state_bits.push_back(bddIDVariable);
        trans_func.push_back(bddIDVariable);
    }
    for (int i=0; i < stateSize; i++) {
        next_state_name = "s" + std::to_string(i) + "'";
        bddIDVariable = inputVar(next_state_name);
        next_state_bits.push_back(bddIDVariable);
    }

    trans_relation = computeTransitionRelation();
    c_s_func = computeCharacteristicFunction(init_state);
    reachability_root = symbolicComputationReachableStates();
}

BDD_ID Reachability::inputVar(const std::string &state_name){
    return createVar(state_name);
}

BDD_ID Reachability::computeTransitionRelation(){

    BDD_ID temp1, temp2;
    std::vector<BDD_ID> ops;

    for (int i=0; i < next_state_bits.size(); i++) {
        temp1=xnor2(next_state_bits[i], trans_func[i]);
        ops.push_back(temp1);
    }
    temp1=ops[0];
    for (int j=1; j < ops.size(); j++) {
        temp2 = and2(temp1, ops[j]);
        temp1 = temp2;
    }

    return temp1;
}

BDD_ID Reachability::computeCharacteristicFunction(std::vector<BDD_ID> states){

    BDD_ID temp1, temp2;
    std::vector<BDD_ID> ops;

    for (int i=0; i < state_bits.size(); i++) {
        temp1=xnor2(state_bits[i], states[i]);
        ops.push_back(temp1);
    }
    temp1=ops[0];
    for (int j=1; j < ops.size(); j++) {
        temp2 = and2(temp1, ops[j]);
        temp1 = temp2;
    }

    return temp1;
}

BDD_ID Reachability::symbolicComputationReachableStates(){
    BDD_ID c_r_it_func, c_r_func, temp1, temp2, img_new;

    c_r_it_func = c_s_func;

    do{
        c_r_func = c_r_it_func;

        temp1 = and2(c_r_func, trans_relation);
        for (unsigned long state_bit : state_bits) {
            temp2 = or2(coFactorTrue(temp1, state_bit), coFactorFalse(temp1, state_bit));
            temp1 = temp2;
        }
        img_new = temp1;

        temp1 = 1;
        for (int i = 0; i < state_bits.size(); i++) {
            temp2 = xnor2(state_bits[i], next_state_bits[i]);
            temp1 = and2(temp2, temp1);
        }
        temp1 = and2(temp1, img_new);

        for (int i = 0; i < state_bits.size(); i++) {
            temp2 = or2(coFactorTrue(temp1, next_state_bits[i]), coFactorFalse(temp1, next_state_bits[i]));
            temp1 = temp2;
        }

        c_r_it_func = or2(c_r_func, temp1);

    } while(c_r_func != c_r_it_func);

    return c_r_func;
}

const std::vector<BDD_ID> &Reachability::getStates() const{
    return state_bits;
}

bool Reachability:: isReachable(const std::vector<bool> &stateVector){
    std::vector<BDD_ID> stateVector_BDD;
    BDD_ID temp;

    if ( stateVector.size() != state_bits.size() ){
        throw std::runtime_error("Runtime_error: The size does not match with number of state bits!");
    }

    temp = reachability_root;
    for(int i=0; i<stateVector.size(); i++){
        if( stateVector[i] ) {
            temp = coFactorTrue(temp, state_bits[i]);
        }
        else {
            temp = coFactorFalse(temp, state_bits[i]);
        }
    }

    return temp;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){
    if ( transitionFunctions.size() != state_bits.size() ){
        throw std::runtime_error("Runtime_error: The number of given transition functions does not match the number of state bits!");
    }

    for(int i=0; i<transitionFunctions.size(); i++){
        if (transitionFunctions[i] >= uniqueTableSize()) {
            throw std::runtime_error("Runtime_error: An unknown ID is provided!");
        }
    }

    for(int i=0; i<init_state.size(); i++){
        trans_func[i] = transitionFunctions[i];
    }

    trans_relation = computeTransitionRelation();

    reachability_root = symbolicComputationReachableStates();
}

void Reachability::setInitState(const std::vector<bool> &stateVector){
    if ( stateVector.size() != init_state.size() ) {
        throw std::runtime_error("Runtime_error: size does not match with number of state bits!");
    }
    for(int i=0; i<init_state.size(); i++) {
        if( stateVector[i] ) {
            init_state[i] = 1;
        }
        else {
            init_state[i] = 0;
        }
    }
    c_s_func = computeCharacteristicFunction(init_state);
}