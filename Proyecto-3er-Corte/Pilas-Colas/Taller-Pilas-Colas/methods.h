#include <iostream>

using namespace std;

const string RED = "\033[31m";
const string CLEAR = "\033[0m";

void print(string text)
{
    cout << text << endl;
}

template <class T>
T input(string text)
{
    T value;
    cout << text;
    cin >> value;
    return value;
}