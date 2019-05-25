#include <interpreter.hpp>
#include <iostream>
#include <queue>
using namespace std;

// Interpreter functions for all Statement
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

// set source to target value
void Interpreter::visit(SetStack &target)
{
    source = target.stack.get();
}

// sets the value of Number stack and point source to number stack
void Interpreter::visit(SetNumber &target)
{
    number.value = target.number;
    source = &number;
}

// loops till the source have zero at top
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

// loops till the source is empty
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

// operates from source to target
void Interpreter::visit(Operator &target)
{
    queue<memseg> q;
    // operates on source and keeps the element in queue
    for (auto t : target.operations)
    {
        q.push(source->read());
        if (t == Operation::Move)
            source->pop();
    }
    // empties the queue to target
    while (!q.empty())
    {
        target.target->push(q.front());
        q.pop();
    }
    // set the source to target
    source = target.target.get();
}