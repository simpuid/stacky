#include <parser.hpp>
#include <sstream>
#include <error.hpp>
#include <special.hpp>

// TokenList functions
TokenList::TokenList(const vector<Token> &token) : token(token) {}

// returns the next token and increase the pointer
Token TokenList::next()
{
    return token[pointer++];
}

bool TokenList::isEmpty()
{
    return pointer >= (int)token.size();
}

// conver string to memseg
memseg convert(const string &num)
{
    memseg m{0}, tens{1};
    for (int i = num.length() - 1; i >= 0; i--)
    {
        m = m + (tens * (num[i] - '0'));
        tens = (tens * 10);
    }
    return m;
}

// foreward declaration of recursive function
void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack);

// recusive calls the function when the start of bracket is found
template <class T>
void handleBracket(vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack)
{
    unique_ptr<T> b = make_unique<T>();
    recursiveParsing(b->statements, tList, stack);
    list.push_back(move(b));
}

// merges all the consecutive operator tokens with target stack
void handleOperator(Token tt, vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack)
{
    vector<Operation> opList;
    opList.push_back(tt.type == Type::Move ? Operation::Move : Operation::Copy);
    while (!tList.isEmpty())
    {
        Token t = tList.next();
        switch (t.type)
        {
        // keep adding the next operator to opList
        case Type::Move:
            opList.push_back(Operation::Move);
            break;
        case Type::Copy:
            opList.push_back(Operation::Copy);
            break;
        // when the next token is stack then terminate the function
        case Type::Stack:
            list.push_back(make_unique<Operator>(opList, stack.find(t.data)->second));
            return;
        default:
            // next token is neither an operator nor a stack, so error
            stringstream msg;
            msg << "unexpected token " << t << " after operator " << tt;
            error(msg.str());
            return;
        }
    }
    // tokenlist ran out of tokens without the terminating stack token, so error
    stringstream msg;
    msg << "no stack specified after operator " << tt;
    error(msg.str());
}

// recursive call to parse the tokens
void recursiveParsing(vector<unique_ptr<Statement>> &list, TokenList &tList, map<string, unique_ptr<StackBase>> &stack)
{
    while (!tList.isEmpty())
    {
        Token t = tList.next();
        switch (t.type)
        {
        // exit condition if next tokens are closing brackets
        case Type::ZeroEnd:
        case Type::EmptyEnd:
            return;
        // recursive call if next tokens are starting brackets
        case Type::ZeroStart:
            handleBracket<ZeroBlock>(list, tList, stack);
            break;
        case Type::EmptyStart:
            handleBracket<EmptyBlock>(list, tList, stack);
            break;
        // special function call for operator
        case Type::Move:
        case Type::Copy:
            handleOperator(t, list, tList, stack);
            break;
        // setstack case
        case Type::Stack:
            list.push_back(make_unique<SetStack>(stack.find(t.data)->second));
            break;
        // setnumber case
        case Type::Number:
            list.push_back(make_unique<SetNumber>(convert(t.data)));
            break;
        }
    }
}

// reports about unmatched brackets
void checkBrackets(const vector<Token> &token)
{
    vector<Token> b;
    for (Token t : token)
    {
        if (t.type == Type::EmptyStart || t.type == Type::EmptyEnd || t.type == Type::ZeroStart || t.type == Type::ZeroEnd)
        {
            // if b has opening bracket of same type as closing bracket of t then pop b
            if ((b.size() > 0) && ((t.type == Type::ZeroEnd && b[b.size() - 1].type == Type::ZeroStart) || (t.type == Type::EmptyEnd && b[b.size() - 1].type == Type::EmptyStart)))
                b.pop_back();
            else
                b.push_back(t);
        }
    }
    // now b contains the unmatched brackets tokens, so error
    if (b.size() > 0)
    {
        std::stringstream stream;
        stream << "parser error";
        for (Token t : b)
        {
            stream << "\nunmatched bracket '" << t;
        }
        error(stream.str());
    }
}

// reports about non-literal and non-stack at start of tokenlist
void checkStart(const std::vector<Token> &tokens)
{
    if (tokens.size() > 0 && (tokens[0].type != Type::Stack && tokens[0].type != Type::Number))
        error("Unexpected starting token.It should be either a stack or a number");
}

// parse the tokenlist
vector<unique_ptr<Statement>> parse(const vector<Token> &token, map<string, unique_ptr<StackBase>> &stack)
{
    // check for error
    checkBrackets(token);
    checkStart(token);
    TokenList list(token);
    vector<unique_ptr<Statement>> graph;
    recursiveParsing(graph, list, stack);
    return graph;
}

// creates a map of stack which will be later used in parsing
map<string, unique_ptr<StackBase>> generateStackMap(const vector<Token> &token)
{
    // map should contain all the special stacks of the program
    map<string, unique_ptr<StackBase>> m;
    m.insert(pair<string, unique_ptr<StackBase>>("io", make_unique<Console>()));
    m.insert(pair<string, unique_ptr<StackBase>>("add", make_unique<Add>()));
    m.insert(pair<string, unique_ptr<StackBase>>("and", make_unique<And>()));
    m.insert(pair<string, unique_ptr<StackBase>>("or", make_unique<Or>()));
    m.insert(pair<string, unique_ptr<StackBase>>("rsft", make_unique<RightShift>()));
    m.insert(pair<string, unique_ptr<StackBase>>("lsft", make_unique<LeftShift>()));
    m.insert(pair<string, unique_ptr<StackBase>>("inv", make_unique<Invert>()));
    m.insert(pair<string, unique_ptr<StackBase>>("int", make_unique<Integer>()));
    m.insert(pair<string, unique_ptr<StackBase>>("bin", make_unique<Bin>()));

    // inserting user defined stacks to the map
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
    // returning the user generated map
    return m;
}