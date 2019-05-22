#include <parser.hpp>
#include <sstream>
#include <console.hpp>

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

void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList);
void handleBracket(Token t, vector<unique_ptr<Statement>> &list, TokenList &tList)
{
    if (t.type == Type::EmptyStart)
    {
        unique_ptr<EmptyBlock> b = make_unique<EmptyBlock>();
        recursiveParsing(b->statements,tList);
        list.push_back(move(b));
    }
    else
    {
        unique_ptr<ZeroBlock> b = make_unique<ZeroBlock>();
        recursiveParsing(b->statements,tList);
        list.push_back(move(b));
    }
}
void handleOperator(Token t, vector<unique_ptr<Statement>> &list, TokenList &tList)
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
            list.push_back(make_unique<Operator>(opList,t2.data));
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
void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList)
{
    while (!tList.isEmpty())
    {
        Token t = tList.next();
        if (isBlockEnd(t.type))
            return;
        else if (isBlockStart(t.type))
        {
            handleBracket(t, list, tList);
        }
        else if (isOperator(t.type))
        {
            handleOperator(t, list, tList);
        }
        else if (t.type == Type::Stack)
        {
            //Statement *s = new SetStack(t.data);
            list.push_back(make_unique<SetStack>(t.data));
        }
        else if (t.type == Type::Number)
        {
            //Statement *s = new SetNumber(t.data);
            list.push_back(make_unique<SetNumber>(t.data));
        }
    }
}

vector<unique_ptr<Statement>> parse(const vector<Token> &token)
{
    TokenList list(token);
    vector<unique_ptr<Statement>> graph;
    recursiveParsing(graph, list);
    return graph;
}