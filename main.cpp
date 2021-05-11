#include <iostream>
#include <vector>
#include <random>
#include "bnp.hpp"
#include "dummy_sum_problem.hpp"
#include "dummy_sum_action.hpp"

std::vector<DummySumBnpSetAction> dummy_sum_propagation(DummySumBnpProblem& ssbp) {
    std::vector<DummySumBnpSetAction> v;
    if(!ssbp.is_solved() && ssbp.x > 80) {
        DummySumBnpSetAction action = DummySumBnpSetAction('y', 100 - ssbp.x);
        v.push_back(action);
        action.apply(ssbp);
    }
    return v;
}

bool dummy_sum_prune(const DummySumBnpProblem& ssbp) {
    return ssbp.x < 40;
}

std::vector<DummySumBnpSetAction> dummy_sum_branch(DummySumBnpProblem& ssbp) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::vector<DummySumBnpSetAction> actions;
    if(ssbp.x + ssbp.y > 1000) return actions;
    for(int x = 0; x < 1000; ++x) {
        DummySumBnpSetAction a = DummySumBnpSetAction('x', x);
        actions.push_back(a);
    }
    for(int y = 0; y < 1000; ++y) {
        DummySumBnpSetAction a = DummySumBnpSetAction('y', y);
        actions.push_back(a);
    }
    std::shuffle(actions.begin(), actions.end(), gen);
    return actions;
}

int main(int argc, char **argv) {
    DummySumBnpProblem problem = DummySumBnpProblem();
    using DummyBnp = Bnp<DummySumBnpProblem, DummySumBnpSetAction>;
    DummyBnp bnp = DummyBnp(problem, dummy_sum_branch);
    bnp.set_propagation_callback(dummy_sum_propagation);
    bnp.set_prune_callback(dummy_sum_prune);
    bnp.solve();
    std::cout << "Solution: (" << problem.x << ", " << problem.y << ")" <<  std::endl;
    return 0;
}