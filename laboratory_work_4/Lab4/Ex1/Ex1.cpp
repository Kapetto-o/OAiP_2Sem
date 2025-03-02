#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

struct Student {
    string name;
    string admission_date;
    string specialty;
    string group;
    string faculty;
    double average_score;
};

void print_student(const Student& student) {
    cout << "Ф.И.О.: " << student.name << '\n';
    cout << "Дата поступления: " << student.admission_date << '\n';
    cout << "Специальность: " << student.specialty << '\n';
    cout << "Группа: " << student.group << '\n';
    cout << "Факультет: " << student.faculty << '\n';
    cout << "Средний балл: " << student.average_score << '\n';
}

void add_student(vector<Student>& students) {
    Student student;
    cout << "Введите Ф.И.О.: ";
    getline(cin, student.name);
    cout << "Введите дату поступления: ";
    getline(cin, student.admission_date);
    cout << "Введите специальность: ";
    getline(cin, student.specialty);
    cout << "Введите группу: ";
    getline(cin, student.group);
    cout << "Введите факультет: ";
    getline(cin, student.faculty);
    cout << "Введите средний балл: ";
    cin >> student.average_score;
    cin.ignore();
    students.push_back(student);
}

void print_students(const vector<Student>& students) {
    for (const auto& student : students) {
        print_student(student);
        cout << "---\n";
    }
}

void delete_student(vector<Student>& students) {
    string name;
    cout << "Введите Ф.И.О. студента, которого нужно удалить: ";
    getline(cin, name);
    students.erase(remove_if(students.begin(), students.end(),
        [&name](const Student& student) {
            return student.name == name;
        }), students.end());
}

void find_student(const vector<Student>& students) {
    string name;
    cout << "Введите Ф.И.О. студента, которого нужно найти: ";
    getline(cin, name);
    for (const auto& student : students) {
        if (student.name == name) {
            print_student(student);
            return;
        }
    }
    cout << "Студент не найден.\n";
}

void save_to_file(const vector<Student>& students) {
    ofstream outputFile("students.txt", ios::out | ios::binary);
    for (const auto& student : students) {
        outputFile.write((char*)&student, sizeof(Student));
    }
}

void load_from_file(vector<Student>& students) {
    ifstream inputFile("students.txt", ios::in | ios::binary);
    Student student;
    while (inputFile.read((char*)&student, sizeof(Student))) {
        students.push_back(student);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Student> students;
    while (true) {
        cout << "1. Добавить студента\n"
            << "2. Вывести студентов\n"
            << "3. Удалить студента\n"
            << "4. Найти студента\n"
            << "5. Сохранить в файл\n"
            << "6. Загрузить из файла\n"
            << "7. Выход\n"
            << "Выберите действие: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            add_student(students);
            break;
        case 2:
            print_students(students);
            break;
        case 3:
            delete_student(students);
            break;
        case 4:
            find_student(students);
            break;
        case 5:
            save_to_file(students);
            break;
        case 6:
            load_from_file(students);
            break;
        case 7:
            return 0;
        default:
            cout << "Неверный выбор.\n";
        }
    }
}