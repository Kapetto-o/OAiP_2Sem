#include <iostream>
#include <locale>
#include "C:\Users\Kapetto\Desktop\Univer\Laboratory\KPO\Laboratory_work_6\SE_Lab06L\Dictionary.h"
#pragma comment(lib, "C:\\Users\\Kapetto\\Desktop\\Univer\\Laboratory\\KPO\\Laboratory_work_6\\Debug\\SE_Lab06L.lib")

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

#ifdef TEST_DICTIONARY
	try
	{
		Dictionary::Instance d1 = Dictionary::Create("xxx", 10);
		Dictionary::Entry e1 = { 1, "abcd" }, e2 = { 2,"efg" }, e3 = { 3,"hij" }, e4 = { 4,"klm" }, e5 = { 5,"nop" }, e7 = { 7,"qrs" }, e8 = { 8,"tuv" }, e9 = { 9,"wxy" }, e10 = { 10,"zzz" };
        Dictionary::AddEntry(d1, e1);
        Dictionary::AddEntry(d1, e2);
        Dictionary::AddEntry(d1, e3);
        Dictionary::AddEntry(d1, e4);
        Dictionary::AddEntry(d1, e7);
        Dictionary::AddEntry(d1, e8);
        Dictionary::AddEntry(d1, e9);
        Dictionary::Entry ex2 = Dictionary::GetEntry(d1, 4);
        Dictionary::DelEntry(d1, 2);
        Dictionary::AddEntry(d1, e10);
        Dictionary::Entry newentry1 = { 6, "Гурин" };
        Dictionary::UpdEntry(d1, 3, newentry1);
		Dictionary::Print(d1);
		Delete(d1);
	}
	catch (char* e)
	{
        cout << e << endl;
	};
#endif

#ifdef TEST_CREATE_01
    try
    {
        Dictionary::Create("hbkberjgeoigjkjbeijegpierjb", 5);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif

#ifdef TEST_CREATE_02
    try
    {
        Dictionary::Create("wgeiuwb", 101);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif

#ifdef TEST_ADDENTRY_03  
    try
    {
        Dictionary::Instance TEST = Dictionary::Create("TEST", 2);
        Dictionary::Entry e1 = { 1, "hwbefjw" }, e2 = { 2, "grjwjngwg" }, e3 = { 3, "wuhguwbeg" };
        Dictionary::AddEntry(TEST, e1);
        Dictionary::AddEntry(TEST, e2);
        Dictionary::AddEntry(TEST, e3);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif

#ifdef TEST_ADDENTRY_04
    try
    {
        Dictionary::Instance TEST = Dictionary::Create("TEST", 3);
        Dictionary::Entry e1 = { 1, "hwbefjw" }, e2 = { 2, "grjwjngwg" }, e3 = { 2, "wuhguwbeg" };
        Dictionary::AddEntry(TEST, e1);
        Dictionary::AddEntry(TEST, e2);
        Dictionary::AddEntry(TEST, e3);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif

#ifdef TEST_GETENTRY_05
    try
    {
        Dictionary::Instance TEST = Dictionary::Create("TEST", 3);
        Dictionary::Entry e1 = { 1, "hwbefjw" }, e2 = { 2, "grjwjngwg" }, e3 = { 3, "wuhguwbeg" };
        Dictionary::AddEntry(TEST, e1);
        Dictionary::AddEntry(TEST, e2);
        Dictionary::AddEntry(TEST, e3);
        Dictionary::GetEntry(TEST, 4);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif

#ifdef TEST_DELENTRY_06  
    try
    {
        Dictionary::Instance TEST = Dictionary::Create("TEST", 3);
        Dictionary::Entry e1 = { 1, "hwbefjw" }, e2 = { 2, "grjwjngwg" }, e3 = { 3, "wuhguwbeg" };
        Dictionary::AddEntry(TEST, e1);
        Dictionary::AddEntry(TEST, e2);
        Dictionary::AddEntry(TEST, e3);
        Dictionary::DelEntry(TEST, 4);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif

#ifdef TEST_UPDENTRY_07
    try
    {
        Dictionary::Instance TEST = Dictionary::Create("TEST", 3);
        Dictionary::Entry e1 = { 1, "hwbefjw" }, e2 = { 2, "grjwjngwg" }, e3 = { 3, "wuhguwbeg" };
        Dictionary::AddEntry(TEST, e1);
        Dictionary::AddEntry(TEST, e2);
        Dictionary::AddEntry(TEST, e3);
        Dictionary::UpdEntry(TEST, 4, e2);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif 

#ifdef TEST_UPDENTRY_08
    try
    {
        Dictionary::Instance TEST = Dictionary::Create("TEST", 3);
        Dictionary::Entry e1 = { 1, "hwbefjw" }, e2 = { 2, "grjwjngwg" }, e3 = { 3, "wuhguwbeg" };
        Dictionary::AddEntry(TEST, e1);
        Dictionary::AddEntry(TEST, e2);
        Dictionary::AddEntry(TEST, e3);
        Dictionary::Entry ed2 = { 3, "woihgiowegiweg" };
        Dictionary::UpdEntry(TEST, 2, ed2);
    }
    catch (const char* e)
    {
        cout << e << endl;
    }
#endif
	system("pause");
	return 0;
}