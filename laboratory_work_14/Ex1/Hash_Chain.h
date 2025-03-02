#pragma once // Hash_Chain.h
#include "List.h"
namespace hashTC//namespace for hashtable operting functions
{
	struct Object//structure for a hash table element
	{
		int size;//size 
		int(*FunKey)(void*);//pointer to functrion and data type
		listx::Object* Hash;//hashing 
		Object(int siz, int(*f)(void*))//object function to assign elements
		{
			size = siz;
			FunKey = f;
			Hash = new listx::Object[size];
		};
		int hashFunction(void* data);//has functions
		bool insert(void* data);//insert element function
		listx::Element* search(void* data);//search function
		bool deleteByData(void* data);//deletion by data
		void Scan();//scanning function
	};
	Object create(int size, int(*f)(void*));//function to create a hash table
}