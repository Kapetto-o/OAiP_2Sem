#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    const char* FILE1 = "FILE1.txt";
    const char* FILE2 = "FILE2.txt";
    int N1, N2;

    cout << " Введите интервал строк: ";
    cin >> N1;
    cin >> N2;

    if (N1 > N2) {
        swap(N1, N2);
    }

    ifstream inputFile(FILE1, ios::in | ios::binary);
    ofstream outputFile(FILE2, ios::out | ios::binary);

    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла " << FILE1 << endl;
        return 1;
    }

    string line;
    int currentLine = 0;

    while (getline(inputFile, line)) {
        currentLine++;

        if (currentLine >= N1 && currentLine <= N2 && !line.empty() && line[0] == 'С') {
            outputFile << line << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    ifstream countFile(FILE2, ios::in | ios::binary);
    if (countFile.is_open()) {
        getline(countFile, line);
        int wordCount = 0;

        for (char c : line) {
            if (c == ' ' || c == '\t') {
                wordCount++;
            }
        }

        if (!line.empty()) {
            wordCount++;
        }

        cout << "Количество слов в первой строке файла " << FILE2 << ": " << wordCount << endl;
        countFile.close();
    }
    else {
        cout << "Ошибка открытия файла " << FILE2 << endl;
    }

    return 0;
}