#include "List2.h"
#include <iostream>
struct AAA 
{
	int key;//tbale key
	char* mas;//table element
};
namespace listx//namespace for list
{
	bool Object::insert(void* data)//function to insert an element into a single linked list
	{
		bool rc = NULL;
		if (head == NULL)
			head = new Element(NULL, data, head);

		else head = (head->prev = new Element(NULL, data, head));
		return rc;
	}
	//-------------------------------
	Element* Object::search(void* data)//function to search elements in a single linked list
	{
		Element* rc = head;
		while ((rc != NULL) && ((((AAA*)rc->data)->key) != ((AAA*)data)->key))
			rc = rc->next;
		return rc;
	}
	//-------------------------------
	bool Object::deleteByElement(Element* e)//function to delete element by value in a single linked list
	{
		bool rc = NULL;
		if (rc = (e != NULL))
		{
			if (e->next != NULL)
				e->next->prev = e->prev;
			if (e->prev != NULL)
				e->prev->next = e->next;
			else
				head = e->next;
			delete e;
		}
		std::cout << "" << std::endl;
		return rc;
	}
	//-------------------------------
	bool Object::deleteByData(void* data)//function to delete by data from a single linked list
	{
		return deleteByElement(search(data));
	}
	//-------------------------------
	Element* Object::getLast()//function to get the last element of a single linked list
	{
		listx::Element* e = this->getFirst(), * rc = this->getFirst();
		while (e != NULL)
		{
			rc = e;
			e = e->getNext();
		};
		return rc;
	}
	Object create()//object function to create a new list
	{
		return *(new Object());
	};
	//-------------------------------
	void Object::scan()//function to scan the whole list 
	{
		listx::Element* e = this->getFirst();
		while (e != NULL)
		{
			std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << "/ ";
			e = e->getNext();
		};
	}
}