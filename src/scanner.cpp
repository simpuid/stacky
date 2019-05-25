#include <scanner.hpp>
#include <sstream>
#include <map>
#include <console.hpp>
using namespace std;

static map<char, Type> lookup{{'>', Type::Move}, {'+', Type::Copy}, {'[', Type::ZeroStart}, {']', Type::ZeroEnd}, {'{', Type::EmptyStart}, {'}', Type::EmptyEnd}};

vector<Token> scan(const string &code)
{
    int line{1}, column{1}, pointer{0}, end{(int)code.length()};
    stringstream ss,msg;
    msg << "unexpected character";
    bool err = false;
    vector<Token> tokens;
    auto clear = [&]() {
        stringstream().swap(ss);
    };
    auto addToken = [&](Type type) {
        string value = ss.str();
        tokens.push_back(Token{type, value, line, column - (int)value.length() + 1});
        clear();
    };
    auto isAlphabet = [&](int i) -> bool {
        return (i >= 0 && i < end) && ((code[i] >= 'a' && code[i] <= 'z') || (code[i] >= 'A' && code[i] <= 'Z'));
    };
    auto isNumber = [&](int i) -> bool {
        return (i >= 0 && i < end) && (code[i] >= '0' && code[i] <= '9');
    };
    while (pointer < end)
    {
        ss << code[pointer];
        if (isAlphabet(pointer) && !isAlphabet(pointer + 1))
            addToken(Type::Stack);
        else if (isNumber(pointer) && !isNumber(pointer + 1))
            addToken(Type::Number);
        else if (!isNumber(pointer) && !isAlphabet(pointer))
        {
            auto iter = lookup.find(code[pointer]);
            if (iter != lookup.end())
                addToken(iter->second);
            else if (code[pointer] == '\n')
            {
                line++;
                column = 0;
            }
            else if (code[pointer] != ' ' && code[pointer] != '\t')
            {
                msg << '\n' << code[pointer] << " at line:" << line << " column:" << column;
                err = true;
            }
            clear();
        }
        column++;
        pointer++;
    }
    if (err)
        error(msg.str());
    return tokens;
}