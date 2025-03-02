#include <iostream>
#include <Windows.h>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(int data) {
        Node* temp = new Node;
        temp->data = data;
        temp->next = nullptr;

        if (front == nullptr) {
            front = temp;
            rear = temp;
        }
        else {
            rear->next = temp;
            rear = temp;
        }
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Очередь пуста." << endl;
        }
        else {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void display() {
        if (front == nullptr) {
            cout << "Очередь пуста." << endl;
        }
        else {
            Node* temp = front;
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    int size() {
        int count = 0;
        Node* temp = front;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    int getFront() {
        if (front != nullptr) {
            return front->data;
        }
        else {
            cout << "Очередь пуста." << endl;
            return -1;
        }
    }

    void clear() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

void createQueues(Queue& q, Queue& q1, Queue& q2) {
    while (q.size() != 0) {
        int element = q.getFront();
        q.dequeue();

        if (element % 2 == 0) {
            q1.enqueue(element);
        }
        else {
            q2.enqueue(element);
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Queue q, q1, q2;
    int size, element, choice;

    cout << "Введите максимальный размер очереди: ";
    cin >> size;

    do {
        cout << "\n1. Добавить элемент в очередь\n";
        cout << "2. Удалить элемент из очереди\n";
        cout << "3. Показать элементы очереди\n";
        cout << "4. Разделить очередь на две\n";
        cout << "5. Показать текущий размер очереди\n";
        cout << "6. Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (q.size() < size) {
                q1.clear();
                q2.clear();

                cout << "Введите элемент: ";
                cin >> element;
                q.enqueue(element);
            }
            else {
                cout << "Очередь полна." << endl;
            }
            break;
        case 2:
            q.dequeue();
            break;
        case 3:
            q.display();
            break;
        case 4:
            createQueues(q, q1, q2);
            cout << "Элементы очереди Queue1 (четные): ";
            q1.display();
            cout << "Элементы очереди Queue2 (нечетные): ";
            q2.display();
            break;
        case 5:
            cout << "Текущий размер очереди: " << q.size() << endl;
            break;
        case 6:
            break;
        default:
            cout << "Неверный выбор." << endl;
        }
    } while (choice != 6);
    return 0;
}