﻿#include <iostream> // Подключение стандартной библиотеки c++
using namespace std; // Указываем на использование пространства имён std, что позволяет не писать "std::" перед операторами ввода/вывода

// Определение структуры узла для дека
struct node {
    int elem; // элемент узла
    node* sled; // указатель на следующий узел
};

// Определение класса Spisok, который представляет собой дек
class Spisok {
private:
    node* id, * rd; // указатели на начало и конец дека
    int el_left, el_right; // элементы слева и справа

public:
    // Методы класса Spisok
    void POSTROENIE(); // построение дека
    void VYVOD(); // вывод дека
    // Новая функция COUNT в программе 
    int COUNT(); // подсчет количества элементов в деке
    void VSTAV1(int); // вставка элемента справа
    void VSTAV2(int); // вставка элемента слева
    int SelElLeft() { return el_left; } // выбор элемента слева
    int SelElRight() { return el_right; } // выбор элемента справа
    void YDALE1(); // удаление элемента справа
    void YDALE2(); // удаление элемента слева
    void OCHISTKA(); // очистка дека
};

// Главная функция
void main()
// В данном случае эта функция задаёт общий вид выполняемой программы
// Объединяет и использует все представленные в коде функции
{
    setlocale(LC_ALL, "Rus"); // установка русского языка
    Spisok A; // создание объекта класса Spisok
    int el; // переменная для хранения элемента

    // Построение и вывод дека
    A.POSTROENIE(); A.VYVOD();

    // Выводим количество элементов в деке
    cout << "Количество элементов в деке: " << A.COUNT() << endl;

    // Добавление элемента справа
    cout << "Добавим звено справа.\n";
    cout << "Введите элемент добавляемого звена: ";
    cin >> el;
    A.VSTAV1(el); A.VYVOD();

    // Выводим количество элементов в деке
    cout << "Количество элементов в деке: " << A.COUNT() << endl;

    // Добавление элемента слева
    cout << "Добавим звено слева.\n";
    cout << "Введите элемент добавляемого звена: ";
    cin >> el;
    A.VSTAV2(el); A.VYVOD();

    // Выводим количество элементов в деке
    cout << "Количество элементов в деке: " << A.COUNT() << endl;

    // Удаление элемента справа
    cout << "Удалим звено справа.\n";
    A.YDALE1(); A.VYVOD();

    // Выводим количество элементов в деке
    cout << "Количество элементов в деке: " << A.COUNT() << endl;

    // Удаление элемента слева
    cout << "Удалим звено слева.\n";
    A.YDALE2(); A.VYVOD();

    // Выводим количество элементов в деке
    cout << "Количество элементов в деке: " << A.COUNT() << endl;

    // Очистка дека
    A.OCHISTKA();

    cout << "\n";
    system("PAUSE"); // Указываем на остановку/завершение программыпрограммы
}

void Spisok::POSTROENIE()
// Функция используется для построения дека
// Она считывает элементы, введенные пользователем, и добавляет их в дек
{
    node* k; // Временный указатель на узел
    int el; // Временная переменная для хранения элемента

    // Выводим сообщение о вводе элементов дека
    cout << "Вводите содержимое звеньев дека:\n";
    cin >> el; // Считываем элемент

    // Если элемент не равен нулю, то начинаем построение дека
    if (el != 0) {
        k = new(node); // Создаем новый узел
        (*k).elem = el; // Присваиваем элементу узла значение введенного элемента
        (*k).sled = NULL; // Устанавливаем указатель на следующий узел в NULL

        id = k; // Устанавливаем указатель на начало дека на новый узел
        rd = k; // Устанавливаем указатель на конец дека на новый узел

        cin >> el; // Считываем следующий элемент

        // Пока элемент не равен нулю, продолжаем добавлять элементы в дек
        while (el != 0)
        {
            VSTAV1(el); // Добавляем элемент в конец дека
            cin >> el; // Считываем следующий элемент
        }
    }
    else
    {
        // Если первый введенный элемент равен нулю, то дек пуст
        rd = NULL;
        id = NULL;
    }
}

void Spisok::VYVOD()
// Функция выводит элементы начиная с начала дека и продолжает до конца
// При достижения конца функция завершает вывод и переходит на новую строку
{
    node* k; // Временный указатель на узел

    k = id; // Устанавливаем указатель на начало дека

    cout << "Дек: "; // Выводим сообщение о начале дека

    // Пока указатель на узел не равен NULL, продолжаем выводить элементы
    while (k != NULL)
    {
        cout << (*k).elem << " "; // Выводим элемент узла
        k = (*k).sled; // Переходим к следующему узлу
    }

    cout << endl; // Переходим на новую строку после вывода всех элементов
}

int Spisok::COUNT()
// Разработанная мной функция
// Она подсчитывает число элементов внутри дека возвращает это число
{
    node* k; // Временный указатель на узел
    int count = 0; // Счетчик элементов

    k = id; // Устанавливаем указатель на начало дека

    // Пока указатель на узел не равен NULL, продолжаем считать элементы
    while (k != NULL)
    {
        count++; // Увеличиваем счетчик
        k = (*k).sled; // Переходим к следующему узлу
    }

    return count; // Возвращаем количество элементов в деке
}

void Spisok::VSTAV1(int el)
// Функция создает новый узел, присваивает ему значение введенного элемента и добавляет его в конец дека
// Используется для  добавления элемента в конец дека
{
    node* k; // Временный указатель на узел

    k = new(node); // Создаем новый узел
    (*k).elem = el; // Присваиваем элементу узла значение введенного элемента
    (*k).sled = NULL; // Устанавливаем указатель на следующий узел в NULL

    // Если дек не пуст, то добавляем элемент в конец дека
    if (rd != NULL) {
        (*rd).sled = k; // Устанавливаем указатель на следующий узел текущего последнего узла на новый узел
        rd = k; // Обновляем указатель на конец дека на новый узел
    }
    else {
        // Если дек пуст, то новый узел становится единственным узлом в деке
        rd = k;
        id = k;
    }
}


void Spisok::VSTAV2(int el)
// Функция создает новый узел, присваивает ему значение введенного элемента и добавляет его в начало дека.
// Используется для  добавления элемента в начало дека
{

    node* k; // Временный указатель на узел

    k = new(node); // Создаем новый узел
    (*k).elem = el; // Присваиваем элементу узла значение введенного элемента
    (*k).sled = id; // Устанавливаем указатель на следующий узел на текущий первый узел

    // Если дек не пуст, то добавляем элемент в начало дека
    if (rd != NULL)
        id = k;
    else {
        // Если дек пуст, то новый узел становится единственным узлом в деке
        id = k;
        rd = k;
    }
}


void Spisok::YDALE1()
// Функция удаляет последний элемент дека

{
    node* z; // Временный указатель на узел
    node* k; // Временный указатель на узел

    // Если в деке только один элемент
    if (rd == id) {
        el_right = (*rd).elem; // Сохраняем значение элемента
        delete rd; // Удаляем узел
        id = rd = NULL; // Устанавливаем указатели на начало и конец дека в NULL
        cout << "Дек пуст!\n"; // Выводим сообщение о том, что дек пуст
    }
    else {
        // Если в деке больше одного элемента
        z = id; // Устанавливаем временный указатель на начало дека
        k = (*id).sled; // Устанавливаем временный указатель на второй узел дека

        // Продолжаем, пока не достигнем конца дека
        while (k != rd)
        {
            z = k; // Переходим к следующему узлу
            k = (*k).sled; // Переходим к следующему узлу
        }

        el_right = (*rd).elem; // Сохраняем значение последнего элемента
        (*z).sled = NULL; // Устанавливаем указатель на следующий узел предпоследнего узла в NULL
        delete rd; // Удаляем последний узел
        rd = z; // Обновляем указатель на конец дека
    }
}

void Spisok::YDALE2()
// Функция для удаления элемента из начала дека
{
    node* q; // Временный указатель на узел

    // Если дек не пуст
    if (id != NULL) {
        el_left = (*id).elem; // Сохраняем значение первого элемента
        q = id; // Сохраняем указатель на первый узел
        id = (*id).sled; // Обновляем указатель на начало дека на второй узел
        delete q; // Удаляем первый узел
    }
    else
        cout << "Дек пуст!\n"; // Выводим сообщение о том, что дек пуст
}


void Spisok::OCHISTKA()
// Очистка дека \ удаления всех его элементов
// Функция начинает с начала дека и продолжает до конца, удаляя каждый узел
// Когда достигнут конец дека (NULL), метод завершает удаление узлов
{
    node* k, * q; // Временные указатели на узлы
    k = id; // Устанавливаем указатель на начало дека

    // Если дек не пуст
    if (k != NULL) {
        q = (*k).sled; // Сохраняем указатель на второй узел

        // Пока не достигнем конца дека
        while (q != NULL)
        {
            delete k; // Удаляем текущий узел
            k = q; // Переходим к следующему узлу
            q = (*k).sled; // Обновляем указатель на следующий узел
        }

        delete k; // Удаляем последний узел
    }
}
