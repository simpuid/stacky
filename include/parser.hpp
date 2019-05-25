#pragma once
#include <graph.hpp>
#include <scanner.hpp>
#include <vector>
#include <memory>
#include <map>
#include <memory.hpp>
// tokenlist class is used in recursive function to supply token
class TokenList
{
public:
    const vector<Token> &token;
    int pointer = 0;
    TokenList(const vector<Token> &token);
    Token next();
    bool isEmpty();
};

vector<unique_ptr<Statement>> parse(const vector<Token> &token, map<string, unique_ptr<StackBase>> &stack);
map<string, unique_ptr<StackBase>> generateStackMap(const vector<Token> &token);