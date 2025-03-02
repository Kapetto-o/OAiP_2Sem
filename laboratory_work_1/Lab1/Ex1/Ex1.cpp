#include <iostream>
using namespace std;

double f1(double x) {
    return x * x * x + x - 4;
}

double f2(double x) {
    return 1 - x * x;
}

double dichotomy(double (*f)(double), double a, double b, double e) {
    double c;
    while ((b - a) / 2 > e) {
        c = (a + b) / 2;
        if ((*f)(c) == 0.0)
            break;
        else if ((*f)(a) * (*f)(c) < 0)
            b = c;
        else
            a = c;
    }
    return (a + b) / 2;
}

int main() {
    setlocale(LC_ALL, "RU");
    double a, b, e = 0.001;

     cout << "Введите интервал для первого уравнения x^3+x-4: ";
     cin >> a >> b;
     cout << "Корень первого уравнения: " << dichotomy(f1, a, b, e) <<  endl;

     cout << "Введите интервал для второго уравнения 1-x^2: ";
     cin >> a >> b;
     cout << "Корень второго уравнения: " << dichotomy(f2, a, b, e) <<  endl;

    return 0;
}