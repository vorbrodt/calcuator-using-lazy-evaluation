#pragma once

#include <string>
using namespace std;

class Register
{
public:
    string registerName;
    int registerValue;
    Register(string name, int value)
        : registerName(name), registerValue(value)
    {
    }
    // setters
    void setValue(int val);
    // getters
    int getValue();
    string getName();
};
