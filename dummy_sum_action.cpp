#include <iostream>
#include "dummy_sum_action.hpp"
#include "dummy_sum_problem.hpp"


DummySumBnpSetAction::DummySumBnpSetAction(char variable_name, int value):
    m_variable_name(variable_name),
    m_new_value(value) {
    }

void DummySumBnpSetAction::undo(DummySumBnpProblem& ssbp) {
    if(m_variable_name == 'x') {
        std::cout << "Undoing x: " << ssbp.x << "->" << m_previous_value << "\n";
        ssbp.x = m_previous_value;
    }
    else if(m_variable_name == 'y') {
        std::cout << "Undoing y: " << ssbp.y << "->" << m_previous_value << "\n";
        ssbp.y = m_previous_value;
    }
}

void DummySumBnpSetAction::apply(DummySumBnpProblem& ssbp) {
    if(m_variable_name == 'x'){
        std::cout << "Applying x = " << m_new_value << "\n";
        m_previous_value = ssbp.x;
        ssbp.x = m_new_value;
    } else {
        std::cout << "Applying y = " << m_new_value << "\n";
        m_previous_value = ssbp.y;
        ssbp.y = m_new_value;
    }
}