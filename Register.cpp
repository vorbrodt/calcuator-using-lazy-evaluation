#include "Register.h"

void Register::setValue(int val)
{
    registerValue = move(val);
}
int Register::getValue()
{
    return registerValue;
}
string Register::getName()
{
    return registerName;
}