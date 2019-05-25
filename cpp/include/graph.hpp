#pragma once
#include <string>
#include <vector>
#include <memory>
#include <memory.hpp>
using namespace std;

// enum for the two operations the lang support
enum class Operation
{
    Move,Copy
};

// foreward declaration of base class visitor
class Visitor;

// base class for all statement
class Statement
{
public:
    virtual void accept(Visitor &v);
};

// operator statement containing the list of operations to perform and the target stack
class Operator : public Statement
{
public:
    vector<Operation> operations;
    unique_ptr<StackBase> &target;
    Operator(vector<Operation> operations, unique_ptr<StackBase> &target);
    void accept(Visitor &v);
};

// setstack statement containing the pointer to target stack. It sets the source to targer stack
class SetStack : public Statement
{
public:
    unique_ptr<StackBase> &stack;
    SetStack(unique_ptr<StackBase> &stack);
    void accept(Visitor &v);
};

// setnumber statement containing the target value. It sets the source to the target number
class SetNumber : public Statement
{
public:
    memseg number;
    SetNumber(memseg number);
    void accept(Visitor &v);
};

// block statement containing list of child statement. Loop until the last stack have top element zero
class ZeroBlock : public Statement
{
public:
    vector<unique_ptr<Statement>> statements;
    void accept(Visitor &v);
};

// block statement containing list of child statement. Loop until the last stack is empty
class EmptyBlock : public Statement
{
public:
    vector<unique_ptr<Statement>> statements;
    void accept(Visitor &v);
};