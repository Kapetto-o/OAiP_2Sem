﻿#include <iostream>//libraries
#include <fstream>
#include <cctype>
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;
struct Address
{
	char name[NAME_SIZE];
	char city[CITY_SIZE];
	Address* next;
	Address* prev;
};
//-----------------------------------------------------------
int menu(void)
{
	char s[80]; int c;
	cout << endl;
	cout << "1. Ввод имени" << endl;
	cout << "2. Удаление элемента по имени" << endl;
	cout << "3. Вывод на экран" << endl;
	cout << "4. Поиск" << endl;
	cout << "5. Удаление элемента по номеру" << endl;
	cout << "6. Удаление удаление всех элементов по имени" << endl;
	cout << "7. Выход" << endl;
	cout << endl;
	do {
		cout << "Ваш выбор: ";
		cin.sync();
		gets_s(s);
		cout << endl;
		c = atoi(s);
	} while (c < 0 || c > 7);
	return c;
}
//-----------------------------------------------------------
void insert(Address* e, Address** phead, Address** plast) //Добавление в конец списка
{
	Address* p = *plast;
	if (*plast == NULL)
	{
		e->next = NULL;
		e->prev = NULL;
		*plast = e;
		*phead = e;
		return;
	}
	else
	{
		p->next = e;
		e->next = NULL;
		e->prev = p;
		*plast = e;
	}
}

Address* setElement() // Создание элемента и ввод его значений с клавиатуры
{
	Address* temp = new Address();
	if (!temp)
	{
		cerr << "Ошибка выделения памяти";
		return NULL;
	}

	bool validInput = false;
	bool validCityInput = false;
	while (!validInput) {
		cout << "Введите имя: ";
		cin.getline(temp->name, NAME_SIZE - 1, '\n');
		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();

		if (isupper(temp->name[0])) {
			validInput = true;
		}
		else {
			cout << "Первая буква имени должна быть заглавной. Попробуйте снова." << endl;
		}
	}

	while (!validCityInput) {
		cout << "Введите город: ";
		cin.getline(temp->city, CITY_SIZE - 1, '\n');
		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();

		if (isupper(temp->city[0])) {
			validCityInput = true;
		}
		else {
			cout << "Первая буква города должна быть заглавной. Попробуйте снова." << endl;
		}
	}

	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

void outputList(Address** phead, Address** plast) //Вывод списка на экран
{
	Address* t = *phead;
	while (t)
	{
		cout << t->name << ' ' << t->city << endl;
		t = t->next;
	}
	cout << "" << endl;
}

void find(char name[NAME_SIZE], Address** phead) {
	Address* t = *phead;
	bool found = false;

	while (t) {
		if (!strcmp(name, t->name)) {
			cout << t->name << ' ' << t->city << endl;
			found = true;
		}
		t = t->next;
	}

	if (!found) {
		cerr << "Элементы с именем " << name << " не найдены" << endl;
	}
}

//-----------------------------------------------------------
void deletX(char name[NAME_SIZE], Address** phead, Address** plast) // Удаление имени
{
	struct Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name)) break;
		t = t->next;
	}
	if (!t)
		cerr << "Имя не найдено" << endl;
	else
	{
		if (*phead == t)
		{
			*phead = t->next;
			if (*phead)
				(*phead)->prev = NULL;
			else
				*plast = NULL;
		}
		else
		{
			t->prev->next = t->next;
			if (t != *plast)
				t->next->prev = t->prev;
			else
				*plast = t->prev;
		}
		delete t;
		cout << "Элемент удален" << endl;
	}
}
void deleteByNumber(int pos, Address** phead, Address** plast) {
	if (pos < 0) {
		cout << "Некорректный номер элемента" << endl;
		return;
	}

	Address* t = *phead;
	int current_position = 0;

	while (t) {
		if (current_position == pos) break;
		t = t->next;
		current_position++;
	}

	if (!t) {
		cout << "Элемент с номером " << pos + 1 << " не найден" << endl;
		return;
	}

	if (*phead == t) {
		*phead = t->next;
		if (*phead)
			(*phead)->prev = NULL;
		else
			*plast = NULL;
	}
	else {
		t->prev->next = t->next;
		if (t->next)
			t->next->prev = t->prev;
		else
			*plast = t->prev;
	}

	delete t;
	cout << "Элемент удален" << endl;
}

void deleteAllByName(char name[NAME_SIZE], Address** phead, Address** plast) {
	Address* t = *phead;
	Address* next;

	while (t) {
		next = t->next;
		if (!strcmp(name, t->name)) {
			if (*phead == t) {
				*phead = t->next;
				if (*phead)
					(*phead)->prev = NULL;
				else
					*plast = NULL;
			}
			else {
				t->prev->next = t->next;
				if (t->next)
					t->next->prev = t->prev;
				else
					*plast = t->prev;
			}
			delete t;
		}
		t = next;
	}

	cout << "Все элементы с именем " << name << " удалены" << endl;
}


//-----------------------------------------------------------
int main(void)
{
	Address* head = NULL;
	Address* last = NULL;
	setlocale(LC_CTYPE, "Rus");
	while (true)
	{
		switch (menu())
		{
		case 1: insert(setElement(), &head, &last);
			break;
		case 2: {
			char dname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(dname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			deletX(dname, &head, &last);
		}
			  break;
		case 3: outputList(&head, &last);
			break;
		case 4: {
			char fname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(fname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			find(fname, &head);
		}
			  break;
		case 5:int X;
			cout << "Введите номер элемента, который хотите удалить: ";
			cin >> X;
			deleteByNumber(X - 1, &head, &last);
			break;
		case 6: {
			char nameToDelete[NAME_SIZE];
			cout << "Введите имя, по которому хотите удалить все элементы: ";
			cin.getline(nameToDelete, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			deleteAllByName(nameToDelete, &head, &last);
		}
			  break;

		case 7:exit(0); break;
			//default: exit(1);
		}
	}
	return 0;
}