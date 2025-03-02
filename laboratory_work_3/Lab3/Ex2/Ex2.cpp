#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void writeToFile(const vector<char>& str, const string& filename) {
    ofstream file(filename, ios::out | ios::binary);
    if (file.is_open()) {
        for (char c : str) {
            file << c;
        }
        file.close();
    }
}

vector<char> readFromFile(const string& filename) {
    vector<char> str;
    ifstream file(filename, ios::in | ios::binary);
    if (file.is_open()) {
        char c;
        while (file.get(c)) {
            str.push_back(c);
        }
        file.close();
    }
    return str;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<char> str;
    cout << "Введите строку: ";
    char c;
    while (cin.get(c) && c != '\n') {
        str.push_back(c);
    }

    string filename = "file.txt";
    writeToFile(str, filename);

    vector<char> fileContent = readFromFile(filename);

    vector<vector<char>> words;
    vector<char> word;
    for (char c : fileContent) {
        if (c == ' ') {
            words.push_back(word);
            word.clear();
        }
        else {
            word.push_back(c);
        }
    }
    words.push_back(word);

    int minIndex = 0;
    for (int i = 1; i < words.size(); ++i) {
        if (words[i].size() < words[minIndex].size()) {
            minIndex = i;
        }
    }

    cout << "Порядковый номер слова минимальной длины: " << minIndex + 1 << endl;
    cout << "Количество символов в слове: " << words[minIndex].size() << endl;
        
    return 0;
}