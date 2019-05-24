#include <visitor.hpp>
#include <iostream>
#include <queue>
using namespace std;

void Printer::visit(SetStack &target)
{
    cout << "stack(" << target.stack.get() << ") ";
}
void Printer::visit(SetNumber &target)
{
    cout << "number(" << (int)target.number << ") ";
}
void Printer::visit(ZeroBlock &target)
{
    cout << "[";
    for (auto &t : target.statements)
    {
        t->accept(*this);
    }
    cout << "]";
}
void Printer::visit(EmptyBlock &target)
{
    cout << "{";
    for (auto &t : target.statements)
    {
        t->accept(*this);
    }
    cout << "}";
}
void Printer::visit(Statement &_target)
{
    cout << "statement";
}
void Printer::visit(Operator &target)
{
    cout << "operator(";
    for (auto op : target.operations)
    {
        cout << (op == Operation::Move ? '>' : '+');
    }
    cout << "," << target.target.get() << ") ";
}


Runner::Runner():number(Number()),source(&number){}
void Runner::visit(Statement &target)
{
}
void Runner::visit(SetStack &target)
{
    source = target.stack.get();
}
void Runner::visit(SetNumber &target)
{
    number.value = target.number;
    source = &number;
}
void Runner::visit(ZeroBlock &target)
{
    while (source->read() != 0)
    {
        for (auto &t : target.statements)
        {
            t->accept(*this);
        }
    }
}
void Runner::visit(EmptyBlock &target)
{
    
    while (!source->isEmpty())
    {
        for (auto &t : target.statements)
        {
            t->accept(*this);
        }
    }
}
void Runner::visit(Operator &target)
{
    queue<memseg> q;
    q.empty();
    for (auto t : target.operations)
    {
        q.push(source->read());
        if (t == Operation::Move)
        {
            source->pop();
        }
    }
    while (!q.empty())
    {
        target.target->push(q.front());
        q.pop();
    }
    
    source = target.target.get();
}