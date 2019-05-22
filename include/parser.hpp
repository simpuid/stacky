
#pragma once
#include <graph.hpp>
#include <scanner.hpp>
#include <vector>
#include <memory>
class TokenList
{
    const vector<Token> &token;
    int pointer;

public:
    TokenList(const vector<Token> &token);
    Token next();
    bool isEmpty();
};
vector<unique_ptr<Statement>> parse(const vector<Token> &token);