
#pragma once
#include <graph.hpp>
#include <scanner.hpp>
#include <vector>
#include <memory>
#include <map>
#include <memory.hpp>
class TokenList
{
    const vector<Token> &token;
    int pointer;

public:
    TokenList(const vector<Token> &token);
    Token next();
    bool isEmpty();
};
vector<unique_ptr<Statement>> parse(const vector<Token> &token, map<string,unique_ptr<Stack>> &stack);
map<string,unique_ptr<Stack>> generateStackMap(const vector<Token> &token);