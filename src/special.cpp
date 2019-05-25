#include <special.hpp>
#include <iostream>

using namespace std;

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
void RightShift::push(memseg data)
{
    vec.push_back(data >> 1);
}
void LeftShift::push(memseg data)
{
    vec.push_back(data << 1);
}
void Invert::push(memseg data)
{
    vec.push_back(~data);
}

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