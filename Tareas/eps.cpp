#include <iostream>
#include <string>
#include <queue>

using namespace std;

class User
{
public:
    string document;
    double hours;
    User(string doc) : document(doc) {}
};

class EPS
{
private:
    queue<User *> users;
    int pendingAppoint = 0;
    double parkingFee = 5.0;

public:
    void requestAppointment(User *p)
    {
        users.push(p);
        pendingAppoint++;
        cout << "Requested appointment for patient with document: " << p->document << endl;
    }

    void payParking(User *p)
    {
        double total = p->hours * parkingFee;
        cout << "The parking fee for " << p->hours << " hours is: $" << total << endl;
    }

    void mostrarCitasPendientes()
    {
        cout << "There's " << pendingAppoint << " pending appointments" << endl;
    }
};

int main()
{
    EPS eps;
    int option;
    while (option != 4) {
        cout << "1. Request appointment" << endl;
        cout << "2. Pay parking" << endl;
        cout << "3. Show pending appointments" << endl;
        cout << "4. Exit" << endl;
        cin >> option;
        if (option == 1) {
            string doc;
            cout << "Enter document: ";
            cin >> doc;
            User *user = new User(doc);
            eps.requestAppointment(user);
        } else if (option == 2) {
            string doc;
            cout << "Enter document: ";
            cin >> doc;
            User *user = new User(doc);
            eps.payParking(user);
        } else if (option == 3) {
            eps.mostrarCitasPendientes();
        } else if (option == 4) {
            break;
        } else {
            cout << "Invalid option" << endl;
        }
    }
    return 0;
}