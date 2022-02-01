//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

using namespace ClassProject;

explicit Reachability::ReachabilityInterface(unsigned int stateSize){

    auto state_name;
    BDD_ID trans;

    if (stateSize==0) {
        throw std::runtime_error("Runtime_error if stateSize is zero!");
    }
    else
    {
        for (i=0; i < stateSize; i++) {
            state_name = "s" + std::to_string(i);
            init_state.push_back(0);
            trans = states_OBDD.createVar(state_name);
            trans_func.push_back(trans);
        }
    }
}

const std::vector<BDD_ID> &Reachability::getStates() {

    return states_OBDD

}

bool Reachability:: isReachable(const std::vector<bool> &stateVector){

}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){

}

void Reachability::setInitState(const std::vector<bool> &stateVector){

}