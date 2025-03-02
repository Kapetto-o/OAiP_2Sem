#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
/*
#include <cctype> 
#include <cwctype>
#include <locale>
#include <codecvt>
*/

using namespace std;

enum Days { Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

string getDayName(Days day) {
    switch (day) {
    case Monday: return "Понедельник";
    case Tuesday: return "Вторник";
    case Wednesday: return "Среда";
    case Thursday: return "Четверг";
    case Friday: return "Пятница";
    case Saturday: return "Суббота";
    case Sunday: return "Воскресенье";
    default: return "Неизвестный день";
    }
}

struct Time {
    unsigned int hours : 5;
    unsigned int minutes : 6;
};

struct Train {
    int number;
    string destination;
    vector<Days> days;
    Time arrival;
    Time departure;
};

vector<Train> trains;

/// ВАЛИДАЦИЯ

bool isNumber(const string& str) {
    for (char c : str) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

bool isValidNumber(const string& str) {                 // Номер поезда
    try {
        stoi(str);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool isTrainNumberExists(int number) {
    for (const auto& train : trains) {
        if (train.number == number) {
            return true;
        }
    }
    return false;
}

bool isValidDestination(const string& str) {            // Место назначение
    if (str.empty()) {
        return false;
    }
    vector<string> words;
    string word;
    for (char c : str) {
        if (c == '-') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    for (const string& word : words) {
        if (!(word[0] >= 'А' && word[0] <= 'Я')) {
            return false;
        }
        for (size_t i = 1; i < word.size(); ++i) {
            if (!((word[i] >= 'а' && word[i] <= 'я'))) {
                return false;
            }
        }
    }
    return true;
}

bool isValidDay(const string& str) {                // День следования
    if (!isNumber(str)) {
        return false;
    }
    int day = stoi(str);
    return day >= 0 && day <= 7;
}

bool isValidTime(const string& str) {                   // Время
    if (str.size() != 5 || str[2] != ':') {
        return false;
    }
    string hoursStr = str.substr(0, 2);
    string minutesStr = str.substr(3, 2);
    if (!isNumber(hoursStr) || !isNumber(minutesStr)) {
        return false;
    }
    int hours = stoi(hoursStr);
    int minutes = stoi(minutesStr);
    return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
}

// РЕАЛИЗАЦИЯ ФУНКЦИЙ

void addTrain() {
    cout << "\n\n";
    cout << "\tДобавление поезда" << endl;
    cout << "\n";
    Train train;
    string input;
    int day, hours, minutes;

    cout << "Введите номер поезда: ";
    cin >> input;
    while (!isValidNumber(input) || isTrainNumberExists(stoi(input))) {
        if (!isValidNumber(input)) {
            cout << "Неверный ввод. Попробуйте ввести только числовое значение: ";
        }
        else {
            cout << "Поезд с таким номером уже существует. Попробуйте другой номер: ";
        }
        cin >> input;
    }
    train.number = stoi(input);

    cin.ignore();
    cout << "Введите пункт назначения: ";
    getline(cin, train.destination);
    while (!isValidDestination(train.destination)) {
        cout << "Неверный ввод. Попробуйте ввести русскими символами с большой буквы: ";
        getline(cin, train.destination);
    }
    cout << "Введите дни следования (1 - Понедельник, 2 - Вторник, ..., 7 - Воскресенье, 0 - конец ввода): ";
    string dayStr;
    while (cin >> dayStr && dayStr != "0") {
        while (!isValidDay(dayStr)) {
            cout << "Неверный ввод. Введите число от 1 до 7, или 0 для завершения ввода: ";
            cin >> dayStr;
        }
        day = stoi(dayStr);
        train.days.push_back(static_cast<Days>(day));
    }

    string time;
    do {
        cout << "Введите время прибытия (формат чч:мм): ";
        cin >> time;
        if (!isValidTime(time)) {
            cout << "Неверный формат времени. Попробуйте еще раз.\n";
        }
    } while (!isValidTime(time));
    train.arrival.hours = stoi(time.substr(0, 2));
    train.arrival.minutes = stoi(time.substr(3, 2));

    do {
        cout << "Введите время отправления (формат чч:мм): ";
        cin >> time;
        if (!isValidTime(time)) {
            cout << "Неверный формат времени. Попробуйте еще раз.\n";
        }
    } while (!isValidTime(time));
    train.departure.hours = stoi(time.substr(0, 2));
    train.departure.minutes = stoi(time.substr(3, 2));

    trains.push_back(train);
    cout << "\n\n";
}

void displayTrains() {
    cout << "\n\n";
    cout << "\tСохранённые поезда:" << endl;
    for (const auto& train : trains) {
        cout << "\n";
        cout << "Номер поезда: " << train.number << "\n";
        cout << "Пункт назначения: " << train.destination << "\n";
        cout << "Дни следования: ";
        for (const auto& day : train.days) {
            cout << getDayName(day) << " ";
        }
        cout << "\n";
        cout << "Время прибытия: " << train.arrival.hours << ":" << train.arrival.minutes << "\n";
        cout << "Время отправления: " << train.departure.hours << ":" << train.departure.minutes << "\n";
    }
    cout << "\n\n";
}

void deleteTrain() {
    cout << "\n\n";
    cout << "\tУдаление поезда" << endl;
    cout << "\n";
    string destination;
    cout << "Введите пункт назначения для удаления поезда: ";
    cin >> destination;
    for (auto it = trains.begin(); it != trains.end(); ++it) {
        if (it->destination == destination) {
            trains.erase(it);
            cout << "Поезд с пунктом назначения " << destination << " удален.\n";
            cout << "\n\n";
            return;
        }
    }
    cout << "Поезд с пунктом назначения " << destination << " не найден.\n";
    cout << "\n\n";
}

void findTrain() {
    cout << "\n\n";
    cout << "\tПоиск поезда" << endl;
    cout << "\n";
    string destination;
    cout << "Введите пункт назначения для поиска поезда: ";
    cin >> destination;
    for (const auto& train : trains) {
        if (train.destination == destination) {
            cout << "\n";
            cout << "Номер поезда: " << train.number << "\n";
            cout << "Пункт назначения: " << train.destination << "\n";
            cout << "Дни следования: ";
            for (const auto& day : train.days) {
                cout << getDayName(day) << " ";
            }
            cout << "\n";
            cout << "Время прибытия: " << train.arrival.hours << ":" << train.arrival.minutes << "\n";
            cout << "Время отправления: " << train.departure.hours << ":" << train.departure.minutes << "\n";
            cout << "\n\n";
            return;
        }
    }
    cout << "Поезд с пунктом назначения " << destination << " не найден.\n";
    cout << "\n\n";
}


// ВИД ПРОГРАММЫ

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        cout << "\tГлавное меню\n\n";
        cout << "1. Добавить поезд\n";
        cout << "2. Показать поезда\n";
        cout << "3. Удалить поезд\n";
        cout << "4. Найти поезд\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice < 1 || choice > 5) {
            cout << "Неверный выбор. Попробуйте еще раз.\n";
            continue;
        }

        switch (choice) {
        case 1:
            addTrain();
            break;
        case 2:
            displayTrains();
            break;
        case 3:
            deleteTrain();
            break;
        case 4:
            findTrain();
            break;
        case 5:
            cout << "Выход из программы.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}