#include <graph.hpp>
#include <visitor.hpp>

Operator::Operator(vector<Operation> operations, unique_ptr<StackBase>& target) : operations(operations), target(target) {}

SetStack::SetStack(unique_ptr<StackBase> &stack) : stack(stack){};

SetNumber::SetNumber(memseg number) : number(number) {}

// accept method for visitor pattern
void Statement::accept(Visitor &v)
{
    v.visit(*this);
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
