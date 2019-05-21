#include <filehandle.hpp>
#include <console.hpp>
#include <fstream>
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