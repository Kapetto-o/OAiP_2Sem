#include <iostream>
#include "Hash.h"
using namespace std;
struct AAA // structure to realize en element of a hash table
{
	int key;
	char* mas;
	AAA(int k, char* z)
	{
		key = k; mas = z;
	} AAA() {}
};
//-------------------------------
int key(void* d)//function that insert's a key
{
	AAA* f = (AAA*)d;
	return f->key;
}
//-------------------------------
void AAA_print(void* d)//function to print the whole table
{
	cout << " ключ " << ((AAA*)d)->key << " - " << ((AAA*)d)->mas << endl;
}
//-------------------------------
int main()//main function
{
	setlocale(LC_ALL, "rus");//localize console
	int siz, choice, k;//variables for functioning
	cout << "Введите размер хеш-таблицы" << endl;
	cin >> siz;
	Object H = create(siz, key);//create a new hash table
	for (;;)
	{
		cout << "1 - вывод хеш-таблицы" << endl;
		cout << "2 - добавление элемента" << endl;
		cout << "3 - удаление элемента" << endl;
		cout << "4 - поиск элемента" << endl;
		cout << "0 - выход" << endl;
		cout << "сделайте выбор" << endl; cin >> choice;
		switch (choice)
		{
		case 0: exit(0);
		case 1: H.scan(AAA_print); break;
		case 2: {
			if (H.N >= H.size * 0.5) {
				int new_size = siz * 2;//get the new size
				H.resize(&H, siz, new_size);//using resize function to complete a task
				cout << "Размер хэш-таблицы увеличен вдвое вследствии заполнения половины исходного размера" << endl;
			}
			AAA* a = new AAA;//memory for a new structure element
			char* str = new char[20];//memory for a value
			cout << "введите ключ" << endl;
			cin >> k;
			a->key = k;
			cout << "введите строку" << endl;
			cin >> str;
			a->mas = str;

			if (H.N == H.size)//if the table is already full
				cout << "Таблица заполнена" << endl;
			else
				H.insert(a);//f not  - insert an element
		} break;
		case 3: {
			cout << "введите ключ для удаления" << endl;
			cin >> k;
			H.deleteByKey(k);//deletion by key
		} break;
		case 4: {
			cout << "введите ключ для поиска" << endl;
			cin >> k;
			if (H.search(k) == NULL)//search function
				cout << "Элемент не найден" << endl;
			else
				AAA_print(H.search(k));
		} break;
		}
	}
	return 0;
}