#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <regex>
#include <windows.h>

using namespace std;

struct Grade {
    string subject;
    int grade;
};

union Data {
    string* classId;
    vector<Grade>* grades;
};

struct Student {
    string name;
    Data data;
    float average;
    bool isClassId;
};

vector<Student> students;

// ВАЛИДАЦИЯ

bool validateName(string name) {                                                                // ФИО
    int spaceCount = count(name.begin(), name.end(), ' ');
    if (spaceCount < 1 || spaceCount > 2) {
        cout << "Некорректный ввод. ФИО должно состоять из 2 или 3 слов.\n";
        return false;
    }

    regex namePattern("^[А-ЯЁ][а-яё]*(-[А-ЯЁ][а-яё]*)?( [А-ЯЁ][а-яё]*(-[А-ЯЁ][а-яё]*)?){1,2}$");
    if (!regex_match(name, namePattern)) {
        cout << "Некорректный ввод. Каждое слово должно начинаться с заглавной буквы и продолжаться строчными.\n";
        return false;
    }

    return true;
}

bool validateClass(string classId) {                                                            // Класс
    regex classPattern("^([1-9]|1[01])( |-)?[А-Я]$");
    if (!regex_match(classId, classPattern)) {
        cout << "Некорректный ввод. Класс должен быть в формате Число-Буква, Число Буква или ЧислоБуква, где Число от 1 до 11, а Буква - любая заглавная русская буква.\n";
        return false;
    }
    return true;
}

bool validateSubject(string subject) {                                                          // Предмет
    regex subjectPattern("^[А-Яа-яёЁ\\s\\-.]+$");
    if (!regex_match(subject, subjectPattern)) {
        cout << "Некорректный ввод. Название предмета должно быть на русском языке и может содержать пробелы, '-' и '.'.\n";
        return false;
    }
    return true;
}

bool validateGrade(int grade) {                                                                 // Оценка
    if (grade < 1 || grade > 10) {
        cout << "Некорректный ввод. Оценка должна быть целым числом от 1 до 10.\n";
        return false;
    }
    return true;
}


// РЕАЛИЗАЦИЯ ФУНКЦИЙ

void input() {
    Student s;
    while (true) {
        cout << "Введите Ф.И.О.: ";
        getline(cin, s.name);
        if (validateName(s.name)) {
            break;
        }
        cin.clear();
        cin.sync();
    }
    s.data.classId = new string;
    while (true) {
        cout << "Введите класс (цифра+буква): ";
        getline(cin, *s.data.classId);
        if (validateClass(*s.data.classId)) {
            break;
        }
        cin.clear();
        cin.sync();
    }
    s.isClassId = true;

    s.data.grades = new vector<Grade>;
    int numGrades;
    cout << "Введите количество предметов: ";
    cin >> numGrades;
    cin.ignore();
    for (int i = 0; i < numGrades; ++i) {
        Grade g;
        while (true) {
            cout << "Введите предмет: ";
            getline(cin, g.subject);
            if (validateSubject(g.subject)) {
                break;
            }
            cin.clear();
            cin.sync();
        }
        while (true) {
            cout << "Введите оценку: ";
            cin >> g.grade;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Попробуйте еще раз.\n";
            }
            else if (validateGrade(g.grade)) {
                cin.ignore(10000, '\n');
                break;
            }
            else {
                cout << "Попробуйте еще раз.\n";
            }
        }
        s.data.grades->push_back(g);
    }
    s.isClassId = false;

    students.push_back(s);
}

float calculateAverage(const vector<Grade>& grades) {
    int sum = 0;
    for (const Grade& g : grades) {
        sum += g.grade;
    }
    return static_cast<float>(sum) / grades.size();
}

void display() {
    for (const Student& s : students) {
        cout << "Ф.И.О.: " << s.name << "\n";
        if (s.isClassId) {
            cout << "Класс: " << *s.data.classId << "\n";
        }
        else {
            for (const Grade& g : *s.data.grades) {
                cout << "Предмет: " << g.subject << "\tОценка: " << g.grade << "\n";
            }
            cout << "Средний балл: " << calculateAverage(*s.data.grades) << "\n";
        }
    }
}

void writeToFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        for (const Student& s : students) {
            file << "Ф.И.О.: " << s.name << "\n";
            if (s.isClassId) {
                file << "Класс: " << *s.data.classId << "\n";
            }
            else {
                for (const Grade& g : *s.data.grades) {
                    file << "Предмет: " << g.subject << "\tОценка: " << g.grade << "\n";
                }
                file << "Средний балл: " << calculateAverage(*s.data.grades) << "\n";
            }
            file << "\n";
        }
        file.close();
    }
    else {
        cout << "Не удалось открыть файл";
    }
}


void readFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    }
    else {
        cout << "Не удалось открыть файл";
    }
}

void search() {
    string name;
    cout << "Введите фамилию ученика: ";
    getline(cin, name);
    for (const Student& s : students) {
        if (s.name.find(name) != string::npos) {
            cout << "Ф.И.О.: " << s.name << "\n";
            if (s.isClassId) {
                cout << "Класс: " << *s.data.classId << "\n";
            }
            else {
                for (const Grade& g : *s.data.grades) {
                    cout << "Предмет: " << g.subject << "\tОценка: " << g.grade << "\n";
                }
                cout << "Средний балл: " << calculateAverage(*s.data.grades) << "\n";
            }
            break;
        }
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        cout << "\tГлавное меню\n\n";
        cout << "1. Добавить ученика\n";
        cout << "2. Показать данные учеников\n";
        cout << "3. Записать данные в файл\n";
        cout << "4. Прочитать данные из файла\n";
        cout << "5. Поиск\n";
        cout << "6. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();
        if (choice < 1 || choice > 6) {
            cout << "Неверный выбор. Попробуйте еще раз.\n";
            continue;
        }

        switch (choice) {
        case 1:
            input();
            break;
        case 2:
            display();
            break;
        case 3:
            writeToFile("students.txt");
            break;
        case 4:
            readFromFile("students.txt");
            break;
        case 5:
            search();
            break;
        case 6:
            cout << "Выход из программы.\n";
            break;
        }
    } while (choice != 6);

    return 0;
}