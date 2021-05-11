#pragma once
#include <iostream>
#include <list>
#include <chrono>

// Branch and propagate framework.

// Defines a set of abstractions for a backtracking algorithm
// supporting
// - branching callbacks (which decision to make in each problem state)
// - constraint propagation callbacks (given a partial solution it extends it as defined by user)
// - history tracking structures to support undoing-redoing history (if 
//   the branch didn't lead to any solution, algorithm needs to undo all the propagations)

template <typename BnpProblem,
          typename Action>
class Bnp{
public:
    Bnp(const Bnp&) = delete;
    Bnp(BnpProblem&, std::vector<Action> (*branch_callback_fn)(BnpProblem&));
    void set_propagation_callback(std::vector<Action> (*propagate_callback_fn)(BnpProblem&));
    void set_prune_callback(bool (*prune_callback_fn)(const BnpProblem&));
    void solve();
private:
    void recur();
    BnpProblem& m_bnp_problem;
    std::vector<Action> (*m_branch_callback)(BnpProblem&);
    std::vector<Action> (*m_propagation_callback)(BnpProblem&);
    bool (*m_prune_callback)(const BnpProblem&);
    uint32_t m_nnodes_explored, m_nprunnings, m_nactions_propagated;
};

template <typename BnpProblem,
          typename Action>
Bnp<BnpProblem, Action>::Bnp(
    BnpProblem& bnp_problem,
    std::vector<Action> (*branch_callback_fn)(BnpProblem&)):
    m_bnp_problem(bnp_problem),
    m_branch_callback(branch_callback_fn),
    m_propagation_callback(nullptr),
    m_prune_callback(nullptr),
    m_nnodes_explored(0),
    m_nprunnings(0),
    m_nactions_propagated(0) {}


template <typename BnpProblem,
          typename Action>
void Bnp<BnpProblem, Action>::set_propagation_callback(
    std::vector<Action> (*callback_fn)(BnpProblem&)) {
    m_propagation_callback = callback_fn;
}

template <typename BnpProblem,
          typename Action>
void Bnp<BnpProblem, Action>::set_prune_callback(
    bool (*callback_fn)(const BnpProblem&)) {
    m_prune_callback = callback_fn;
}

template <typename BnpProblem,
          typename Action>
void Bnp<BnpProblem, Action>::solve() {
    m_nnodes_explored = 0;
    m_nprunnings = 0;
    m_nactions_propagated = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "Using BNP solver \n";
    if(m_prune_callback != nullptr)
        std::cout << "Prunning enabled \n";
    if(m_propagation_callback != nullptr)
        std::cout << "Propagation enabled \n";
    recur();
    std::cout << "Solved: " << (m_bnp_problem.is_solved() ? "Yes" : "No") << '\n';
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Seconds elapsed: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0
              << '\n';
    std::cout << "Nodes explored: " << m_nnodes_explored << '\n';
    std::cout << "Prunnings: " << m_nprunnings << '\n';
    std::cout << "Propagated actions: " << m_nactions_propagated << '\n';
    
    return;
}

template <typename BnpProblem,
          typename Action>
void Bnp<BnpProblem, Action>::recur() {
    ++m_nnodes_explored;
    if(m_bnp_problem.is_solved())
        return;
    if(m_prune_callback != nullptr && !m_prune_callback(m_bnp_problem)) {
        std::cout << "Prunning \n";
        ++m_nprunnings;
        return;
    }
    std::vector<Action> propagated_actions;
    if(m_propagation_callback != nullptr)
        // callback is expected to modify the m_bnp_problem and return the actions it took
        propagated_actions = m_propagation_callback(m_bnp_problem);
        if(propagated_actions.size() > 0) {
            m_nactions_propagated += propagated_actions.size();
            recur();
        }
            
    if(m_bnp_problem.is_solved())
        return;
    // if problem is at infeasible state, brancher should give empty action set
    std::vector<Action> actions = m_branch_callback(m_bnp_problem);
    for(Action& branch_action: actions) {
        branch_action.apply(m_bnp_problem);
        recur();
        if(m_bnp_problem.is_solved())
            return;
        else
            branch_action.undo(m_bnp_problem);
    }
    for(Action& propagation_action: propagated_actions)
        propagation_action.undo(m_bnp_problem);
}