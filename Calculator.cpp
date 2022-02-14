#include "Calculator.h"

void Calculator::add(Register &reg, int value)
{
    reg.setValue(reg.registerValue + value);
}
void Calculator::subtract(Register &reg, int value)
{
    reg.setValue(reg.registerValue - value);
}
void Calculator::multiply(Register &reg, int value)
{
    reg.setValue(reg.registerValue * value);
}

// check if entered operation is valid
bool Calculator::isAllowedOperation(string operation)
{
    vector<string> allowedOperations{"add", "subtract", "multiply"};
    for (string s : allowedOperations)
    {
        if (stringEquals(s, operation))
        {
            return true;
        }
    }
    return false;
}

// check if register exists
bool Calculator::registerExists(string registerName, vector<Register> &currentRegisters)
{
    for (Register &reg : currentRegisters)
    {
        if (stringEquals(reg.getName(), registerName))
        {
            return true;
        }
    }
    return false;
}

/*
iterate over string until non-digit character found
if no non-digit character found consider it a digit
*/
bool Calculator::is_number(const std::string &s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

// handels evaluation logic
void Calculator::handleEvaluation(vector<Register> &currentRegisters, string registerName, string operation, string value)
{
    for (Register &reg : currentRegisters)
    {
        // find relevant register
        if (stringEquals(reg.getName(), registerName))
        {

            double num;
            // check if given input <value> is a number
            if (is_number(value))
            {
                num = stoi(value);
            }
            // else assume its a register and get is value from there
            else
            {
                for (Register &r : currentRegisters)
                {
                    if (stringEquals(r.getName(), value))
                    {
                        num = r.getValue();
                        break;
                    }
                }
            }

            // check what operation to do and execute it
            if (stringEquals(operation, "add"))
            {
                add(reg, num);
            }
            else if (stringEquals(operation, "subtract"))
            {
                subtract(reg, num);
            }
            else if (stringEquals(operation, "multiply"))
            {
                multiply(reg, num);
            }
            else
            {
                cout << operation << " is not a valid operation" << endl;
            }

            break;
        }
    }
}

// Handel case insensitive comparison between strings
bool Calculator::stringEquals(const string &a, const string &b)
{
    if (strcasecmp(a.c_str(), b.c_str()) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// get value of register
string Calculator::getValueFromRegister(vector<Register> &currentRegisters, string registerName)
{
    for (Register &r : currentRegisters)
    {
        if (stringEquals(r.registerName, registerName))
        {
            return to_string(r.getValue());
        }
    }
    return 0;
}

// looks through lazy evaluation stack and check if program should wait with print until all commands have been evaluated
bool Calculator::waitForPrint(vector<vector<string>> lazyEvaluationStack, string registerName)
{
    for (vector<string> command : lazyEvaluationStack)
    {
        if (stringEquals(command[0], registerName))
        {
            return true;
        }
    }
    return false;
}