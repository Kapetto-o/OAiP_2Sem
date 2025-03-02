#pragma once 
#define LISTNIL (Element*)-1
namespace listx//namespace for list
{
	struct Element//structure to define a doubly linked list
	{
		Element* prev;//pointers to the next and previous element
		Element* next;
		void* data;//data
		Element(Element* pr, void* dat, Element* nt)//namespace function 
		{
			prev = pr;
			data = dat;
			next = nt;
		}
		Element* getNext()//getting next element
		{
			return next;
		};
		Element* getPrev()//getting previous element
		{
			return prev;
		};
	};
	static Element* NIL = nullptr;//set the first pointer
	struct Object//object structure
	{
		Element* head;//head pointer
		Object()
		{
			head = NIL;
		};
		Element* getFirst()//get the head of the list
		{
			return head;
		};
		Element* getLast();//same functions applied to a doubly linked list
		Element* search(void* data);
		bool insert(void* data);
		bool deleteByElement(Element* e);
		bool deleteByData(void* data);
		void scan();
	};
	Object create();
}
#undef LISTNIL