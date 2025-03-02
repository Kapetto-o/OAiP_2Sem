#include <stdio.h> // Подключение библиотеки для работы с вводом/выводом
#include<conio.h> // Подключение библиотеки для работы с консолью
#include<iostream> // Подключение библиотеки для работы с потоками ввода/вывода
using namespace std; // Использование пространства имен std

// Определение структуры "Узел"
struct Uzel
{
	char Key; // Ключ узла
	Uzel* Left; // Указатель на левого потомка
	Uzel* Right; // Указатель на правого потомка
};

// Определение структуры "Звено"
struct zveno
{
	Uzel* Element; // Указатель на элемент
	zveno* Sled; // Указатель на следующее звено
};

// Определение класса "Дерево"
class Tree
{
private:
	Uzel* Root; // Корень дерева
	zveno* Stack; // Стек
public:
	Tree(); // Конструктор
	void Udalenie(Uzel**); // Функция удаления узла
	void V_stack(Uzel*); // Функция добавления элемента в стек
	void PrintTree(Uzel*, int); // Функция печати дерева
	void Print_Tree_Left(Uzel*, int); // Функция печати дерева (левый обход)
	void Print_Tree_End(Uzel*, int); // Функция печати дерева (конечный обход)
	void Print_Tree_Back(Uzel*, int); // Функция печати дерева (обратный обход)
	Uzel* GetTree() { return Root; }; // Функция получения корня дерева
};

// Функция добавления элемента в стек
void Tree::V_stack(Uzel* Elem)
{
	zveno* q = new(zveno); // Создание нового звена
	q->Element = Elem; // Присваивание элемента звену
	q->Sled = Stack; // Присваивание следующего звена
	Stack = q; // Обновление вершины стека
}

// Функция удаления узла
void Tree::Udalenie(Uzel** tmp)
{
	zveno* q;
	if (Stack != NULL) // Если стек не пуст
	{
		(*tmp) = Stack->Element; // Получение элемента из вершины стека
		q = Stack; // Сохранение указателя на вершину стека
		Stack = Stack->Sled; // Обновление вершины стека
		delete q; // Удаление звена
	}
}

// Функция печати дерева
void Tree::PrintTree(Uzel* w, int l)
{
	if (w != NULL) // Если узел не пуст
	{
		PrintTree(w->Right, l + 1); // Рекурсивный вызов для правого поддерева
		for (int i = 1; i <= l; i++) // Вывод отступов
			cout << " ";
		cout << w->Key << endl; // Вывод ключа узла
		PrintTree(w->Left, l + 1); // Рекурсивный вызов для левого поддерева
	}
}

// Функция печати дерева (левый обход)
void Tree::Print_Tree_Left(Uzel* w, int l)
{
	if (w != NULL) // Если узел не пуст
	{
		cout << w->Key << " "; // Вывод ключа узла
		Print_Tree_Left(w->Left, l + 1); // Рекурсивный вызов для левого поддерева
		Print_Tree_Left(w->Right, l + 1); // Рекурсивный вызов для правого поддерева
	}
}

// Функция печати дерева (конечный обход)
void Tree::Print_Tree_End(Uzel* w, int l)
{
	if (w != NULL) // Если узел не пуст
	{
		Print_Tree_End(w->Left, l + 1); // Рекурсивный вызов для левого поддерева
		Print_Tree_End(w->Right, l + 1); // Рекурсивный вызов для правого поддерева
		cout << w->Key << " "; // Вывод ключа узла
	}
}

// Функция печати дерева (обратный обход)
void Tree::Print_Tree_Back(Uzel* w, int l)
{
	if (w != NULL) // Если узел не пуст
	{
		cout << "("; // Вывод открывающей скобки
		Print_Tree_Back(w->Left, l + 1); // Рекурсивный вызов для левого поддерева
		cout << w->Key << " "; // Вывод ключа узла
		Print_Tree_Back(w->Right, l + 1); // Рекурсивный вызов для правого поддерева
		cout << ")"; // Вывод закрывающей скобки
	}
}

// Конструктор класса "Дерево"
Tree::Tree()
{
	Stack = NULL; // Инициализация стека
	Root = new(Uzel); // Создание корня дерева
	Root->Right = NULL; // Инициализация правого потомка корня
}

void main()
{
	setlocale(LC_ALL, "Rus"); // Установка русской локали для корректного отображения кириллицы

	char Formula_Post[30]; // Массив для хранения формулы
	char k; // Переменная для хранения текущего символа формулы
	Uzel* Ukazatel = NULL; // Указатель на текущий узел дерева

	cout << "Введите формулу записанную в постфиксной форме..\n"; // Вывод приглашения для ввода формулы
	gets_s(Formula_Post); // Считывание формулы с консоли

	_strrev(Formula_Post); // Реверсирование формулы (переворачивание строки)

	cout << "Приступим к построению дерева формулы..\n"; // Вывод сообщения о начале построения дерева

	Tree A; // Создание объекта класса "Дерево"
	Uzel* Temp = A.GetTree(); // Получение корня дерева

	for (int i = 0; i < strlen(Formula_Post); i++) // Цикл по символам формулы
	{
		k = Formula_Post[i];
		if(strchr("+-*/^",k)!=NULL)
			if (Temp->Right == NULL)
			{
				Temp->Right = new(Uzel);
				Temp = Temp->Right;
				Temp->Key = k;
				Temp->Left = Temp->Right = NULL;
				A.V_stack(Temp);
			}
			else
			{
				Temp->Left = new(Uzel);
				Temp = Temp->Left;
				Temp->Key = k;
				Temp->Left = Temp->Right = NULL;
				A.V_stack(Temp);
			}
		else
			if (Temp->Right == NULL)
			{
				Temp->Right = new(Uzel);
				Temp = Temp->Right;
				Temp->Key = k;
				Temp->Left = Temp->Right = NULL;
				A.Udalenie(&Ukazatel);
				Temp = Ukazatel;
			}
			else
			{
				Temp->Left = new(Uzel);
				Temp = Temp->Left;
				Temp->Key = k;
				Temp->Left = Temp->Right = NULL;
				A.Udalenie(&Ukazatel);
				Temp = Ukazatel;
			}
	}

	cout << "\nКонтрольный вывод дерева-формулы..\n"; // Вывод сообщения о начале контрольного вывода дерева
	A.PrintTree(A.GetTree()->Right, 0); // Печать дерева

	cout << "Перед Вами формула, записанная в инфиксной форме..\n"; // Вывод сообщения о начале вывода формулы в инфиксной форме
	A.Print_Tree_Back(A.GetTree()->Right, 0); // Печать дерева (обратный обход)
	cout << endl;

	cout << "------------------------------------------------\n";
	cout << "Перед Вами формула, записанная в префиксной форме..\n"; // Вывод сообщения о начале вывода формулы в префиксной форме
	A.Print_Tree_Left(A.GetTree()->Right, 0); // Печать дерева (левый обход)
	cout << endl;

	cout << "------------------------------------------------\n";
	cout << "Перед Вами формула, записанная в постфиксной форме..\n"; // Вывод сообщения о начале вывода формулы в постфиксной форме
	A.Print_Tree_End(A.GetTree()->Right, 0); // Печать дерева (конечный обход)
	cout << "\n";

	system("PAUSE"); // Пауза перед завершением программы
}