#pragma once
#include <vector>
#include <map>
using namespace std;
typedef unsigned char memseg;

class StackBase
{
public:
    virtual memseg read()=0;
    virtual void pop()=0;
    virtual bool isEmpty()=0;
    virtual void push(memseg data)=0;
};

class Stack : public StackBase
{
public:
    vector<memseg> vec;
    virtual memseg read();
    virtual void pop();
    virtual bool isEmpty();
    virtual void push(memseg data);
};

class Number : public StackBase
{
public:
    memseg value;
    memseg read();
    void pop();
    bool isEmpty();
    void push(memseg data);
};