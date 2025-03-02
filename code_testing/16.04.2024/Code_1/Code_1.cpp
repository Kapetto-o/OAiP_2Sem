﻿#include <iostream>
using namespace std;

// Cтруктура звена Висюльки
struct nodeVis
{
	int elem; // Элемент звена
	nodeVis* vniz; // Указатель на следующее звено
};

// Структура звена Гирлянды
struct nodeGir
{
	int elem; // Элемент звена
	nodeVis* vniz; // Указатель на висюльку текущего звена
	nodeGir* sled; // Указатель на следующее звено Гирлянды
};

// Объявление класса для гирлянды и висюльки
class GirVis {
private:
	nodeGir* phead; // Голова гирлянды
	nodeVis* pheadVis; // Голова висюльки
	void VisVyvod(); // Вывод висюльки

public:
	GirVis() { phead = new(nodeGir); } // Конструктор
	~GirVis() { delete phead; } // Деструктор
	nodeVis* VisPostr(); // Создание висюльки
	nodeVis* VisPoisk(int); // Поиск звена в висюльке
	void SetpheadVis(nodeVis* r) { pheadVis = r; } // Установка головы висюльки
	void VisVstav(nodeVis*, int); // Вставка звена в висюльку после заданного звена
	void Vis1Vstav(nodeVis*, int); // Вставка звена в висюльку перед заданным звеном
	void VisUdale(nodeVis*); // Удаление звена в висюльке после заданного звена
	void Vis1Udale(nodeVis*); // Удаление заданного звена в висюльке
	void GirPostr(); // Создание гирлянды
	void GirVyvod(); // Вывод гирлянды
	nodeGir* GirPoisk(int); // Поиск звена в гирлянде
	void OCHISTKA(); // Очистка гирлянды
	void OCHISTKA1(); // Очистка висюльки
};

void main()
{
	setlocale(LC_ALL, "Rus"); // Установка локали для поддержки русского языка
	GirVis A; // Создание объекта гирлянды
	int el, elGir, elVis; // Объявление переменных для элемента, звена гирлянды и звена висюльки
	nodeGir* Res; // Объявление указателя на звено гирлянды
	nodeVis* ResVis; // Объявление указателя на звено висюльки

	A.GirPostr(); // Создание гирлянды
	A.GirVyvod(); // Вывод гирлянды
	cout << "\nВведите элемент звена гирлянды, ";
	cout << "чьи висюльки будем изменять: \n";
	cin >> elGir; // Ввод элемента звена гирлянды
	cout << "\nВведите элемент звена висюльки, после которого ";
	cout << "осуществляется вставка:\n";
	cin >> elVis; // Ввод элемента звена висюльки
	cout << "\nВведите вставляемый элемент:\n";
	cin >> el; // Ввод вставляемого элемента

	Res = A.GirPoisk(elGir); // Поиск звена гирлянды
	if (Res != NULL) // Если звено найдено
	{
		A.SetpheadVis((*Res).vniz); // Установка головы висюльки
		ResVis = A.VisPoisk(elVis); // Поиск звена висюльки
		if (ResVis != NULL) // Если звено найдено
			A.VisVstav(ResVis, el); // Вставка нового звена после найденного
		else cout << "Элемента в висюльке нет!\n"; // Если звено не найдено
	}
	else cout << "Элемента в гирлянде нет!\n"; // Если звено не найдено
	A.GirVyvod(); // Вывод гирлянды

	cout << "\nВведите элемент гирлянды, чью висюльку будем изменять:\n";
	cin >> elGir;
	cout << "Введите элемент висюльки, перед которым осуществляется вставка:\n";
	cin >> elVis;
	cout << "Введите вставляемый элемент:\n";
	cin >> el;

	Res = A.GirPoisk(elGir);
	if (Res != NULL)
	{
		A.SetpheadVis((*Res).vniz);
		ResVis = A.VisPoisk(elVis);
		if (ResVis != NULL);
		A.SetpheadVis((*Res).vniz);
		ResVis = A.VisPoisk(elVis);
		if (ResVis != NULL)
			A.Vis1Vstav(ResVis, el);
		else cout << "Элемента в висюльке нет!\n";
	}
	else cout << "Элемента в гирлянде нет!\n";
	A.GirVyvod();
	cout << "\nВведите элемент гирлянды, чью висюльку будем изменять:\n";
	cin >> elGir;
	cout << "Введите элемент висюльки, после которой нужно удалить:\n";
	cin >> elVis;

	Res = A.GirPoisk(elGir);
	if (Res != NULL)
	{
		A.SetpheadVis((*Res).vniz);
		ResVis = A.VisPoisk(elVis);
		if ((ResVis != NULL) && ((*ResVis).vniz != NULL))
			A.VisUdale(ResVis);
		else cout << "Элемента в висюльке нет!\n";
	}
	else cout << "Элемента в гирлянде нет!\n";
	A.GirVyvod();
	cout << "\nВведите элемент гирлянды, чью висюльку будем изменять:\n";
	cin >> elGir;

	cout << "Введите элемент висюльки, который удаляется:\n";
	cin >> elVis;

	Res = A.GirPoisk(elGir);
	if (Res != NULL)
	{
		A.SetpheadVis((*Res).vniz);
		ResVis = A.VisPoisk(elVis);
		if ((ResVis != NULL) && ((*ResVis).vniz != NULL))
			A.Vis1Udale(ResVis);
		else cout << "Элемента в висюльке нет или он последний!\n";
	}
	else cout << "Элемента в гирлянде нет!\n";
	A.GirVyvod();

	A.OCHISTKA(); // Очистка гирлянды

	cout << "\n";
	system("PAUSE"); // Пауза перед завершением программы
}

void GirVis::OCHISTKA()
{
	nodeGir* q, * q1;
	q = phead; // Начинаем с головы гирлянды
	q1 = (*q).sled; // Следующее звено гирлянды

	while (q1 != NULL) // Пока не достигнем конца гирлянды
	{
		q = q1; // Переходим к следующему звену
		q1 = (*q1).sled; // Обновляем указатель на следующее звено
		pheadVis = (*q).vniz; // Устанавливаем голову висюльки
		OCHISTKA1(); // Очищаем висюльку
		delete q; // Удаляем текущее звено гирлянды
	}
}


void GirVis::OCHISTKA1()
{
	nodeVis* q, * q1;
	q = pheadVis; // Начинаем с головы висюльки
	q1 = (*q).vniz; // Следующее звено висюльки

	while (q1 != NULL) // Пока не достигнем конца висюльки
	{
		q = q1; // Переходим к следующему звену
		q1 = (*q1).vniz; // Обновляем указатель на следующее звено
		delete q; // Удаляем текущее звено висюльки
	}
}

void GirVis::GirPostr()
{
	nodeGir* t; // Объявление указателя на звено гирлянды
	int el; // Объявление переменной для элемента
	t = phead; // Начинаем с головы гирлянды
	(*t).sled = NULL; // Устанавливаем следующее звено гирлянды в NULL
	cout << "Вводите элемент гирлянды:\n";
	cin >> el; // Ввод элемента

	while (el != 0) // Пока введенный элемент не равен 0
	{
		(*t).sled = new(nodeGir); // Создаем новое звено гирлянды
		t = (*t).sled; // Переходим к новому звену
		(*t).elem = el; // Устанавливаем элемент звена
		(*t).sled = NULL; // Устанавливаем следующее звено в NULL
		(*t).vniz = VisPostr(); // Создаем висюльку для текущего звена
		cout << "Вводите элемент гирлянды:\n";
		cin >> el; // Ввод следующего элемента
	}
}

nodeVis* GirVis::VisPostr()
{
	nodeVis* t; // Объявление указателя на звено висюльки
	int el; // Объявление переменной для элемента
	pheadVis = new (nodeVis); // Создание новой висюльки
	t = pheadVis; // Начинаем с головы висюльки
	(*t).vniz = NULL; // Устанавливаем следующее звено висюльки в NULL
	cout << "Вводите элементы звеньев висюльки:\n";
	cin >> el; // Ввод элемента

	while (el != 0) // Пока введенный элемент не равен 0
	{
		(*t).vniz = new(nodeVis); // Создаем новое звено висюльки
		t = (*t).vniz; // Переходим к новому звену
		(*t).elem = el; // Устанавливаем элемент звена
		(*t).vniz = NULL; // Устанавливаем следующее звено в NULL
		cin >> el; // Ввод следующего элемента
	}
	return pheadVis; // Возвращаем голову висюльки
}

void GirVis::GirVyvod()
{
	nodeGir* t; // Объявление указателя на звено гирлянды

	t = phead; // Начинаем с головы гирлянды
	t = (*t).sled; // Переходим к следующему звену
	cout << "Гирлянда: "; // Выводим начальный текст

	while (t != NULL) // Пока не достигнем конца гирлянды
	{
		cout << (*t).elem << " "; // Выводим элемент текущего звена
		pheadVis = (*t).vniz; // Устанавливаем голову висюльки
		VisVyvod(); // Выводим висюльку
		t = (*t).sled; // Переходим к следующему звену
	}
}

nodeGir* GirVis::GirPoisk(int el)
{
	nodeGir* t, * r; // Объявление указателей на звено гирлянды

	r = NULL; // Инициализация указателя r как NULL
	t = phead; // Начинаем с головы гирлянды
	t = (*t).sled; // Переходим к следующему звену

	while (t != NULL && r == NULL) // Пока не достигнем конца гирлянды и не найдем искомый элемент
		if ((*t).elem == el) r = t; // Если элемент текущего звена равен искомому, устанавливаем r на текущее звено
		else t = (*t).sled; // Иначе переходим к следующему звену

	return r; // Возвращаем указатель на найденное звено или NULL, если звено не найдено
}

void GirVis::VisVyvod()
{
	nodeVis* t; // Объявление указателя на звено висюльки

	t = pheadVis; // Начинаем с головы висюльки
	t = (*t).vniz; // Переходим к следующему звену
	cout << "("; // Выводим открывающую скобку

	while (t != NULL) // Пока не достигнем конца висюльки
	{
		cout << (*t).elem << " "; // Выводим элемент текущего звена
		t = (*t).vniz; // Переходим к следующему звену
	}
	cout << ")"; // Выводим закрывающую скобку
}


nodeVis* GirVis::VisPoisk(int el)
{
	nodeVis* t, * r; // Объявление указателей на звено висюльки

	r = NULL; // Инициализация указателя r как NULL
	t = pheadVis; // Начинаем с головы висюльки
	t = (*t).vniz; // Переходим к следующему звену

	while (t != NULL && r == NULL) // Пока не достигнем конца висюльки и не найдем искомый элемент
		if ((*t).elem == el) r = t; // Если элемент текущего звена равен искомому, устанавливаем r на текущее звено
		else t = (*t).vniz; // Иначе переходим к следующему звену

	return r; // Возвращаем указатель на найденное звено или NULL, если звено не найдено
}


void GirVis::VisVstav(nodeVis* r, int el)
{
	nodeVis* q; // Объявление указателя на звено висюльки
	q = new(nodeVis); // Создание нового звена
	(*q).elem = el; // Установка элемента нового звена
	(*q).vniz = (*r).vniz; // Установка следующего звена нового звена как следующее звено заданного звена
	(*r).vniz = q; // Установка следующего звена заданного звена как новое звено
}


void GirVis::Vis1Vstav(nodeVis* r, int el)
{
	nodeVis* q; // Объявление указателя на звено висюльки
	q = new(nodeVis); // Создание нового звена
	(*q).elem = (*r).elem; // Копирование элемента из заданного звена в новое звено
	(*q).vniz = (*r).vniz; // Установка следующего звена нового звена как следующее звено заданного звена
	(*r).elem = el; // Замена элемента заданного звена на новый элемент
	(*r).vniz = q; // Установка следующего звена заданного звена как новое звено
}


void GirVis::VisUdale(nodeVis* r)
{
	nodeVis* q; // Объявление указателя на звено висюльки
	q = (*r).vniz; // Установка указателя на следующее звено после заданного

	if ((*r).vniz != NULL) // Если следующее звено существует
	{
		(*r).vniz = (*(*r).vniz).vniz; // Установка следующего звена заданного звена как следующее звено для следующего звена
		delete q; // Удаление следующего звена
	}
	else cout << "Звено с заданным элементом последнее!\n"; // Если следующего звена нет, выводим сообщение об ошибке
}


void GirVis::Vis1Udale(nodeVis* r)
{
	nodeVis* g; // Объявление указателя на звено висюльки

	if ((*r).vniz != NULL) // Если следующее звено существует
	{
		g = (*r).vniz; // Установка указателя на следующее звено
		(*r).elem = (*(*r).vniz).elem; // Копирование элемента из следующего звена в заданное звено
		(*r).vniz = (*(*r).vniz).vniz; // Установка следующего звена заданного звена как следующее звено для следующего звена
		delete g; // Удаление следующего звена
	}
	else cout << "Не умею удалять последнее звено\n"; // Если следующего звена нет, выводим сообщение об ошибке
}