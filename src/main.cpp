#include <iostream>
#include <string>
#include <vector>
#include <filehandle.hpp>
#include <scanner.hpp>
#include <console.hpp>
#include <checks.hpp>
#include <parser.hpp>
#include <graph.hpp>
using namespace std;

int main(int argCount, char *args[])
{
    try
    {
        string name = getName(argCount, args);
        string code = getCode(name);
        vector<Token> token = scan(code);
        checkBrackets(token);
        checkStart(token);
        vector<unique_ptr<Statement>> v = parse(token);
        Printer p;
        for (auto &t : v)
        {
            accept(t.get(),p);
        }
    }
    catch (const std::exception &e)
    {
        cerr << "\nTerminated!" << endl;
        return -1;
    }
    return 0;
}