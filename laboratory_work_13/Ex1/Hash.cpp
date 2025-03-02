#include "Hash.h"
#include <iostream>
int HashFunction(int key, int size, int p) //???-???????
{
	double key2 = 5 * ((0.6180339887499 * key) - int((0.6180339887499 * key)));
	return (p + key) % size;
}
//-------------------------------
int Next_hash(int hash, int size, int p)//calculating the variable for the next hash
{
	return (hash + 5 * p + 3 * p * p) % size;
}
//-------------------------------
Object create(int size, int(*getkey)(void*))//create a new hash-table
{
	return *(new Object(size, getkey));
}
//-------------------------------
Object::Object(int size, int(*getkey)(void*))//object function that  implements an object
{
	N = 0;
	this->size = size;
	this->getKey = getkey;
	this->data = new void* [size];
	for (int i = 0; i < size; ++i)
		data[i] = NULL;
}
//-------------------------------
bool Object::insert(void* d)//function that inserts an element into a hash table
{
	bool b = false;//variable to check if the table is full or not
	if (N != size)
		for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0);
			i != size && !b; j = Next_hash(j, size, ++i))
			if (data[j] == NULL || data[j] == DEL)
			{
				data[j] = d;
				N++;
				b = true;
			}
	return b;
}
//-------------------------------
int Object::searchInd(int key)//function to search by index
{
	int t = -1;
	bool b = false;
	if (N != 0)
		for (int i = 0, j = HashFunction(key, size, 0); data[j] != NULL && i//cycle to search
			!= size && !b; j = HashFunction(key, size, ++i))
			if (data[j] != DEL)if (getKey(data[j]) == key)
			{
				t = j; b = true;
			}
	return t;
}
//-------------------------------
void* Object::search(int key)//the actual search function of a class
{
	int t = searchInd(key);
	return(t >= 0) ? (data[t]) : (NULL);
}
//-------------------------------
void* Object::deleteByKey(int key)//deletion by key
{
	int i = searchInd(key);
	void* t = data[i];
	if (t != NULL)//check to delete
	{
		data[i] = DEL;
		N--;
	}
	return t;
}
//-------------------------------
bool Object::deleteByValue(void* d)//deletion by value
{
	return(deleteByKey(getKey(d)) != NULL);
}
//-------------------------------
void Object::scan(void(*f)(void*))//scaning the whole table to print it
{
	for (int i = 0; i < this->size; i++)
	{
		std::cout << "" << i;
		if ((this->data)[i] == NULL)
			std::cout << "" << std::endl;
		else
			if ((this->data)[i] == DEL)
				std::cout << "" << std::endl;
			else
				f((this->data)[i]);
	}
}
void Object::resize(Object* obj, int oldSize, int newSize) {
	void** newData = new void* [newSize];//a new array to store elements in it

	for (int i = 0; i < newSize; i++) {//initialize a new array and fill it with NULLs
		newData[i] = NULL;
	}

	//copying the old data into an array
	for (int i = 0; i < oldSize; i++) {
		if (obj->data[i] != NULL && obj->data[i] != DEL) {
			// Find a palce to copy elements into a new array
			int newIndex = (HashFunction(obj->getKey(obj->data[i]), newSize, 0) + Next_hash(0, newSize, 0)) % newSize;
			while (newData[newIndex] != NULL && newData[newIndex] != DEL) {
				newIndex = (newIndex + 1) % newSize;
			}
			newData[newIndex] = obj->data[i];
		}
	}

	// free the old array
	delete[] obj->data;

	// repalce the old array with a new one
	obj->data = newData;
	obj->size = newSize;
}