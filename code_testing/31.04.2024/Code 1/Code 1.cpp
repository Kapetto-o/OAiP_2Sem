﻿#include <iostream> // Подключаем библиотеку для ввода и вывода данных

using namespace std; // Используем пространство имен std, что позволяет нам не писать std:: перед каждым оператором ввода/вывода

// Определяем структуру "Узел"
struct node
{
	int Key; // Ключ узла
	int Count; // Количество узлов
	node* Left; // Указатель на левого потомка
	node* Right; // Указатель на правого потомка
};

// Определяем класс "Дерево"
class TREE
{
private:
	node* Tree; // Указатель на корень дерева
	void Search(int, node**); // Метод для поиска узла в дереве
public:
	TREE() { Tree = NULL; } // Конструктор класса
	node** GetTree() { return &Tree; } // Метод для получения корня дерева
	void BuildTree(); // Метод для построения дерева
	void CleanTree(node**); // Метод для очистки дерева
	void ObhodEnd(node**); // Метод для концевого обхода дерева
	void ObhodLeft(node**); // Метод для левостороннего обхода дерева
	void ObhodBack(node**); // Метод для обратного обхода дерева
	void Vyvod(node**, int); // Метод для вывода дерева
	int Height(node**); // Метод для определения высоты дерева
};

void main()
{
	setlocale(LC_ALL, "Rus"); // Устанавливаем русскую локализацию
	TREE A; // Создаем объект класса TREE

	A.BuildTree(); // Строим дерево
	cout << "\nВывод дерева:\n";
	A.Vyvod(A.GetTree(), 0); // Выводим дерево
	cout << "\nВысота дерева:" << A.Height(A.GetTree()) << endl; // Выводим высоту дерева
	cout << "\nЛевосторонний обход дерева: ";
	A.ObhodLeft(A.GetTree()); // Производим левосторонний обход дерева
	cout << "\nКонцевой обход дерева: ";
	A.ObhodEnd(A.GetTree()); // Производим концевой обход дерева
	cout << "\nОбратный обход дерева: ";
	A.ObhodBack(A.GetTree()); // Производим обратный обход дерева

	cout << "\n";
	system("PAUSE"); // Останавливаем выполнение программы
}

void TREE::BuildTree()
// Функция считывает ключи узлов от пользователя и добавляем их в дерево
// Когда мы вводим 0, она прекращает считывание ключей и построение дерева
{
	int el; // Объявляем переменную для хранения ключа узла

	cout << "Вводите ключи вершин дерева:\n"; // Выводим приглашение для ввода ключей узлов
	cin >> el; // Считываем ключ узла
	while (el != 0) // Пока введенный ключ не равен нулю
	{
		Search(el, &Tree); // Ищем место для вставки узла в дерево и вставляем его
		cin >> el; // Считываем следующий ключ узла
	}
}

void TREE::Search(int x, node** p)
// Функция используется для поиска места в дереве, где должен быть вставлен новый узел
// Если узел с таким ключом уже существует, функция увеличивает счетчик этого узла на 1
// Если такого узла нет, функция создает новый узел с данным ключом
// Eсли ключ нового узла меньше ключа текущего узла, функция ищет место для вставки в левом поддереве, иначе - в правом
{
	if (*p == NULL) // Если узел пуст
	{
		*p = new(node); // Создаем новый узел
		(**p).Key = x; // Присваиваем ключу узла значение x
		(**p).Count = 1; // Устанавливаем счетчик узла равным 1
		(**p).Left = NULL; // Устанавливаем указатель на левого потомка равным NULL
		(**p).Right = NULL; // Устанавливаем указатель на правого потомка равным NULL
	}
	else
		if (x < (**p).Key) // Если x меньше ключа узла
			Search(x, &((**p).Left)); // Ищем место для вставки узла в левом поддереве
		else
			if (x > (**p).Key) // Если x больше ключа узла
				Search(x, &((**p).Right)); // Ищем место для вставки узла в правом поддереве
			else
				(**p).Count = (**p).Count + 1; // Если x равно ключу узла, увеличиваем счетчик узла на 1
}

void TREE::ObhodLeft(node** w)
// Функция левостороннего обхода дерева
// Cначала обрабатывается корень, затем левое поддерево, а затем правое поддерево
// Если узел пуст, обход прекращается
// Если узел не пуст, функция выводит ключ узла, а затем рекурсивно обходит левое и правое поддеревья этого узла
{
	if (*w != NULL) // Если узел не пуст
	{
		cout << (**w).Key << " "; // Выводим ключ узла
		ObhodLeft(&((**w).Left)); // Обходим левое поддерево
		ObhodLeft(&((**w).Right)); // Обходим правое поддерево
	}
}

void TREE::ObhodEnd(node** w)
// Функция концевого обхода
// Cначала обрабатывается левое поддерево, затем правое поддерево, а затем корень
// Если узел пуст, обход прекращается
// Если узел не пуст, функция рекурсивно обходит левое и правое поддеревья этого узла, а затем выводит ключ узла
{
	if (*w != NULL) // Если узел не пуст
	{
		ObhodEnd(&((**w).Left)); // Обходим левое поддерево
		ObhodEnd(&((**w).Right)); // Обходим правое поддерево
		cout << (**w).Key << " "; // Выводим ключ узла
	}
}

void TREE::ObhodBack(node** w)
// Функция обратного обхода
// Сначала обрабатывается левое поддерево, затем корень, а затем правое поддерево
// Если узел пуст, обход прекращается
// Если узел не пуст, функция рекурсивно обходит левое поддерево этого узла, выводит ключ узла, а затем рекурсивно обходит правое поддерево
{
	if (*w != NULL) // Если узел не пуст
	{
		ObhodBack(&((**w).Left)); // Обходим левое поддерево
		cout << (**w).Key << " "; // Выводим ключ узла
		ObhodBack(&((**w).Right)); // Обходим правое поддерево
	}
}

void TREE::CleanTree(node** w)
// Функция очистки дерева
// Она рекурсивно обходит все узлы дерева и удаляет их
// Сначала очищает левое и правое поддеревья узла, а затем удаляет сам узел
// Если узел пуст, очистка прекращается
{
	if (*w != NULL) // Если узел не пуст
	{
		CleanTree(&((**w).Left)); // Очищаем левое поддерево
		CleanTree(&((**w).Right)); // Очищаем правое поддерево
		delete* w; // Удаляем узел
	}
}

void TREE::Vyvod(node** w, int l)
// Функция вывода дерева
// Она рекурсивно обходит все узлы дерева и выводит их
// Сначала выводит правое поддерево, затем ключ узла, а затем левое поддерево
// Если узел пуст, вывод прекращается
{
	int i;
	if (*w != NULL) // Если узел не пуст
	{
		Vyvod(&((**w).Right), l + 1); // Выводим правое поддерево
		for (i = 1; i <= l; i++)
			cout << "   "; // Выводим пробелы для отступа
		cout << (**w).Key << endl; // Выводим ключ узла
		Vyvod(&((**w).Left), l + 1); // Выводим левое поддерево
	}
}

int TREE::Height(node** w)
// Функция вычисления высоты дерева
// Она рекурсивно обходит все узлы дерева и вычисляет их высоту
// Если узел пуст, функция возвращает -1
// Если узел не пуст, функция вычисляет высоту левого и правого поддеревьев этого узла, а затем возвращает максимальную из этих двух высот, увеличенную на 1
{
	int h1, h2;
	if (*w == NULL) // Если узел пуст
		return(-1); // Возвращаем -1
	else            // Если узел не пуст
	{
		h1 = Height(&((**w).Left)); // Вычисляем высоту левого поддерева
		h2 = Height(&((**w).Right)); // Вычисляем высоту правого поддерева
		if (h1 > h2) // Если высота левого поддерева больше высоты правого поддерева
			return(1 + h1); // Возвращаем высоту левого поддерева + 1
		else
			return(1 + h2); // Возвращаем высоту правого поддерева + 1
	}
}