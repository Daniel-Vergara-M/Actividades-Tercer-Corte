#include "../methods.h"
#include <stack>
#include <string>
/*
Realizar un programa que le permita al usuario crear una lista de
llamadas telefónicas recientes. (Stack).
Se muestre la lista de llamadas desde la más reciente a la más antigua.
*/

using namespace std;

struct Call
{
    string number;
    string time;
    Call(string number, string time) : number(number), time(time) {}
};

class RecentCalls
{

private:
    stack<Call *> calls;

public:
    RecentCalls() : calls(){};
    ~RecentCalls()
    {
        while (!calls.empty())
        {
            calls.pop();
        }
    }

    /**
     * Adds a call to the collection.
     *
     * @param call A pointer to the Call object to be added.
     */
    void addCall(Call *call)
    {
        calls.push(call);
    }

    /**
     * Removes the most recent call from the collection.
     */
    void removeCall()
    {
        if (!calls.empty())
        {
            calls.pop();
        }
    }

    Call *getCall()
    {
        if (!calls.empty())
        {
            return calls.top();
        }
        return nullptr;
    }

    void showCalls()
    {
        if (calls.empty())
        {
            print(RED + "[!] No calls to show" + CLEAR);
            return;
        }
        int i = 1;
        stack<Call *> temp = calls;
        while (!temp.empty())
        {
            Call *call = temp.top();
            print("Call " + to_string(i) + ":");
            print("  Number: " + call->number);
            print("  Time: " + call->time);
            temp.pop();
            i++;
        }
    }

    void showByTime()
    {
        if (calls.empty())
        {
            print(RED + "[!] No calls to show" + CLEAR);
            return;
        }
        stack<Call *> temp = calls;
    }

    int size()
    {
        return calls.size();
    }

    void run()
    {
        int option;
        do
        {
            print("1. Add call");
            print("2. Remove call");
            print("3. Show calls");
            print("4. Show calls by time");
            print("5. Exit");
            option = input<int>("Option: ");
            switch (option)
            {
            case 1:
            {
                system("cls");
                string number = input<string>("Number: ");
                string date = input<string>("Date: ");
                string time = input<string>("Time: ");
                addCall(new Call(number, time));
                break;
            }
            case 2:
                system("cls");
                removeCall();
                break;
            case 3:
                system("cls");
                showCalls();
                break;
            case 4:
                system("cls");
                showByTime();
                break;
            case 5:
                break;
            default:
                system("cls");
                print(RED + "[!] Invalid option" + CLEAR);
                break;
            }
        } while (option != 5);
    }

    void clear()
    {
        while (!calls.empty())
        {
            calls.pop();
        }
    }
};

int main()
{

    RecentCalls recentCalls = RecentCalls();
    recentCalls.run();
    recentCalls.clear();
    return 0;
}