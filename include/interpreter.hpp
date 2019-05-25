#pragma once
#include <visitor.hpp>
#include <vector>
#include <memory>
class Interpreter : public Visitor
{
    StackBase *source;
    Number number;

public:
    Interpreter(vector<unique_ptr<Statement>> &statements);
    void visit(Statement &target);
    void visit(SetStack &target);
    void visit(SetNumber &target);
    void visit(ZeroBlock &target);
    void visit(EmptyBlock &target);
    void visit(Operator &target);
};