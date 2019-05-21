#include <checks.hpp>
#include <sstream>
#include <console.hpp>
using namespace std;

void checkBrackets(const vector<Token>& token)
{
    std::vector<Token> b;
    for (Token t : token)
    {
        if (t.type == Type::EmptyStart || t.type == Type::EmptyEnd || t.type == Type::ZeroStart || t.type == Type::ZeroEnd)
        {
            if ((b.size() > 0) && ((t.type == Type::ZeroEnd && b[b.size()-1].type == Type::ZeroStart) || (t.type == Type::EmptyEnd && b[b.size()-1].type == Type::EmptyStart)))
            {
                b.pop_back();
            }
            else
            {
                b.push_back(t);
            }
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
    {
        error("Unexpected starting token.It should be either a stack or a number");
    }
}