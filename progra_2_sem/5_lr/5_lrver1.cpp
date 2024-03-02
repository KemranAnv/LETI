#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

const int HASH_TABLE_SIZE = 23; // размер хэш-таблицы

// Функция хэширования, которая возвращает номер ячейки в хэш-таблице для заданного слова
int hash_function(string word);

// Класс, представляющий хэш-таблицу
class HashTable {
private:
    vector<list<string>> Htable; 		     // хранилище элементов таблицы

public:
    // Конструктор
    HashTable() {
        Htable.resize(HASH_TABLE_SIZE); 	     // инициализируем хранилище заданной размерностью
    }

    // Функция добавления слова в хэш-таблицу
    void add_word(string word); 
    
    // Функция поиска слова в хэш-таблице
    bool search_word(string word);

};

void HashTable::add_word(string word)
{
	int index = hash_function(word);     // вычисляем номер ячейки
    Htable[index].push_back(word);        // добавляем слово в соответствующую ячейку
}

bool HashTable::search_word(string word) 
{
    int index = hash_function(word);     						  // вычисляем номер ячейки
    auto& words = Htable[index];          						  // получаем список слов для данной ячейки
    return find(words.begin(), words.end(), word) != words.end(); // осуществляем поиск слова в списке
}



int main() {
    HashTable hash_table;                    // создаем хэш-таблицу

    // Читаем слова с клавиатуры и добавляем их в хэш-таблицу
    cout << "Enter words (type \"exit\" to finish):\n";
    string word;
    while (cin >> word) {
        if (word == "exit") break;
        hash_table.add_word(word);
    }

    // Ищем слово в хэш-таблице
    cout << "Enter a word to search: ";
    cin >> word;
    if (hash_table.search_word(word)) {
        cout << "The word \"" << word << "\" was found.\n";
    } else {
        cout << "The word \"" << word << "\" was not found.\n";
    }


    return 0;
}
// Функция хэширования, которая возвращает номер ячейки в хэш-таблице для заданного слова
int hash_function(string word) {
    return word[0] - 'a'; 					  // используем первую букву слова для вычисления номера ячейки
}












