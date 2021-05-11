#pragma once
#include <vector>
#include "dummy_sum_action.hpp"


class DummySumBnpProblem {
    // Dummy problem where we're to find a pair x, y of
    // numbers between 0 and 100 such that the sum is 100
private:
    int m_x, m_y;
public:
    int x, y;
    DummySumBnpProblem();
    bool is_solved() const;
    friend class DummySumBnpSetAction;
    friend std::vector<DummySumBnpSetAction> dummy_sum_branch(DummySumBnpProblem& ssbp);
    friend std::vector<DummySumBnpSetAction> dummy_sum_propagation(DummySumBnpProblem& ssbp);
};