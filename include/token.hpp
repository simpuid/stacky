#pragma once
#include <string>
using namespace std;

enum class Type
{
    Move,
    Copy,
    ZeroStart,
    ZeroEnd,
    EmptyStart,
    EmptyEnd,
    Stack,
    Number
};

class Token
{
public:
    Type type;
    string data;
    int line;
    int column;
};