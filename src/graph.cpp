#include <graph.hpp>
#include <visitor.hpp>

Operator::Operator(vector<Operation> operations, unique_ptr<Stack>& target) : operations(operations), target(target) {}
SetStack::SetStack(unique_ptr<Stack> &stack) : stack(stack){};
SetNumber::SetNumber(memseg number) : number(number) {}

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
