#include <iostream>
#include <cstring>
using namespace std;
int nr_client = 0;
string pass = "abcd123";
struct Bikes
{
    string brand[100] = {"Yamaha", "Kawasaki", "Honda", "BMW"};
    string model[100] = {"YZF-R3", "YZF-R1", "Ninja 400", "ZX-10R", "CBR600RR", "CBR1000RR", "S1000RR", "M1000RR"};
    string speed[100] = {"181 km/h", "284 km/h", "169 km/h", "299 km/h", "251 km/h", "346 km/h", "303 km/h", "314 km/h"};
    int price[100] = {6000, 18000, 5000, 15000, 10000, 17000, 35000, 16000};
    int year[100] = {2024, 2018, 2023, 2004, 2005, 2006, 2009, 2025};
    int stock[100] = {5, 3, 7, 2, 2, 4, 3, 1};
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
        if (bike.stock[input] > 0)
        {
            cout << "'This model has a top speed of " << bike.speed[input] << ", was made in year " << bike.year[input] << " and costs " << bike.price[input] << " euros. Do you wish to proceed to payment?" << '\n';
            string choice;
            cin >> choice;
            if (choice == "yes")
            {
                int amount;
                cout << "Amount: ";
                cin >> amount;
                if (bike.stock[input] - amount >= 0)
                {
                    cout << "Name of customer: ";
                    cin >> customer.name[nr_client];
                    cout << "Age: ";
                    cin >> customer.age[nr_client];
                    type.model_owner[nr_client] = bike.model[input];
                    bike.stock[input] -= amount;
                    nr_client++;
                }
                else
                    cout << "Not enough in stock!" << '\n';
            }
        }
        else
            cout << "Out of stock!" << '\n';
        return;
    }

    else if (m == 2)
    {
        if (bike.stock[input + 1] > 0)
        {
            cout << "'This model has a top speed of " << bike.speed[input + 1] << ", was made in year " << bike.year[input + 1] << " and costs " << bike.price[input + 1] << " euros. Do you wish to proceed to payment?" << '\n';
            string choice;
            cin >> choice;
            if (choice == "yes")
            {
                int amount;
                cout << "Amount: ";
                cin >> amount;
                if (bike.stock[input + 1] - amount >= 0)
                {
                    cout << "Name of customer: ";
                    cin >> customer.name[nr_client];
                    cout << "Age: ";
                    cin >> customer.age[nr_client];
                    type.model_owner[nr_client] = bike.model[input + 1];
                    bike.stock[input + 1] -= amount;
                    nr_client++;
                }
                else
                    cout << "Not enough in stock!" << '\n';
            }
        }
        else
            cout << "Out of stock!" << '\n';
        return;
    }
    else
        cout << "Nonexistent command!" << '\n';
    return;
}

void quick(int st, int dr, int a[])
{

    int pivot = a[(st + dr) / 2];
    int i = st, j = dr;
    while (i <= j)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
        {
            int aux = a[i];
            a[i] = a[j];
            a[j] = aux;
            i++;
            j--;
        }
    }
    if (st < j)
        quick(st, j, a);
    if (i < dr)
        quick(i, dr, a);
}

void print_brand(int n)
{
    for (int i = 0; i < 4; ++i)
    {
        cout << "Enter " << n << " to select " << bike.brand[i] << '\n';
        n++;
    }
}

void print_model(int n, int brand)
{
    for (int i = 0; i < 2; ++i)
    {
        cout << "Enter " << n << " to select " << bike.model[brand * 2 - 2 + i] << '\n';
        n++;
    }
}

void sort_price(int a[])
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (a[i] == bike.price[j])
                cout << bike.model[j] << " " << bike.price[j] << " euros" << '\n';
}

void print_info(int brand, int nr)
{
    cout << "Our " << bike.brand[brand - 1] << " " << bike.model[nr] << " was made in " << bike.year[nr] << ", has a top speed of " << bike.speed[nr] << " and costs " << bike.price[nr] << " euros" << '\n';
}

void customer_info(int nr_client)
{
    if (nr_client != 0)
        for (int i = 0; i < nr_client; ++i)
            cout << customer.name[i] << " is " << customer.age[i] << " years old and rides a " << type.brand_owner[i] << " " << type.model_owner[i] << '\n';
    else
        cout << "No existing clients!" << '\n';
}

void add_stock(int nr)
{
    int s;
    cout << "Amount: ";
    cin >> s;
    bike.stock[nr] += s;
}
void menu()
{
    while (true)
    {
        int choice, n;
        cout << "1. Customer" << '\n'
             << "2. Owner" << '\n';
        cin >> choice;
        if (choice == 1)
        {
            int command;
            cout << "Choose a command:" << '\n'
                 << "1. Buy a motorcycle" << '\n'
                 << "2. Show information about a motorcycle" << '\n'
                 << "3. Sort by price" << '\n'
                 << "4. Exit" << '\n';
            cin >> command;
            if (command == 1)
            {
                print_brand(1);
                int input;
                cin >> input;
                select(input * 2 - 2, nr_client);
                type.brand_owner[nr_client - 1] = bike.brand[input - 1];
            }
            else if (command == 2)
            {

                int brand, model;
                print_brand(1);
                cin >> brand;
                print_model(1, brand);
                cin >> model;
                model--;
                int nr = brand * 2 - 2 + model;
                print_info(brand, nr);
            }
            else if (command == 3)
            {
                int a[101] = {};

                for (int i = 0; i < 8; ++i)
                    a[i] = bike.price[i];

                quick(0, 7, a);
                sort_price(a);
            }

            else if (command == 4)
                return;
        }
        else if (choice == 2)
        {
            string password;
            cout << "Enter password: "; // password is abcd123
            cin >> password;
            if (pass == password)
            {
                int command;
                cout << "Choose a command:" << '\n'
                     << "1. Show client info" << '\n'
                     << "2. Add stock" << '\n'
                     << "3. Show stock" << '\n'
                     << "4. Exit" << '\n';
                cin >> command;
                if (command == 1)
                    customer_info(nr_client);

                else if (command == 2)
                {
                    int brand, model;
                    print_brand(1);
                    cin >> brand;
                    print_model(1, brand);
                    cin >> model;
                    model--;
                    int nr = brand * 2 - 2 + model;
                    add_stock(nr);
                }
                else if (command == 3)
                {
                    int brand, model;
                    print_brand(1);
                    cin >> brand;
                    print_model(1, brand);
                    cin >> model;
                    model--;
                    int nr = brand * 2 - 2 + model;
                    cout << bike.stock[nr] << '\n';
                }
                else if (command == 4)
                    return;
            }
            else
                cout << "Wrong password!" << '\n';
        }
        else
            cout << "Nonexistent command!" << '\n';
    }
    return;
}

int main()
{
    menu();
    return 0;
}
