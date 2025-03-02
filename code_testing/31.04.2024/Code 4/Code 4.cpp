// Подключение библиотек
#include<conio.h>
#include<iostream>
// Использование пространства имен std
using namespace std;

// Структура узла дерева
struct node
{
	int key; // Ключ узла
	int count; // Количество узлов
	node* Left; // Указатель на левый узел
	node* Right; // Указатель на правый узел
};

// Класс дерева
class Tree
{
private:
	node* root; // Корень дерева
	void DisposeTree(node*); // Метод для удаления дерева
	void printTree(node*, int); // Метод для печати дерева
	void Delete(node**, int); // Метод для удаления узла
	void del(node**, node*); // Вспомогательный метод для удаления узла
public:
	Tree() { root = NULL; }; // Конструктор дерева
	~Tree(); // Деструктор дерева
	void creat_Tree(); // Метод для создания дерева
	void look_Tree(); // Метод для просмотра дерева
	void add_Tree(); // Метод для добавления узла в дерево
	void delete_Tree(); // Метод для удаления узла из дерева
	void search(int, node**); // Метод для поиска узла в дереве
	node* getTree() { return root; }; // Метод для получения корня дерева
};

// Структура звена кольца
struct zveno
{
	int element; // Элемент звена
	Tree ukTree; // Дерево, связанное с звеном
	zveno* sled; // Указатель на следующее звено
};

// Класс кольца
class ring
{
private:
	zveno* ukring; // Указатель на текущее звено кольца
public:
	ring() { ukring = NULL; }; // Конструктор кольца
	~ring(); // Деструктор кольца
	void create(); // Метод для создания кольца
	void look(); // Метод для просмотра кольца
	void add_after(int, zveno*); // Метод для добавления звена после указанного звена
	void add_befor(int, zveno*); // Метод для добавления звена перед указанным звеном
	void Delete(zveno*); // Метод для удаления указанного звена
	void delete_next(zveno*); // Метод для удаления звена после указанного звена
	int poisk(int, zveno**); // Метод для поиска элемента в кольце
	zveno** getring() { return &ukring; }; // Метод для получения текущего звена кольца
};

void ring::create()
{
	zveno* ukzv;
	int elem;

	cout << "\nПостроение кольца.." << endl;
	cout << "Вводите элементы кольца (ввод окончить 0):\n";
	cout << "-->";
	cin >> elem;
	if (elem != 0)
	{
		ukzv = ukring = new(zveno);
		(*ukzv).element = elem;
		(*ukzv).ukTree.creat_Tree();
		cout << "\n-->";
		cin >> elem;
		while (elem != 0)
		{
			(*ukzv).sled = new(zveno);
			ukzv = (*ukzv).sled;
			(*ukzv).element = elem;
			(*ukzv).ukTree.creat_Tree();
			cout << "\n-->";
			cin >> elem;
		}
		ukzv->sled = ukring;
	}
}

ring::~ring()
{
	zveno* ukzv;
	ukzv = ukring;
	while(ukring!=NULL)
		if (ukzv->sled == ukring)
		{
			ukring = NULL;
			ukzv->ukTree.~Tree();
			delete ukzv;
		}
		else
		{
			while (ukzv->sled->sled != ukring)
				ukzv = (*ukzv).sled;
			(*ukzv).sled->ukTree.~Tree();
			delete(*ukzv).sled;
			ukzv->sled = ukring;
			ukzv = ukring;
		}
}

void ring::look()
{
	zveno* ukzv;
	cout << "\nВывод содержимого кольца: ";
	ukzv = ukring;
	do {
		cout << "\n-->" << (*ukzv).element << endl;
		ukzv->ukTree.look_Tree();
		ukzv = ukzv->sled;
		_getch();
	} while (ukzv != ukring);
	cout << endl;
}

void ring::add_befor(int elem, zveno* zv)
{
	zveno* ukzv;
	Tree temp;
	ukzv = new(zveno);
	temp = ukzv->ukTree;
	ukzv->element = zv->element;
	ukzv->ukTree = zv->ukTree;
	ukzv->sled = zv->sled;
	zv->element = elem;
	zv->ukTree = temp;
	zv->ukTree.creat_Tree();
	zv->sled = ukzv;
}

void ring::add_after(int elem, zveno* zv)
{
	zveno* ukzv;

	ukzv = new(zveno);
	ukzv->element = elem;
	ukzv->ukTree.creat_Tree();
	ukzv->sled = zv->sled;
	zv->sled = ukzv;
}

void ring::Delete(zveno* zv)
{
	zveno* ukzv1, *ukzv2;
	zveno* time;
	if (zv->sled != ukring)
	{
		time = zv->sled;
		zv->ukTree.~Tree();
		(*zv) = *((*zv).sled);
		delete time;
	}
	else
		if (zv->sled == zv)
		{
			zv->ukTree.~Tree();
			delete ukring;
			ukring = NULL;
			cout << "Список пуст..\n";
		}
		else
		{
			ukzv2 = ukring;
			ukzv1 = ukring->sled;
			while (ukzv1 != zv)
			{
				ukzv2 = ukzv1;
				ukzv1 = ukzv1->sled;
			}
			time = ukzv2->sled;
			ukzv2->sled->ukTree.~Tree();
			ukzv2->sled = ukzv2->sled->sled;
			delete time;
		}
}

void ring::delete_next(zveno* zv)
{
	zveno* time;
	if (zv->sled != ukring)
	{
		time = zv->sled;
		zv->sled = zv->sled->sled;
		time->ukTree.~Tree();
		delete time;
	}
	else
		if (zv->sled == zv)
			cout << "В кольце только один элемент!\n";
		else
		{
			time = ukring->sled;
			*((*zv).sled) = (*(*(*zv).sled).sled);
			time->ukTree.~Tree();
			delete time;
		}
}

int ring::poisk(int elem, zveno** Res)
{
	zveno* ukzv;
	int vozvr = 0;
	if (*(getring()) == NULL)
		cout << "Кольцо не существует..\n";
	else
	{
		ukzv = ukring;
		while (ukzv->sled != ukring && (*Res) == NULL)
		{
			if (ukzv->element == elem)
			{
				vozvr = 1;
				*Res = ukzv;
			}
			ukzv = ukzv->sled;
		}
		if((*Res)==NULL)
			if (ukzv->element == elem)
			{
				vozvr = 1;
				*Res = ukzv;
			}
	}
	return vozvr;
}

Tree::~Tree()
{
	DisposeTree(root);
	root = NULL;
}

void Tree::DisposeTree(node* p)
{
	if (p != NULL)
	{
		DisposeTree(p->Left);
		DisposeTree(p->Right);
		delete p;
	}
}

void Tree::search(int x, node** p)
{
	if (*p == NULL)
	{
		*p = new(node);
		(**p).key = x;
		(**p).count = 1;
		(**p).Left = (**p).Right = NULL;
	}
	else
		if (x < (**p).key)search(x, &((**p).Left));
		else
			if (x > (**p).key)
				search(x, &((**p).Right));
			else
				(**p).count += 1;
}

void Tree::creat_Tree()
{
	int elem;
	cout << "Вводите ключи узлов дерева (ввод окончите 0):\n";
	cin >> elem;
	while (elem != 0)
	{
		search(elem, &root);
		cin >> elem;
	}
}

void Tree::look_Tree()
{
	if (root == NULL)
		cout << "Дерево пусто..\n";
	else
		printTree(root, 0);
}

void Tree::printTree(node* w, int L)
{
	if (w != NULL)
	{
		printTree(w->Left, L + 1);
		for (int i = 1; i <= L; i++)
			cout << " ";
		cout << w->key << endl;
		printTree(w->Right, L + 1);
	}
}

void Tree::add_Tree()
{
	int k;

	cout << "\nВводите ключи обавляемых узлов (ввод окончите 0):\n";
	cin >> k;
	cout << " ";
	while (k != 0)
	{
		search(k, & (root));
		cin >> k;
		cout << " ";
	}
}

void Tree::delete_Tree()
{
	int elem;
	if (root == NULL)
		cout << "Дерево пусто..\n";
	else
	{
		cout << "Введите ключи удаляемого узла: ";
		cin >> elem;
		cout << endl;
		Delete(&root, elem);
	}
}

void Tree::Delete(node** d, int k)
{
	node* q;
	node* s;

	if (*d == NULL)
		cout << "Узел с заданным ключом в дереве не найден..\n";
	else
		if (k < (**d).key)
			Delete(&((**d).Left), k);
		else
			if (k > (**d).key)
				Delete(&((**d).Right), k);
			else
			{
				q = *d;
				s = *d;
				if ((*d)->Right == NULL)
				{
					*d = (*q).Left;
					delete s;
				}
				else
					if ((*q).Left == NULL)
					{
						*d = (*q).Right;
						delete s;
					}
					else
						del(&((*q).Left), &(*q));
			}
}

void Tree::del(node** r, node* q)
{
	node* s;
	if ((**r).Right == NULL)
	{
		(*q).key = (**r).key;
		(*q).count = (**r).count;
		q = s = *r;
		*r = (**r).Left;
		delete s;
	}
	else
		del(&((**r).Right), &(*q));
}

void main()
{
	setlocale(LC_ALL, "Rus"); // подключение русского языка
	int menu1 = 1, choice, elem1, elem2, menu2; // Объявление переменных
	ring A;
	zveno* Res;
	cout << " ----------------Структура---------------\n";
	cout << "-----------\"кольцо с деревьями\"-----------\n\n";
	while (menu1)
	{
		cout << endl;
		cout << "<------------Главное меню 1.0------------>\n";
		cout << "1. Построение структуры...................\n";
		cout << "2. Просмотр структуры.....................\n";
		cout << "3. Добавление элемента после указанного...\n";
		cout << "4. Добавление элемента перед указанным....\n";
		cout << "5. Удаление элемента......................\n";
		cout << "6. Удаление элемента после указанного.....\n";
		cout << "7. Преобразование дерева заданного эл-та..\n";
		cout << "8. Удаление структуры.....................\n";
		cout << "9. Выход..................................\n";
		cout << "Введите номер режима и нажмите <Enter>: ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			if (*(A.getring()) == NULL)
				A.create();
			else
				cout << "Кольцо уже существует..\n";
			break;
		case 2:
			if (*(A.getring()) == NULL)
				cout << "Кольцо пусто..\n";
			else A.look();
			break;
		case 3:
			if(*(A.getring())==NULL)
				cout << "Кольцо пусто..\n";
			else
			{
				Res = NULL;
				cout << "Введите элемент после которого хотите добавить звено: ";
				cin >> elem1;
				cout << endl;
				if (A.poisk(elem1, &Res))
				{
					cout << "Введите элемент который хотите добавить: ";
					cin >> elem2;
					cout << endl;
					A.add_after(elem2, Res);
				}
				else
					cout << "Элемент" << elem1 << "не найден.\n";
			}
			break;
		case 4:
			if (*(A.getring()) == NULL)
				cout << "Кольцо пусто..\n";
			else
			{
				Res = NULL;
				cout << "Введите элемент перед которым хотите добавить звено: ";
				cin >> elem1;
				cout << endl;
				if (A.poisk(elem1, &Res))
				{
					cout << "Введите элемент который хотите добавить: ";
					cin >> elem2;
					cout << endl;
					A.add_befor(elem2, Res);
				}
				else
					cout << "Элемент" << elem1 << "не найден.\n";
			}
			break;
		case 5:
			if (*(A.getring()) == NULL)
				cout << "Кольцо пусто..\n";
			else
			{
				Res = NULL;
				cout << "Введите элемент который хотите удалить: ";
				cin >> elem1;
				cout << endl;
				if (A.poisk(elem1, &Res))
					A.Delete(Res);
				else
					cout << "Элемент отсутствует..\n";
			}
			break;
		case 6:
			if (*(A.getring()) == NULL)
				cout << "Кольцо пусто..\n";
			else
			{
				Res = NULL;
				cout << "Введите элемент после которого хотите удалить: ";
				cin >> elem1;
				cout << endl;
				if (A.poisk(elem1, &Res))
					A.delete_next(Res);
				else
					cout << "Элемент отсутствует..\n";
			}
			break;
		case 7:
			if (*(A.getring()) == NULL)
				cout << "Кольцо пусто..\n";
			else
			{
				Res = NULL;
				cout << "Введите элемент кольца: ";
				cin >> elem1;
				cout << endl;
				if (A.poisk(elem1, &Res))
				{
					menu2 = 1;
					while (menu2)
					{
						cout << endl;
						cout << "<----------- Меню 1.1 ----------->\n";
						cout << "1. Построение дерева..............\n";
						cout << "2. Просмотр дерева................\n";
						cout << "3. Добавление элемента в дерево...\n";
						cout << "4. Удаление элемента из дерева....\n";
						cout << "5. Удаление дерева................\n";
						cout << "6. Выход в главное меню...........\n";
						cout << "Введеите номер режима и нажмите <Enter>: ";
						cin >> choice;
						cout << endl;
						switch (choice)
						{
						case 1:
							if ((*Res).ukTree.getTree() == NULL)
								(*Res).ukTree.creat_Tree();
							else
								cout << "Дерево существует..\n";
							break;
						case 2:
							(*Res).ukTree.look_Tree();
							break;
						case 3:
							(*Res).ukTree.add_Tree();
							break;
						case 4:
							(*Res).ukTree.delete_Tree();
							break;
						case 5:
							if ((*Res).ukTree.getTree() == NULL)
								cout << "Дерево не существует..\n";
							else
								(*Res).ukTree.~Tree();
							break;
						case 6:
							menu2 = 0;
							break;
						default:
							break;
						}

					}
				}
				else
					cout << "Элемент"<<elem1<<"не найден.\n";
			}
			break;
		case 8:
			if (*(A.getring()) == NULL)
				cout << "Кольцо пусто..\n";
			else
				A.~ring();
			break;
		case 9:
			A.~ring();
			menu1 = 0;
			break;
		}
	}
	cout << "\n";
	system("PAUSE");
}