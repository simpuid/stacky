#pragma once
#include <graph.hpp>
#include <memory.hpp>
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

class Runner : public Visitor
{
    Source *source;
    Number number;

public:
    Runner();
    void visit(Statement &target);
    void visit(SetStack &target);
    void visit(SetNumber &target);
    void visit(ZeroBlock &target);
    void visit(EmptyBlock &target);
    void visit(Operator &target);
};