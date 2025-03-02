#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>
using namespace std;

int countMaxWordLength(const string& sentence) {
    int maxLength = 0, length = 0;
    for (char c : sentence) {
        if (c == ' ') {
            maxLength = max(maxLength, length);
            length = 0;
        }
        else {
            length++;
        }
    }
    maxLength = max(maxLength, length);
    return maxLength;
}

void findLongestWord(const char* sentence, ...) {
    setlocale(LC_ALL, "Russian");
    va_list sentences;
    va_start(sentences, sentence);
    while (sentence != nullptr) {
        cout << "Максимальная длина слова в предложении \"" << sentence << "\": " << countMaxWordLength(sentence) <<" букв" << endl;
        sentence = va_arg(sentences, const char*);
    }
    va_end(sentences);
}

int main() {
    setlocale(LC_ALL, "Russian");

    findLongestWord("У нас есть кошка", "Он любит чай", "Это маленьрирапци ывстрицьт стцпрцсицьоупцт сткий дом", "Я вижу большое дерево", nullptr);
    findLongestWord("Она читает интересную книгу", "Мой друг играет на гитаре", "На столе лежит красный ящик", nullptr);
    findLongestWord("Вечером мы гуляем в парке", "Солнце светит ярко", nullptr);

    return 0;
}