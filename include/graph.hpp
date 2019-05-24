#pragma once
#include <string>
#include <vector>
#include <memory>
#include <memory.hpp>
using namespace std;

enum class Operation
{
    Move,
    Copy
};
class Visitor;
class Statement
{
public:
    virtual void accept(Visitor &v);
};

class Operator : public Statement
{
public:
    vector<Operation> operations;
    unique_ptr<Stack> &target;
    Operator(vector<Operation> operations, unique_ptr<Stack> &target);
    void accept(Visitor &v);
};
class SetStack : public Statement
{
public:
    unique_ptr<Stack> &stack;
    SetStack(unique_ptr<Stack> &stack);
    void accept(Visitor &v);
};

class SetNumber : public Statement
{
public:
    memseg number;
    SetNumber(memseg number);
    void accept(Visitor &v);
};
class ZeroBlock : public Statement
{
public:
    vector<unique_ptr<Statement>> statements;
    void accept(Visitor &v);
};
class EmptyBlock : public Statement
{
public:
    vector<unique_ptr<Statement>> statements;
    void accept(Visitor &v);
};