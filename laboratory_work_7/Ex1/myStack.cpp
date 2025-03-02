#include <iostream>
#include <fstream>
#include "myStack.h"

void push(Stack*& st, double data) {
    Stack* pv = new Stack;
    pv->data = data;
    pv->next = st;
    st = pv;
}

void formUniqueStack(Stack*& st1, Stack*& st2, Stack*& result) {
    clear(result);
    Stack* current = st1;
    while (current != nullptr) {
        if (!contains(st2, current->data) && !contains(result, current->data)) {
            push(result, current->data);
        }
        current = current->next;
    }

    current = st2;
    while (current != nullptr) {
        if (!contains(st1, current->data) && !contains(result, current->data)) {
            push(result, current->data);
        }
        current = current->next;
    }
}

bool contains(Stack* st, double data) {
    Stack* current = st;
    while (current != nullptr) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void mergeStacks(Stack*& st1, Stack*& st2, Stack*& result) {
    double data;
    while (st1 != nullptr) {
        data = pop(st1);
        if (data != -1) {
            push(result, data);
        }
    }
    while (st2 != nullptr) {
        data = pop(st2);
        if (data != -1) {
            push(result, data);
        }
    }
}

double pop(Stack*& st) {
    if (st == nullptr) {
        cout << "Стек пуст!" << endl;
        return -1;
    }
    double data = st->data;
    Stack* pv = st;
    st = st->next;
    delete pv;
    return data;
}

void clear(Stack*& st) {
    while (st != nullptr) {
        pop(st);
    }
}

void toFile(Stack*& st) {
    ofstream out("stack.txt");
    if (!out) {
        cout << "Ошибка открытия файла для записи.\n";
        return;
    }
    Stack* current = st;
    while (current != nullptr) {
        out << current->data << endl;
        current = current->next;
    }
    out.close();
}

void fromFile(Stack*& st) {
    clear(st);
    ifstream in("stack.txt");
    if (!in) {
        cout << "Ошибка открытия файла для чтения.\n";
        return;
    }
    double data;
    Stack* tempStack = nullptr;
    while (in >> data) {
        push(tempStack, data);
    }
    in.close();
    while (tempStack != nullptr) {
        push(st, pop(tempStack));
    }
}

void show(Stack*& st) {
    if (st == nullptr) {
        cout << "Стек пуст!" << endl;
        return;
    }
    Stack* current = st;
    while (current != nullptr) {
        cout << current->data << ' ';
        current = current->next;
    }
    cout << '\n';
}