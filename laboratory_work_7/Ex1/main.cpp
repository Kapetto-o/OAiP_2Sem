#include <iostream>
#include <Windows.h>
#include "myStack.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    Stack* stack1 = nullptr, * stack2 = nullptr, * resultStack = nullptr;

    for (;;) {
        cout << "\t����\n";
        cout << "1 - �������� ������� � ���� 1\n";
        cout << "2 - �������� ������� � ���� 2\n";
        cout << "3 - ����� ����� 1 � 2\n";
        cout << "4 - ������������ ���������� ����\n";
        cout << "5 - ������� ����\n";
        cout << "6 - ��������� ���� � ����\n";
        cout << "7 - ������� ���� �� �����\n";
        cout << "8 - �������� ����\n";
        cout << "9 - �����\n";
        cout << "�������� �������: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double value;
            cout << "������� ����� ��� ���������� � ���� 1: ";
            cin >> value;
            push(stack1, value);
            break;
        }
        case 2: {
            double value;
            cout << "������� ����� ��� ���������� � ���� 2: ";
            cin >> value;
            push(stack2, value);
            break;
        }
        case 3:
            cout << "���� �����: " << endl;
            cout << "���� 1: ";
            show(stack1);
            cout << "���� 2: ";
            show(stack2);
            break;
        case 4:
            formUniqueStack(stack1, stack2, resultStack);
            cout << "���������� ���� �����������." << endl;
            break;
        case 5:
            cout << "��� ���������� ����: " << endl;
            show(resultStack);
            break;
        case 6:
            toFile(resultStack);
            cout << "���������� ���� ������� � ����." << endl;
            break;
        case 7:
            fromFile(resultStack);
            cout << "���������� ���� ������ �� �����." << endl;
            break;
        case 8:
            clear(resultStack);
            cout << "���������� ���� ������." << endl;
            break;
        case 9:
            clear(stack1);
            clear(stack2);
            clear(resultStack);
            return 0;

        default:
            cout << "�������� �������!\n";
        }
    }
    return 0;
}