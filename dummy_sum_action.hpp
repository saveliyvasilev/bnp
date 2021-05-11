#pragma once

class DummySumBnpProblem;

class DummySumBnpSetAction {
private:
    char m_variable_name;
    int m_new_value, m_previous_value;
public:
    DummySumBnpSetAction(char variable_name, int value);
    void undo(DummySumBnpProblem& ssbp);
    void apply(DummySumBnpProblem& ssbp);
};
