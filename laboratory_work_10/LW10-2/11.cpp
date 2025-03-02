#include <iostream>
#include <string>
#include <sstream>


using namespace std;


double Frec(double x, int n)
{

    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return x;
    }

    double res = x * x / n / (n - 1);

    return res * Frec(x, n - 2);
}

void Task1()
{
    double x;
    int n;

    string input;

    cout << "Введите x: ";
    while (true)
    {
        getline(cin, input);
        bool validInput = true;
        for (char c : input)
        {
            if (!isdigit(c) && c != '.' && c != '-')
            {
                validInput = false;
                break;
            }
        }

        if (validInput)
        {
            stringstream ss(input);
            if (ss >> x)
            {
                break;
            }
        }
        cout << "Ошибка, введите число для x: ";
    }

    while (true)
    {
        cout << "Введите n: ";
        getline(cin, input);
        bool validInput = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                validInput = false;
                break;
            }
        }

        if (validInput)
        {
            stringstream ss(input);
            if (ss >> n && n >= 0)
            {
                break;
            }
        }
        cout << "Ошибка, введите положительное число для n: ";
    }

    cout << "Результат рекурсивной функции: " << Frec(x, n) << endl;
}

int main()
{
    setlocale(LC_ALL, "");

    Task1();

}