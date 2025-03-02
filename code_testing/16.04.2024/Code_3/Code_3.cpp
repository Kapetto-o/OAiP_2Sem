#include <iostream>
using namespace std;

// Определение структуры "node" для элементов списка
struct node
{
	int elem; // Элемент списка
	node* sled; // Указатель на следующий элемент
	node* pred; // Указатель на предыдущий элемент
};

// Определение класса "Spisok" для работы со списком
class Spisok
{
private:
	node* nsp; // Указатель на начало списка
public:
	Spisok() { nsp = NULL; } // Конструктор класса
	void BuiltRing(); // Метод для создания кольцевого списка
	void VyvodLeftRight(); // Метод для вывода списка слева направо
	void VyvodRightLeft(); // Метод для вывода списка справа налево
	void InsAfter(node*, int); // Метод для вставки элемента после указанного
	void InsBefore(node*, int); // Метод для вставки элемента перед указанным
	void Delete(node*); // Метод для удаления указанного элемента
	void DelAfter(node*); // Метод для удаления элемента после указанного
	node* SearchRing(int); // Метод для поиска элемента в списке
	void Ochistka(); // Метод для очистки списка
};

// Главная функция
void main()
{
	setlocale(LC_ALL, "Rus");
	Spisok A; // Создание объекта класса Spisok
	node* Res; // Указатель для работы с элементами списка
	int el, el1;

	A.BuiltRing(); // Создание кольцевого списка
	cout << "Содержимое кольца по часовой стрелке:\n";
	A.VyvodLeftRight(); // Вывод списка слева направо
	cout << "Содержимое кольца простив часовой стелки:\n";
	A.VyvodRightLeft(); // Вывод списка справа налево
	cout << "Введите элемент звена, после которого осуществляется вставка: ";
	cin >> el;
	cout << "Введите элемент вставляемого звена: ";
	cin >> el1;
	Res = A.SearchRing(el); // Поиск элемента в списке
	if (Res != NULL)
	{
		A.InsAfter(Res, el1); A.VyvodLeftRight(); // Вставка элемента после найденного и вывод списка
	}
	else cout << "Звена с таким элементом в списке нет!\n";

	cout << "Введите элемент звена, перед которым осуществляется вставка: ";
	cin >> el;
	cout << "Введите элемент вставляемого звена: ";
	cin >> el1;
	Res = A.SearchRing(el); // Поиск элемента в списке
	if (Res != NULL) {
		A.InsBefore(Res, el1); A.VyvodLeftRight(); // Вставка элемента перед найденным и вывод списка
	}
	else cout << "Звена с таким элементом в списке нет!\n";

	cout << "Введите элемент звена, который надо удалить: ";
	cin >> el;
	Res = A.SearchRing(el); // Поиск элемента в списке
	if (Res != NULL)
	{
		A.Delete(Res); A.VyvodLeftRight(); // Удаление найденного элемента и вывод списка
	}
	else cout << "Звена с таким элементом в списке нет!\n";
	cout << "Введите элемент звена, после которого осуществляется удаление: ";
	cin >> el;
	Res = A.SearchRing(el); // Поиск элемента в списке
	if (Res != NULL)
	{
		A.DelAfter(Res); A.VyvodLeftRight(); // Удаление элемента после найденного и вывод списка
	}
	else cout << "Звена с таким элементом в списке нет!\n";
	A.Ochistka(); // Очистка списка
	cout << "\n";
	system("PAUSE");
}

// Функция для создания кольцевого списка
void Spisok::BuiltRing()
{
	node* r;
	int el;
	nsp = new(node);

	r = nsp; (*nsp).pred = NULL; (*nsp).sled = NULL;
	cout << "Вводите элементы списка:\n";
	cin >> el;
	while (el != 0)
	{
		(*r).sled = new(node);
		(*((*r).sled)).pred = r; r = (*r).sled;
		(*r).sled = NULL; (*r).elem = el;
		cin >> el;
	}
	if ((*nsp).sled != NULL)
	{
		(*((*nsp).sled)).pred = r; (*r).sled = (*nsp).sled;
	}
	else cout << "Кольцевой список пуст!\n";
}

// Функция для вывода списка слева направо
void Spisok::VyvodLeftRight()
{
	node* r;
	cout << "Кольцевой список: ";
	if ((*nsp).sled != NULL)
	{
		cout << (*((*nsp).sled)).elem << " ";
		r = (*((*nsp).sled)).sled;
		while (r != (*nsp).sled)
		{
			cout << (*r).elem << " "; r = (*r).sled;
		}
		cout << endl;
	}
	else cout << "пуст!";
}

// Функция для вывода списка справа налево
void Spisok::VyvodRightLeft()
{
	node* r;
	cout << "Кольцевой список: ";
	if ((*nsp).sled != NULL)
	{
		cout << (*((*((*nsp).sled)).pred)).elem << " ";
		r = (*((*((*nsp).sled)).pred)).pred;
		while (r != (*((*nsp).sled)).pred)
		{
			cout << (*r).elem << " "; r = (*r).pred;
		}
		cout << endl;
	}
	else cout << "пуст!";
}

// Функция для поиска элемента в списке
node* Spisok::SearchRing(int el)
{
	node* q;
	node* p;
	node* Res;

	Res = NULL;
	p = nsp;
	if ((*((*p).sled)).elem == el) Res = (*p).sled;
	else
	{
		q = (*((*p).sled)).sled;
		while (q != (*p).sled && Res == NULL)
			if ((*q).elem == el) Res = q;
			else q = (*q).sled;
	}
	return Res;
}

// Функция для вставки элемента после указанного
void Spisok::InsAfter(node* Res, int el)
{
	node* q;

	q = new(node);
	(*q).elem = el; (*q).sled = (*Res).sled;
	(*q).pred = (*(*Res).sled).pred;
	(*(*Res).sled).pred = q; (*Res).sled = q;
}

// Функция для вставки элемента перед указанным
void Spisok::InsBefore(node* Res, int el)
{
	node* q;
	q = new(node);
	(*q).elem = el;
	(*q).sled = (*(*Res).pred).sled; (*q).pred = (*Res).pred;
	(*(*Res).pred).sled = q; (*Res).pred = q;
	if (Res == (*nsp).sled) (*nsp).sled = q;
}

// Функция для удаления указанного элемента
void Spisok::Delete(node* Res)
{
	if ((*Res).sled == Res)
	{
		(*nsp).sled = NULL;
		delete Res;
	}
	else
	{
		(*(*Res).sled).pred = (*Res).pred;
		(*(*Res).pred).sled = (*Res).sled;
		if ((*nsp).sled == Res)
			(*nsp).sled = (*Res).sled;
		delete Res;
	}
}

// Функция для удаления элемента после указанного
void Spisok::DelAfter(node* Res)
{
	node* q;

	if ((*Res).sled == Res)
	{
		(*nsp).sled = NULL;
		delete Res;
	}
	else
	{
		q = (*Res).sled;
		(*(*(*Res).sled).sled).pred = (*(*Res).sled).pred;
		(*Res).sled = (*(*Res).sled).sled;
		if ((*(*nsp).sled).pred == Res)
			(*nsp).sled = (*Res).sled;
		delete q;
	}
}

// Функция для очистки списка
void Spisok::Ochistka()
{
	node* q, * q1;
	q = (*((*nsp).sled)).sled;
	q1 = (*q).sled;
	while (q1 != (*((*nsp).sled)).sled)
	{
		delete q; q = q1; q1 = (*q1).sled;
	}
	delete q;
	delete nsp;
}