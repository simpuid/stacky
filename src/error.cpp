#include <error.hpp>
#include <iostream>
#include <sstream>
using namespace std;

// Prints the message as error
void error(string msg)
{
    // form a string and prints it
    stringstream ss;
    ss << "\nError: " << msg;
    cerr << ss.str();
    // terminates the program
    throw exception();
}