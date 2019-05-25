#include <special.hpp>
#include <iostream>

using namespace std;

// console functions
memseg Console::read()
{
    if (empty)
    {
        char in;
        cin >> in;
        lastChar = in;
        empty = false;
    }
    return (memseg)lastChar;
}
void Console::pop()
{
    empty = true;
}
bool Console::isEmpty()
{
    return empty;
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

// trash bin function(does nothing)
memseg Bin::read()
{
    return 0;
}
void Bin::pop() {}
bool Bin::isEmpty()
{
    return true;
}
void Bin::push(memseg data) {}