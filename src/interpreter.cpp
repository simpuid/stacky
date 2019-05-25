#include <interpreter.hpp>
#include <iostream>
#include <queue>
using namespace std;

Interpreter::Interpreter(vector<unique_ptr<Statement>> &statements)
{
    source = &number;
    for (auto &t : statements)
    {
        t->accept(*this);
    }
}
void Interpreter::visit(Statement &target)
{
}
void Interpreter::visit(SetStack &target)
{
    source = target.stack.get();
}
void Interpreter::visit(SetNumber &target)
{
    number.value = target.number;
    source = &number;
}
void Interpreter::visit(ZeroBlock &target)
{
    while (source->read() != 0)
    {
        for (auto &t : target.statements)
        {
            t->accept(*this);
        }
    }
}
void Interpreter::visit(EmptyBlock &target)
{

    while (!source->isEmpty())
    {
        for (auto &t : target.statements)
        {
            t->accept(*this);
        }
    }
}
void Interpreter::visit(Operator &target)
{
    queue<memseg> q;
    for (auto t : target.operations)
    {
        q.push(source->read());
        if (t == Operation::Move)
            source->pop();
    }
    while (!q.empty())
    {
        target.target->push(q.front());
        q.pop();
    }
    source = target.target.get();
}