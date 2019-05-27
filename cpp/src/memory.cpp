#include <memory.hpp>

// Stack funtions
memseg Stack::read()
{
    return (vec.size() != 0) ? vec[vec.size() - 1] : 0;
}
void Stack::pop()
{
    if (!isEmpty())
        vec.pop_back();
}
bool Stack::isEmpty()
{
    return (vec.size() == 0);
}
void Stack::push(memseg data)
{
    vec.push_back(data);
}

// Number functions
memseg Number::read()
{
    return value;
}
bool Number::isEmpty()
{
    return true;
}
void Number::pop()
{
}
void Number::push(memseg data)
{
}