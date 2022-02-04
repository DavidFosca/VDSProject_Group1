//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"

namespace ClassProject {

    class Reachability : public ReachabilityInterface {

    //private:
    public:
        //Manager states_OBDD;
        std::vector<BDD_ID> init_state;
        std::vector<BDD_ID> state_bits;
        std::vector<BDD_ID> next_state_bits;
        std::vector<BDD_ID> trans_func;
        BDD_ID c_s_func;
        BDD_ID trans_relation;
        BDD_ID reachability_root;

        BDD_ID computeTransitionRelation();

        BDD_ID computeCharacteristicFunction(std::vector<BDD_ID> states);

        BDD_ID inputVar(const std::string &state_name);

        BDD_ID symbolicComputationReachableStates();

    public:

        Reachability(unsigned int stateSize);

        const std::vector<BDD_ID> &getStates() const override;

        bool isReachable(const std::vector<bool> &stateVector) override;

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) override;

        void setInitState(const std::vector<bool> &stateVector) override;

    };

}
#endif
