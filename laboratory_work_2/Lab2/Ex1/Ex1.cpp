#pragma warning(disable: 4996)
#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_NUMBERS = 1000;

bool contains(int arr[], int size, int num) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");
    FILE* fileA = fopen("fileA.txt", "r");
    FILE* fileB = fopen("fileB.txt", "w");

    if (!fileA || !fileB) {
        cerr << "Ошибка при открытии файлов." << endl;
        return 1;
    }

    int numbers[MAX_NUMBERS], uniqueCount = 0, num;

    while (fscanf(fileA, "%d", &num) != EOF) {
        if (!contains(numbers, uniqueCount, num)) {
            numbers[uniqueCount] = num;
            ++uniqueCount;
        }
    }

    for (int i = 0; i < uniqueCount; ++i) {
        fprintf(fileB, "%d\n", numbers[i]);
    }

    fclose(fileA);
    fclose(fileB);

    cout << "Уникальные числа записаны в файл fileB.txt." << endl;

    return 0;
}   