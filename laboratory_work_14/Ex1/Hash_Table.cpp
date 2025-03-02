#include "Hash_Chain.h"
#include <iostream>
namespace hashTC//namesapce for a hashtable operating functions
{
	Object create(int size, int(*f)(void*))//function to create a hash table
	{
		return *(new Object(size, f));
	}
	int Object::hashFunction(void* data)//hash function based on XOR
	{
		int fkey = FunKey(data);
		int new_size_value = size;
		//int new_size_value = size ^ 1;
		int final_hash = fkey % new_size_value;
		return final_hash;
	};
	bool Object::insert(void* data)//function to insert a hssh value into a hashtbale
	{
		return (Hash[hashFunction(data)].insert(data));
	};
	bool Object::deleteByData(void* data)//function to delete value by data
	{
		return (Hash[hashFunction(data)].deleteByData(data));
	};
	listx::Element* Object::search(void* data)//function to search by value
	{
		return Hash[hashFunction(data)].search(data);
	};
	void Object::Scan()//functio that scans the whole hashtbale
	{
		for (int i = 0; i < size; i++)
		{
			Hash[i].scan();
			std::cout << '\n';
		}
	};
}