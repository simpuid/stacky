#pragma once
#include <memory.hpp>

class Console : public StackBase
{
    memseg lastChar;
    bool empty = true;
    memseg read();
    void pop();
    bool isEmpty();
    void push(memseg data);
};

class Add : public Stack
{
    void push(memseg data);
};
class And : public Stack
{
    void push(memseg data);
};
class Or : public Stack
{
    void push(memseg data);
};
class RightShift : public Stack
{
    void push(memseg data);
};
class LeftShift : public Stack
{
    void push(memseg data);
};
class Invert : public Stack
{
    void push(memseg data);
};
class Bin:public StackBase
{
    memseg read();
    void pop();
    bool isEmpty();
    void push(memseg data);
};