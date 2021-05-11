#include <vector>
#include "dummy_sum_action.hpp"
#include "dummy_sum_problem.hpp"

DummySumBnpProblem::DummySumBnpProblem(): x(0), y(0) {};
bool DummySumBnpProblem::is_solved() const {
    return x + y == 1455;
}