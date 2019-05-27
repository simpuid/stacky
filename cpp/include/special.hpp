#pragma once
#include <memory.hpp>

// special stack to handle interaction with console
class Console : public StackBase
{
    memseg lastChar;
    bool empty = true;
    memseg read();
    void pop();
    bool isEmpty();
    void push(memseg data);
};

// special stack which add up its elements
class Add : public Stack
{
    void push(memseg data);
};

// special stack which & its elements
class And : public Stack
{
    void push(memseg data);
};

// special stack which | its elements
class Or : public Stack
{
    void push(memseg data);
};

// special stack which right shift its elements
class RightShift : public Stack
{
    void push(memseg data);
};

// special stack which left shift its elements
class LeftShift : public Stack
{
    void push(memseg data);
};

// special stack which ~ its elements
class Invert : public Stack
{
    void push(memseg data);
};