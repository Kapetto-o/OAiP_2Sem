#include <iostream>
using namespace std;

double cos_sum(int n, int x)
{
	if (n == 0) {
		return 0;
	}
	else {
		return cos(n * x) + cos_sum(n - 1, x);
	}
}

void main()
{
	setlocale(LC_CTYPE, "Rus");
	int x;
	cout << "Введите x для косинуса: ";
	cin >> x;
	int n;
	cout << "Введите лимит: ";
	cin >> n;
	double y = cos_sum(x, n);
	cout << "сумма равна: " << y << endl;
}