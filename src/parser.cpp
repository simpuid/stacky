#include <parser.hpp>
#include <sstream>
#include <console.hpp>
#include <memory.hpp>
#include <iostream>
#include <special.hpp>

TokenList::TokenList(const vector<Token> &token) : token(token)
{
    pointer = 0;
}
Token TokenList::next()
{
    return token[pointer++];
}
bool TokenList::isEmpty()
{
    return pointer >= (int)token.size();
}

bool isOperator(Type t)
{
    return t == Type::Move || t == Type::Copy;
}
bool isBlockStart(Type t)
{
    return t == Type::ZeroStart || t == Type::EmptyStart;
}
bool isBlockEnd(Type t)
{
    return t == Type::ZeroEnd || t == Type::EmptyEnd;
}
Operation convert(Type t)
{
    return t == Type::Move ? Operation::Move : Operation::Copy;
}
memseg convert(const string &num)
{
    memseg m = 0;
    memseg tens = 1;

    for (int i = num.length()-1;i >= 0;i--)
    {
        m = (m+(tens*(num[i]-'0'))%256)%256;
        tens = (tens*10)%256;
    }
    return m;
}


void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList, map<string,unique_ptr<Stack>> &stack);
void handleBracket(Token t, vector<unique_ptr<Statement>> &list, TokenList &tList, map<string,unique_ptr<Stack>> &stack)
{
    if (t.type == Type::EmptyStart)
    {
        unique_ptr<EmptyBlock> b = make_unique<EmptyBlock>();
        recursiveParsing(b->statements,tList,stack);
        list.push_back(move(b));
    }
    else
    {
        unique_ptr<ZeroBlock> b = make_unique<ZeroBlock>();
        recursiveParsing(b->statements,tList,stack);
        list.push_back(move(b));
    }
}
void handleOperator(Token t, vector<unique_ptr<Statement>> &list, TokenList &tList,map<string,unique_ptr<Stack>> &stack)
{
    vector<Operation> opList;
    opList.push_back(convert(t.type));
    while (!tList.isEmpty())
    {
        Token t2 = tList.next();
        if (isOperator(t2.type))
        {
            opList.push_back(convert(t2.type));
        }
        else if (t2.type == Type::Stack)
        {
            //Statement *opStatement = new Operator(opList, t2.data);
            auto iter = stack.find(t2.data);
            list.push_back(make_unique<Operator>(opList,iter->second));
            return;
        }
        else
        {
            stringstream msg;
            msg << "unexpected token " << t2.data << " line:" << t2.line << " column:" << t2.column << " after operator";
            error(msg.str());
        }
    }
    stringstream msg;
    msg << "no stack specified after operator " << t.data << " line:" << t.line << " column:" << t.column;
    error(msg.str());
}
void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList,map<string,unique_ptr<Stack>> &stack)
{
    while (!tList.isEmpty())
    {
        Token t = tList.next();
        if (isBlockEnd(t.type))
            return;
        else if (isBlockStart(t.type))
        {
            handleBracket(t, list, tList,stack);
        }
        else if (isOperator(t.type))
        {
            handleOperator(t, list, tList,stack);
        }
        else if (t.type == Type::Stack)
        {
            auto iter = stack.find(t.data);
            list.push_back(make_unique<SetStack>(iter->second));
        }
        else if (t.type == Type::Number)
        {
            list.push_back(make_unique<SetNumber>(convert(t.data)));
        }
    }
}

vector<unique_ptr<Statement>> parse(const vector<Token> &token, map<string,unique_ptr<Stack>> &stack)
{
    TokenList list(token);
    vector<unique_ptr<Statement>> graph;
    recursiveParsing(graph, list,stack);
    return graph;
}

map<string,unique_ptr<Stack>> generateStackMap(const vector<Token> &token)
{
    map<string,unique_ptr<Stack>> m;
    m.insert(pair<string,unique_ptr<Stack>>("output",make_unique<Output>()));
    for (auto t :token)
    {
        if (t.type == Type::Stack)
        {
            auto iter = m.find(t.data);
            if (iter == m.end())
            {
                m.insert(pair<string,unique_ptr<Stack>>(t.data,make_unique<Stack>()));
            }
        }
    }
    return m;
}