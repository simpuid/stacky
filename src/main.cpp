#include <string>
#include <vector>
#include <scanner.hpp>
#include <console.hpp>
#include <parser.hpp>
#include <graph.hpp>
#include <visitor.hpp>
#include <memory.hpp>
#include <fstream>
#include <interpreter.hpp>

using namespace std;

string getName(int argCount, char *args[])
{
    if (argCount < 2)
        error("less number of arguments");
    return string(args[1]);
}

string getCode(const string& name)
{
    ifstream file(name);
    if (!file)
        error("can't read file: " + name);
    return string((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
}

int main(int argCount, char *args[])
{
    try
    {
        string name = getName(argCount, args);
        string code = getCode(name);
        vector<Token> token = scan(code);
        map<string, unique_ptr<StackBase>> stackmap = generateStackMap(token);
        vector<unique_ptr<Statement>> v = parse(token, stackmap);
        
        Interpreter i(v);
    }
    catch (const std::exception &e)
    {
        return -1;
    }
    return 0;
}