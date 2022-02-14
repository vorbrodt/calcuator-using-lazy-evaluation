#pragma once
#include "Register.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

class Calculator
{
public:
    void add(Register &reg, int value);
    void subtract(Register &reg, int value);
    void multiply(Register &reg, int value);
    bool isAllowedOperation(string operation);
    bool registerExists(string registerName, vector<Register> &currentRegisters);
    void handleEvaluation(vector<Register> &currentRegisters, string registerName, string operation, string value);
    bool is_number(const std::string &s);
    bool stringEquals(const string &a, const string &b);
    string getValueFromRegister(vector<Register> &currentRegisters, string registerName);
    bool waitForPrint(vector<vector<string>> lazyEvaluationStack, string registerName);
};