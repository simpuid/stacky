#include <special.hpp>
#include <iostream>

using namespace std;

// console functions
memseg Console::read()
{
    if (!isEmpty())
        return inBuffer[inBuffer.size() - 1];
    else
        return 0;
}
void Console::pop()
{
    inBuffer.pop_back();
}
bool Console::isEmpty()
{
    if (inBuffer.size() != 0)
        return false;
    char c;
    if (cin.get(c))
    {
        inBuffer.push_back(c);
        return false;
    }
    else
    return true;
}
void Console::push(memseg data)
{
    cout << (char)data;
}

// add function
void Add::push(memseg data)
{
    if (isEmpty())
        vec.push_back(data);
    else
    {
        memseg r = read();
        r += data;
        pop();
        push(r);
    }
}

// and function
void And::push(memseg data)
{
    if (isEmpty())
        vec.push_back(data);
    else
    {
        memseg r = read();
        r &= data;
        pop();
        push(r);
    }
}

// or function
void Or::push(memseg data)
{
    if (isEmpty())
        vec.push_back(data);
    else
    {
        memseg r = read();
        r |= data;
        pop();
        push(r);
    }
}

// rightshift function
void RightShift::push(memseg data)
{
    vec.push_back(data >> 1);
}

// leftshift function
void LeftShift::push(memseg data)
{
    vec.push_back(data << 1);
}

// invert function
void Invert::push(memseg data)
{
    vec.push_back(~data);
}