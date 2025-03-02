#pragma warning(disable: 4996)
#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    int minCharCount;
    cout << "Введите минимальное количество символов: ";
    cin >> minCharCount;

    FILE* fileF1Read = fopen("F1.txt", "r");
    if (!fileF1Read) {
        cerr << "Не удалось открыть файл F1.txt для чтения" << endl;
        return 1;
    }

    FILE* fileF2 = fopen("F2.txt", "w");
    if (!fileF2) {
        cerr << "Не удалось открыть файл F2.txt" << endl;
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fileF1Read)) {
        if (strlen(line)-1 > static_cast<size_t>(minCharCount)) {
            fprintf(fileF2, "%s", line);
        }
    }
    
    fclose(fileF1Read);
    fclose(fileF2);

    cout << "Скопированные строки записаны в файл F2.txt." << endl;

    return 0;
}