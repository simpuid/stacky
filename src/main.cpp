#include <iostream>
#include <string>
#include <vector>
#include <filehandle.hpp>
#include <scanner.hpp>
#include <console.hpp>
#include <checks.hpp>
#include <parser.hpp>
#include <graph.hpp>
#include <visitor.hpp>
#include <memory.hpp>
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
        map<string, unique_ptr<Stack>> stackmap = generateStackMap(token);
        vector<unique_ptr<Statement>> v = parse(token, stackmap);
        Printer p;
        for (auto &t : v)
        {
            t->accept(p);
        }
        Runner r;
        for (auto &t : v)
        {
            t->accept(r);
        }
    }
    catch (const std::exception &e)
    {
        cerr << "\nTerminated!" << endl;
        return -1;
    }
    return 0;
}