//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"

namespace ClassProject {

    class Reachability : public ReachabilityInterface {

    public:

        Manager states_OBDD;
        vector<BDD_ID> init_state;
        vector<BDD_ID> trans_func;

        Reachability();

        explicit ReachabilityInterface(unsigned int stateSize) override;

        virtual const std::vector<BDD_ID> &getStates() override;

        virtual bool isReachable(const std::vector<bool> &stateVector) override;

        virtual void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) override;

        virtual void setInitState(const std::vector<bool> &stateVector) override;

    };

}
#endif
