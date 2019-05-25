#include <console.hpp>
#include <iostream>
#include <sstream>
using namespace std;

void error(string msg)
{
    stringstream ss;
    ss << "\nError: " << msg;
    cerr << ss.str();
    close();
}

void close()
{
    throw exception();
}