#include <iostream>
#include <cstring>
using namespace std;
int nr_client = 0;
struct Bikes
{
    string brand[200] = {"Yamaha", "Kawasaki", "Honda", "BMW"};
    string model[200] = {"YZF-R3", "YZF-R1", "Ninja 400", "ZX-10R", "CBR600RR", "CBR1000RR", "S1000RR", "M1000RR"};
    string speed[200] = {"181 km/h", "284 km/h", "169 km/h", "299 km/h", "251 km/h", "346 km/h", "303 km/h", "314 km/h"};
    int price[200] = {6000, 18000, 5000, 15000, 10000, 17000, 35000, 16000};
    int year[200] = {2024, 2018, 2023, 2004, 2005, 2006, 2009, 2025};
} bike;

struct customer_info
{
    string name[100];
    int age[100];
} customer;

struct purchase
{
    string brand_owner[100];
    string model_owner[100];
} type;

void select(int input, int &nr_client)
{
    cout << "Select a Model: " << '\n'
         << "1." << bike.model[input] << '\n'
         << "2." << bike.model[input + 1];
    int m;
    cin >> m;
    if (m == 1)
    {
        cout << "'This model has a top speed of " << bike.speed[input] << ", was made in year " << bike.year[input] << " and costs " << bike.price[input] << " euros. Do you wish to proceed to payment?";
        string a[100] = {};
        cin >> a[1];
        if (a[1] == "yes")
        {
            cout << "Name of customer: ";
            cin >> customer.name[nr_client];
            cout << "Age: ";
            cin >> customer.age[nr_client];
            type.model_owner[nr_client] = bike.model[input];
            nr_client++;
        }
        return;
    }

    else if (m == 2)
    {
        cout << "'This model has a top speed of " << bike.speed[input + 1] << ", was made in year " << bike.year[input + 1] << " and costs " << bike.price[input + 1] << " euros. Do you wish to proceed to payment?";
        string a[100] = {};
        cin >> a[1];
        if (a[1] == "yes")
        {
            cout << "Name of customer: ";
            cin >> customer.name[nr_client];
            cout << "Age: ";
            cin >> customer.age[nr_client];
            type.model_owner[nr_client] = bike.model[input];
            nr_client++;
        }
        return;
    }
    else
        cout << "Nonexistent command!" << '\n';
    return;
}

void menu()
{
    while (true)
    {
        int command, n;
        cout << "Choose a command:" << '\n'
             << "1. Buy a motorcycle" << '\n'
             << "2. Show customers" << '\n'
             << "3. Show information about a motorcycle" << '\n'
             << "4. Exit";
        cin >> command;
        if (command == 1)
        {
            n = 1;
            for (int i = 0; i < 4; ++i)
            {
                cout << "Enter " << n << " to select " << bike.brand[i] << '\n';
                n++;
            }
            int input;
            cin >> input;
            select(input * 2 - 2, nr_client);
            type.brand_owner[nr_client - 1] = bike.brand[input - 1];
        }
        else if (command == 2)
            if (nr_client != 0)
            {
                for (int i = 0; i < nr_client; ++i)
                    cout << customer.name[i] << " is " << customer.age[i] << " years old and rides a " << type.brand_owner[i] << " " << type.model_owner[i] << '\n';
            }
            else
                cout << "No existing clients!";
        else if (command == 3)
        {
            int brand, model;
            n = 1;
            for (int i = 0; i < 4; ++i)
            {
                cout << "Enter " << n << " to select " << bike.brand[i] << '\n';
                n++;
            }
            cin >> brand;
            int n = 1;
            for (int i = 0; i < 2; ++i)
            {
                cout << "Enter " << n << " to select " << bike.model[brand * 2 - 2 + i] << '\n';
                n++;
            }
            cin >> model;
            model--;
            int nr = brand * 2 - 2 + model;
            cout << "Our " << bike.brand[brand - 1] << " " << bike.model[nr] << " was made in " << bike.year[nr] << ", has a top speed of " << bike.speed[nr] << " and costs " << bike.price[nr] << " euros" << '\n';
        }
        else if (command == 4)
            return;
        else
            cout << "Nonexistent command!";
    }
    return;
}

int main()
{
    menu();
    return 0;
}
