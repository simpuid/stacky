#pragma once
#include <string>
using namespace std;

// all the types of tokens
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

// token class which contains all the data
class Token
{
public:
    Type type;
    string data;
    int line;
    int column;
    friend ostream &operator<<(ostream &out, const Token &token);
};