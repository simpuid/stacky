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

void log(string msg)
{
    stringstream ss;
    ss << "\nLog: " << msg;
    clog << ss.str();
}

void warn(string msg)
{
    stringstream ss;
    ss << "\nWarning: " << msg;
    cout << ss.str();
}

void close()
{
    throw exception();
}