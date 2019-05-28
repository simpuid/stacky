#pragma once
#include <vector>
#include <cstdint>
using namespace std;
typedef uint32_t memseg;

// base class for all stack based object
class StackBase
{
public:
    virtual memseg read()=0;
    virtual void pop()=0;
    virtual bool isEmpty()=0;
    virtual void push(memseg data)=0;
};

// normal user defined stack
class Stack : public StackBase
{
public:
    vector<memseg> vec;
    virtual memseg read();
    virtual void pop();
    virtual bool isEmpty();
    virtual void push(memseg data);
};

// special stack to store the number
class Number : public StackBase
{
public:
    memseg value;
    memseg read();
    void pop();
    bool isEmpty();
    void push(memseg data);
};