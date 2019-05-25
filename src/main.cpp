#include <string>
#include <vector>
#include <scanner.hpp>
#include <error.hpp>
#include <parser.hpp>
#include <graph.hpp>
#include <visitor.hpp>
#include <memory.hpp>
#include <fstream>
#include <interpreter.hpp>

using namespace std;

// Extracts the file name from command arguments
string getName(int argCount, char *args[])
{
    if (argCount < 2)
        error("less number of arguments");
    return string(args[1]);
}

// Extract the code from file
string getCode(const string& name)
{
    ifstream file(name);
    if (!file)
        error("can't read file: " + name);
    return string((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
}

// Main
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
        // Terminates the program when exception is caught
        return -1;
    }
    return 0;
}