#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void add_student(string student);

struct Students {
	string name;
	string admission_date;
	string specialty;
	string group;
	string faculty;
	float average_score;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string student;

	cout << "\t База данных Студентов" << endl;
	while (true) {
		int choice;
		cout << "\n1. Добавить студента \n2. Вывод студентов\n3. Удалить студента\n4. Найти студента\n5. Сохранить в файл\n6. Загрузить из файла\n7. Завершить работу\nВыберите один из вариантов: ";
		cin >> choice;
		switch (choice) {
		case 1:
			add_student(student);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			return 0;
		default:
			cout << "Выбран несуществующий вариант. Повторите попытку\n";
		}
	}

}
void add_student(string student) {
	Students student;

	cout << "Введите Ф.И.О.: ";
	getline(cin, student.name);
	cout << "\nВведите дату поступления: ";
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

	cout << "Студент записан" << endl;
}