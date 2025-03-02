#include <iostream>
#include <Windows.h>
#include "myStack.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    Stack* stack1 = nullptr, * stack2 = nullptr, * resultStack = nullptr;

    for (;;) {
        cout << "\tМеню\n";
        cout << "1 - Добавить элемент в стек 1\n";
        cout << "2 - Добавить элемент в стек 2\n";
        cout << "3 - Вывод стека 1 и 2\n";
        cout << "4 - Сформировать уникальный стек\n";
        cout << "5 - Вывести стек\n";
        cout << "6 - Сохранить стек в файл\n";
        cout << "7 - Считать стек из файла\n";
        cout << "8 - Очистить стек\n";
        cout << "9 - Выход\n";
        cout << "Выберите команду: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double value;
            cout << "Введите число для добавления в стек 1: ";
            cin >> value;
            push(stack1, value);
            break;
        }
        case 2: {
            double value;
            cout << "Введите число для добавления в стек 2: ";
            cin >> value;
            push(stack2, value);
            break;
        }
        case 3:
            cout << "Ваши стеки: " << endl;
            cout << "Стек 1: ";
            show(stack1);
            cout << "Стек 2: ";
            show(stack2);
            break;
        case 4:
            formUniqueStack(stack1, stack2, resultStack);
            cout << "Уникальный стек сформирован." << endl;
            break;
        case 5:
            cout << "Ваш уникальный стек: " << endl;
            show(resultStack);
            break;
        case 6:
            toFile(resultStack);
            cout << "Уникальный стек сохранён в файл." << endl;
            break;
        case 7:
            fromFile(resultStack);
            cout << "Уникальный стек считан из файла." << endl;
            break;
        case 8:
            clear(resultStack);
            cout << "Уникальный стек очищен." << endl;
            break;
        case 9:
            clear(stack1);
            clear(stack2);
            clear(resultStack);
            return 0;

        default:
            cout << "Неверная команда!\n";
        }
    }
    return 0;
}