#include "Calculator.h"
#include "Register.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    Calculator calculator;
    vector<Register> currentRegisters;
    string command;
    vector<vector<string>> printCommandStack;
    vector<vector<string>> lazyEvaluationStack;
    vector<vector<string>> lazyPrintResults;

    do
    {
        cout << "==================== Calculator ===================" << endl;
        cout << "Enter one of the following commands:" << endl;
        cout << " <register> <operation> <value>" << endl;
        cout << " print <register>" << endl;
        cout << " quit" << endl;
        cout << "Your command: ";
        // read input
        getline(cin, command);

        // initialize string stream
        istringstream stream(command);
        vector<string> commandLine;
        string temp;
        // add words in stream into vector
        while (stream >> temp)
        {
            commandLine.push_back(temp);
        }

        // check if command is: quit
        if (commandLine.size() == 1 && calculator.stringEquals(commandLine[0], "quit"))
        {
            continue;
        }
        // check if command is: print <register>
        else if (commandLine.size() == 2 && calculator.stringEquals(commandLine[0], "print"))
        {
            // check if register exists in lazyEvaluationStack then it needs to be evaluated later, therefor keep command
            if (
                calculator.waitForPrint(lazyEvaluationStack, commandLine[1]))
            {
                // add entire command to lazyPrintResults
                lazyPrintResults.push_back(commandLine);
            }
            // otherwise get value now and add value to lazyPrintResults
            else
            {
                vector<string> printResult;
                printResult.push_back(calculator.getValueFromRegister(currentRegisters, commandLine[1]));
                lazyPrintResults.push_back(printResult);
            }
        }
        // check if command is: <register> <operation> <value> and valid
        else if (commandLine.size() == 3 && calculator.isAllowedOperation(commandLine[1]) && !calculator.is_number(commandLine[0]))
        {
            // check if registers exist, if not create them and add to currentRegisters vector
            if (!calculator.registerExists(commandLine[0], currentRegisters))
            {
                currentRegisters.push_back(Register(commandLine[0], 0));
            }
            // check if <value> is register and not a digit
            if (!calculator.registerExists(commandLine[2], currentRegisters) && !calculator.is_number(commandLine[2]))
            {
                currentRegisters.push_back(Register(commandLine[2], 0));
            }

            // if <value> is number evaluate now
            if (calculator.is_number(commandLine[2]))
            {
                calculator.handleEvaluation(currentRegisters, commandLine[0], commandLine[1], commandLine[2]);
            }
            // else assume <value> is register and hold evaluation until needed therefor add to lazyEvaluationStack
            else
            {
                lazyEvaluationStack.push_back(commandLine);
            }
        }
        else
        {
            cout << "'" << command << "' is not a valid command." << endl;
        }

        cout << endl;

    } while (!calculator.stringEquals(command, "quit"));

    // handle lazy evaluation
    // reverse vector with commands for lazy evaluation
    reverse(lazyEvaluationStack.begin(), lazyEvaluationStack.end());
    // evalute commands which could not be evaluated earlier
    for (vector<string> c : lazyEvaluationStack)
    {
        calculator.handleEvaluation(currentRegisters, c[0], c[1], c[2]);
    }

    // handle prints
    for (vector<string> pr : lazyPrintResults)
    {
        // if vector<string> size is 1 simply print value
        if (pr.size() == 1)
        {
            cout << pr[0] << endl;
        }
        // else if vector<string> size is 2 it is of type: print <register>
        else if (pr.size() == 2)
        {
            vector<string> printResult;
            printResult.push_back(calculator.getValueFromRegister(currentRegisters, pr[1]));
            cout << printResult[0] << endl;
        }
    }

    return 0;
}