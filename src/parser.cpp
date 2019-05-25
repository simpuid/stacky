#include <parser.hpp>
#include <sstream>
#include <console.hpp>
#include <iostream>
#include <special.hpp>

TokenList::TokenList(const vector<Token> &token) : token(token) {}

Token TokenList::next()
{
    return token[pointer++];
}
bool TokenList::isEmpty()
{
    return pointer >= (int)token.size();
}
memseg convert(const string &num)
{
    memseg m{0}, tens{1};
    for (int i = num.length() - 1; i >= 0; i--)
    {
        m = (m + (tens * (num[i] - '0')) % 256) % 256;
        tens = (tens * 10) % 256;
    }
    return m;
}

void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack);

template <class T>
void handleBracket(vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack)
{
    unique_ptr<T> b = make_unique<T>();
    recursiveParsing(b->statements, tList, stack);
    list.push_back(move(b));
}
void handleOperator(Token tt, vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack)
{
    vector<Operation> opList;
    opList.push_back(tt.type == Type::Move ? Operation::Move : Operation::Copy);
    while (!tList.isEmpty())
    {
        Token t = tList.next();
        switch (t.type)
        {
        case Type::Move:
            opList.push_back(Operation::Move);
            break;
        case Type::Copy:
            opList.push_back(Operation::Copy);
            break;
        case Type::Stack:
            list.push_back(make_unique<Operator>(opList, stack.find(t.data)->second));
            return;
        default:
            stringstream msg;
            msg << "unexpected token " << t.data << " line:" << t.line << " column:" << t.column << " after operator";
            error(msg.str());
            break;
        }
    }
    stringstream msg;
    msg << "no stack specified after operator " << tt.data << " line:" << tt.line << " column:" << tt.column;
    error(msg.str());
}
void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack)
{
    while (!tList.isEmpty())
    {
        Token t = tList.next();
        switch (t.type)
        {
        case Type::ZeroEnd:
        case Type::EmptyEnd:
            return;
        case Type::ZeroStart:
            handleBracket<ZeroBlock>(list, tList, stack);
            break;
        case Type::EmptyStart:
            handleBracket<EmptyBlock>(list, tList, stack);
            break;
        case Type::Move:
        case Type::Copy:
            handleOperator(t, list, tList, stack);
            break;
        case Type::Stack:
            list.push_back(make_unique<SetStack>(stack.find(t.data)->second));
            break;
        case Type::Number:
            list.push_back(make_unique<SetNumber>(convert(t.data)));
            break;
        }
    }
}
void checkBrackets(const vector<Token> &token)
{
    vector<Token> b;
    for (Token t : token)
    {
        if (t.type == Type::EmptyStart || t.type == Type::EmptyEnd || t.type == Type::ZeroStart || t.type == Type::ZeroEnd)
        {
            if ((b.size() > 0) && ((t.type == Type::ZeroEnd && b[b.size() - 1].type == Type::ZeroStart) || (t.type == Type::EmptyEnd && b[b.size() - 1].type == Type::EmptyStart)))
                b.pop_back();
            else
                b.push_back(t);
        }
    }
    if (b.size() > 0)
    {
        std::stringstream stream;
        stream << "parser error";
        for (Token t : b)
        {
            stream << "\nunmatched bracket '" << t.data << "' at line:" << t.line << " column:" << t.column;
        }
        error(stream.str());
    }
}

void checkStart(const std::vector<Token> &tokens)
{
    if (tokens.size() > 0 && (tokens[0].type != Type::Stack && tokens[0].type != Type::Number))
        error("Unexpected starting token.It should be either a stack or a number");
}
vector<unique_ptr<Statement>> parse(const vector<Token> &token, map<string, unique_ptr<StackBase>> &stack)
{
    checkBrackets(token);
    checkStart(token);
    TokenList list(token);
    vector<unique_ptr<Statement>> graph;
    recursiveParsing(graph, list, stack);
    return graph;
}

map<string, unique_ptr<StackBase>> generateStackMap(const vector<Token> &token)
{
    map<string, unique_ptr<StackBase>> m;
    m.insert(pair<string, unique_ptr<StackBase>>("io", make_unique<Console>()));
    m.insert(pair<string, unique_ptr<StackBase>>("add", make_unique<Add>()));
    m.insert(pair<string, unique_ptr<StackBase>>("and", make_unique<And>()));
    m.insert(pair<string, unique_ptr<StackBase>>("or", make_unique<Or>()));
    m.insert(pair<string, unique_ptr<StackBase>>("rsft", make_unique<RightShift>()));
    m.insert(pair<string, unique_ptr<StackBase>>("lsft", make_unique<LeftShift>()));
    m.insert(pair<string, unique_ptr<StackBase>>("inv", make_unique<Invert>()));
    m.insert(pair<string, unique_ptr<StackBase>>("bin", make_unique<Bin>()));
    for (auto t : token)
    {
        if (t.type == Type::Stack)
        {
            auto iter = m.find(t.data);
            if (iter == m.end())
            {
                m.insert(pair<string, unique_ptr<Stack>>(t.data, make_unique<Stack>()));
            }
        }
    }
    return m;
}

