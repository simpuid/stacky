#pragma once
#include <string>
#include <vector>
using namespace std;

enum class Type
{
    Move,Copy,ZeroStart,ZeroEnd,EmptyStart,EmptyEnd,Stack,Number
};

class Token
{
    public:
    Type type;
    string data;
    int line;
    int column;

    Token(Type type,string data,int line,int column);
};

vector<Token> scan(const string &code);