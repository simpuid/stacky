#pragma once
#include <string>
#include <vector>
#include <memory>
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
    string target;
    Operator(vector<Operation> operations, string target);
    void accept(Visitor &v);
};

class SetStack : public Statement
{
public:
    string name;
    SetStack(string name);
    void accept(Visitor &v);
};

class SetNumber : public Statement
{
public:
    string number;
    SetNumber(string number);
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

class Visitor
{
public:
    virtual void visit(Statement &target) = 0;
    virtual void visit(SetStack &target) = 0;
    virtual void visit(SetNumber &target) = 0;
    virtual void visit(ZeroBlock &target) = 0;
    virtual void visit(EmptyBlock &target) = 0;
    virtual void visit(Operator &target) = 0;
};

class Printer : public Visitor
{
    void visit(Statement &target);
    void visit(SetStack &target);
    void visit(SetNumber &target);
    void visit(ZeroBlock &target);
    void visit(EmptyBlock &target);
    void visit(Operator &target);
};

void accept(Statement *statement, Visitor &visitor);