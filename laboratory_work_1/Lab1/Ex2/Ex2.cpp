#include <iostream>
#include <string>
using namespace std;

int maxWordLength(const  string sentence, ...) {
    int maxLength = 0, length = 0;

    for (char c : sentence) {
        const  string *p = &sentence;
        if (c == ' ') {
            if (length > maxLength) {
                maxLength = length;
            }
            length = 0;
        }
        else {
            length++;
        }
    }

    if (length > maxLength) {
        maxLength = length;
    }
    return maxLength;
}

int main() {
    setlocale(LC_ALL, "RU");

    cout << "1. Самое длинное слово в предложениях состоит из " << maxWordLength("Предложение 1, произвольный текст", "Предложение 2, произвольный текст", "Предложение 3, произвольный текст", "Предложение 4, произвольный текст") << " букв" << endl;
    cout << "2. Самое длинное слово в предложениях состоит из " << maxWordLength("Предложение 1, произвольный текст", "Предложение 2, произвольный текст", "Предложение 3, произвольный текст", "Предложение 4, произвольный текст") << " букв" << endl;
    cout << "3. Самое длинное слово в предложениях состоит из " << maxWordLength("Предложение 1, произвольный текст", "Предложение 2, произвольный текст", "Предложение 3, произвольный текст", "Предложение 4, произвольный текст") << " букв" << endl;

    return 0;
}