#include <graph.hpp>
#include <iostream>

Operator::Operator(vector<Operation> operations, string target) : operations(operations), target(target) {}
SetStack::SetStack(string name) : name(name){};
SetNumber::SetNumber(string number) : number(number) {}

void Statement::accept(Visitor &v)
{
}
void SetStack::accept(Visitor &v)
{
    v.visit(*this);
}
void SetNumber::accept(Visitor &v)
{
    v.visit(*this);
}
void ZeroBlock::accept(Visitor &v)
{
    v.visit(*this);
}
void EmptyBlock::accept(Visitor &v)
{
    v.visit(*this);
}
void Operator::accept(Visitor &v)
{
    v.visit(*this);
}
void accept(Statement *statement, Visitor &visitor)
{
    if (dynamic_cast<Operator *>(statement) != nullptr)
    {
        dynamic_cast<Operator *>(statement)->accept(visitor);
    }
    else if (dynamic_cast<SetStack *>(statement) != nullptr)
    {
        dynamic_cast<SetStack *>(statement)->accept(visitor);
    }
    else if (dynamic_cast<SetNumber *>(statement) != nullptr)
    {
        dynamic_cast<SetNumber *>(statement)->accept(visitor);
    }
    else if (dynamic_cast<ZeroBlock *>(statement) != nullptr)
    {
        dynamic_cast<ZeroBlock *>(statement)->accept(visitor);
    }
    else if (dynamic_cast<EmptyBlock *>(statement) != nullptr)
    {
        dynamic_cast<EmptyBlock *>(statement)->accept(visitor);
    }
}

void Printer::visit(SetStack &target)
{
    cout << "stack(" << target.name << ")";
}
void Printer::visit(SetNumber &target)
{
    cout << "number(" << target.number << ')';
}
void Printer::visit(ZeroBlock &target)
{
    cout << "[";
    for (auto &t : target.statements)
    {
        accept(t.get(), *this);
    }
    cout << "]";
}
void Printer::visit(EmptyBlock &target)
{
    cout << "{";
    for (auto &t : target.statements)
    {
        accept(t.get(), *this);
    }
    cout << "}";
}
void Printer::visit(Statement &target)
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
    cout << ", "<<target.target<<" )";
}
