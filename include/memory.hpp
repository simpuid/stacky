#pragma once
#include <vector>
#include <map>

using namespace std;
typedef char memseg;
class Source
{
public:
    virtual memseg read() = 0;
    virtual void pop() = 0;
    virtual bool isEmpty() = 0;
};

class Target
{
public:
    virtual void push(memseg data) = 0;
};

class Stack : public Source, Target
{
public:
    vector<memseg> vec;
    virtual memseg read();
    virtual void pop();
    virtual bool isEmpty();
    virtual void push(memseg data);
};

class Number : public Source
{
public:
    memseg value;
    memseg read();
    void pop();
    bool isEmpty();
};