#include <iostream>
#include <string>
#include <vector>
using namespace std;
string pass = "abcd123";

struct Bikes
{
    std::vector<string> brand = {"Yamaha", "Kawasaki", "Honda", "BMW"};
    std::vector<std::vector<string>> model = {{"YZF-R3", "YZF-R1"}, {"Ninja 400", "ZX-10R"}, {"CBR600RR", "CBR1000RR"}, {"S1000RR", "M1000RR"}};
    std::vector<std::vector<string>> speed = {{"181 km/h", "284 km/h"}, {"169 km/h", "299 km/h"}, {"251 km/h", "346 km/h"}, {"303 km/h", "314 km/h"}};
    std::vector<std::vector<int>> price = {{6000, 18000}, {5000, 15000}, {10000, 17000}, {35000, 16000}};
    std::vector<std::vector<int>> year = {{2024, 2018}, {2023, 2004}, {2005, 2006}, {2009, 2025}};
    std::vector<std::vector<int>> stock = {{5, 3}, {7, 2}, {2, 4}, {3, 1}};
} bike;

struct customer_info
{
    std::vector<string> name;
    std::vector<int> age;
} customer;

struct purchase
{
    std::vector<string> brand_owner;
    std::vector<string> model_owner;
} type;

void print_brand(int n)
{
    for (int i = 0; i < bike.brand.size(); ++i)
    {
        cout << "Enter " << n << " to select " << bike.brand[i] << '\n';
        n++;
    }
}

void print_model(int n, int brand)
{
    for (int i = 0; i < bike.model[brand - 1].size(); ++i)
    {
        cout << "Enter " << n << " to select " << bike.model[brand - 1][i] << '\n';
        n++;
    }
}

void select(int brand)
{
    print_model(1, brand);
    int model;
    std::cin >> model;
    brand--;
    model--;
    if (bike.stock[brand][model] > 0)
    {
        cout << "'This model has a top speed of " << bike.speed[brand][model] << ", was made in year " << bike.year[brand][model] << " and costs " << bike.price[brand][model] << " euros. Do you wish to proceed to payment?" << '\n';
        string choice;
        std::cin >> choice;

        if (choice == "yes")
        {
            int amount;
            cout << "Amount: ";
            std::cin >> amount;
            if (bike.stock[brand][model] - amount >= 0)
            {
                cout << "Name of customer: ";
                std::string name;
                std::cin >> name;
                customer.name.push_back(name);

                cout << "Age: ";
                int age;
                std::cin >> age;
                customer.age.push_back(age);
                std::string motor_type = bike.model[brand][model];
                type.model_owner.push_back(motor_type);
                bike.stock[brand][model] -= amount;
                type.brand_owner.push_back(bike.brand[brand]);
            }
            else
                cout << "Not enough in stock!" << '\n';
        }
        return;
    }
    else
        cout << "Out of stock!" << '\n';

    return;
}

void quick(int st, int dr, std::vector<int> &a)
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

void sort_price(std::vector<int> a)
{
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < bike.price.size(); ++j)
            for (int k = 0; k < bike.price[j].size(); ++k)
                if (a[i] == bike.price[j][k])
                    cout << bike.model[j][k] << " " << bike.price[j][k] << " euros" << '\n';
}

void print_info(int brand, int model)
{
    cout << "Our " << bike.brand[brand] << " " << bike.model[brand][model] << " was made in " << bike.year[brand][model] << ", has a top speed of " << bike.speed[brand][model] << " and costs " << bike.price[brand][model] << " euros" << '\n';
}

void customer_info(int nr_client)
{
    if (nr_client != 0)
        for (int i = 0; i < nr_client; ++i)
            cout << customer.name[i] << " is " << customer.age[i] << " years old and rides a " << type.brand_owner[i] << " " << type.model_owner[i] << '\n';
    else
        cout << "No existing clients!" << '\n';
}

void add_stock(int brand, int model)
{
    int s;
    cout << "Amount: ";
    std::cin >> s;
    bike.stock[brand][model] += s;
}

void sort_list(std::vector<int> &a)
{
    for (int i = 0; i < bike.price.size(); ++i)
        for (int j = 0; j < bike.price[i].size(); ++j)
            a.push_back(bike.price[i][j]);
}

void add_existing_brand(int brand, Bikes &bike)
{
    string model, speed;

    cout << "Model: " << '\n';
    cin.ignore();
    getline(cin, model);
    bike.model[brand - 1].push_back(model);

    cout << "Top speed: " << '\n';
    getline(cin, speed);
    bike.speed[brand - 1].push_back(speed);

    int year, stock, price;

    cout << "Year: " << '\n';
    cin >> year;
    bike.year[brand - 1].push_back(year);

    cout << "Stock: " << '\n';
    cin >> stock;
    bike.stock[brand - 1].push_back(stock);

    cout << "Price: " << '\n';
    cin >> price;
    bike.price[brand - 1].push_back(price);
}

void add_new_brand(Bikes &bike)
{
    cout << "Brand: " << '\n';
    string brand, model, speed;
    cin >> brand;
    bike.brand.push_back(brand);

    std::vector<string> temp;
    cout << "Model: " << '\n';
    cin.ignore();
    getline(cin, model);
    temp.push_back(model);
    bike.model.push_back(temp);

    temp.clear();
    cout << "Top speed: " << '\n';
    getline(cin, speed);
    temp.push_back(speed);
    bike.speed.push_back(temp);

    int year, stock, price;
    std::vector<int> temp1;
    cout << "Year: " << '\n';
    cin >> year;
    temp1.push_back(year);
    bike.year.push_back(temp1);

    temp1.clear();
    cout << "Stock: " << '\n';
    cin >> stock;
    temp1.push_back(stock);
    bike.stock.push_back(temp1);

    temp1.clear();
    cout << "Price: " << '\n';
    cin >> price;
    temp1.push_back(price);
    bike.price.push_back(temp1);
    
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
                int brand;
                cin >> brand;
                select(brand);
            }
            else if (command == 2)
            {

                int brand, model;
                print_brand(1);
                cin >> brand;
                print_model(1, brand);
                cin >> model;
                model--, brand--;
                print_info(brand, model);
            }
            else if (command == 3)
            {
                std::vector<int> a;
                sort_list(a);
                quick(0, a.size() - 1, a);
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
                     << "4. Add new bike" << '\n'
                     << "5. Exit" << '\n';
                cin >> command;
                if (command == 1)
                    customer_info(customer.name.size());

                else if (command == 2)
                {
                    int brand, model;
                    print_brand(1);
                    cin >> brand;
                    print_model(1, brand);
                    cin >> model;
                    model--, brand--;
                    add_stock(brand, model);
                }
                else if (command == 3)
                {
                    int brand, model;
                    print_brand(1);
                    cin >> brand;
                    print_model(1, brand);
                    cin >> model;
                    model--, brand--;
                    cout << bike.stock[brand][model] << '\n';
                }
                else if (command == 4)
                {
                    print_brand(1);
                    cout << "Enter " << bike.brand.size() + 1 << " to add a new brand" << '\n';
                    int brand;
                    cin >> brand;
                    if (brand <= bike.brand.size())
                        add_existing_brand(brand, bike);
                    else
                        add_new_brand(bike);
                }

                else if (command == 5)
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
