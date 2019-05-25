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