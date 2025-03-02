#include <iostream>
#include "Hash_Chain.h"
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
struct AAA//user data type 
{
	int key;
	char* mas;
	AAA(int k, char* z)
	{
		key = k;
		mas = z;
	}AAA()
	{
		key = 0;
		mas = nullptr;
	}
};
int hf(void* d)//function to return a key of a current structure
{
	AAA* f = (AAA*)d;
	return f->key;
}
//-------------------------------
void AAA_print(listx::Element* e)//function to print structure
{
	std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << " / ";
}
//-------------------------------
int main()//main function
{
	setlocale(LC_ALL, "rus");//console localization
	int current_size;
	cout << "Введите размер хеш-таблицы" << endl;
	cin >> current_size;
	hashTC::Object H = hashTC::create(current_size, hf);//use createfunction to create a hashtable
	int choice;
	int k;
	for (;;)//cycle for choise
	{
		cout << "1 - вывод хеш-таблицы" << endl;
		cout << "2 - добавление элемента" << endl;
		cout << "3 - удаление элемента" << endl;
		cout << "4 - поиск элемента" << endl;
		cout << "0 - выход" << endl;
		cout << "сделайте выбор" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: exit(0);
		case 2: {
			AAA* a = new AAA;
			char* str = new char[20];
			cout << "введите номер квартиры" << endl;
			cin >> k;
			a->key = k;
			cout << "введите жильца" << endl;
			cin >> str;
			a->mas = str;
			H.insert(a);
		}
			  break;
		case 1: H.Scan();
			break;
		case 3: {
			AAA* b = new AAA;
			cout << "введите ключ" << endl;
			cin >> k;
			b->key = k;
			H.deleteByData(b);
		}
			  break;
		case 4: AAA * c = new AAA;
			cout << "введите ключ" << endl; cin >> k;
			c->key = k;
			auto start = chrono::high_resolution_clock::now();//timer start
			if (H.search(c) == NULL)
				cout << "Элемент не найден" << endl;
			else
			{
				cout << "Первый элемент с данным ключом" << endl;
				AAA_print(H.search(c));
				cout << endl;
			}
			auto end = chrono::high_resolution_clock::now();//timer end
			auto duration = duration_cast<microseconds>(end - start);//calculate the function running duration
			cout << "Time taken to use the search function is: " << duration.count() << " microseconds" << endl;
			break;
		}
	}
	return 0;
}