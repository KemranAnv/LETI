#include <iostream>
#include <string>
using namespace std;

// Структура для хранения информации о городе
struct City {
    string name;
    string region;
    int population;
    City* next;
    City* prev;
};

// Функция для добавления нового города в список
void addCity(City*& head, City*& tail) {
    string name, region;
    int population;
    cout << "Введите название города: ";
    cin >> name;
    cout << "Введите название региона: ";
    cin >> region;
    cout << "Введите количество жителей: ";
    cin >> population;
    City* newCity = new City {name, region, population, nullptr, tail};
    if (tail != nullptr) {
        tail->next = newCity;
    }
    tail = newCity;
    if (head == nullptr) {
        head = newCity;
    }
    cout << "Город " << name << " добавлен" << endl;
}

// Структура для хранения информации о регионе и суммарной численности населения его городов
struct RegionPopulation {
    string region;
    int population;
};

// Функция для вывода на экран названий регионов в порядке убывания численности населения
void printRegions(City* head) {
    RegionPopulation regions[100];
    int numRegions = 0;
    City* current = head;
    while (current != nullptr) {
        bool found = false;
        for (int i = 0; i < numRegions; i++) {
            if (regions[i].region == current->region) {
                regions[i].population += current->population;
                found = true;
                break;
            }
        }
        if (!found) {
            regions[numRegions] = {current->region, current->population};
            numRegions++;
        }
        current = current->next;
    }
    for (int i = 0; i < numRegions; i++) {
        for (int j = i + 1; j < numRegions; j++) {
            if (regions[i].population < regions[j].population) {
                RegionPopulation temp = regions[i];
                regions[i] = regions[j];
                regions[j] = temp;
            }
        }
    }
    for (int i = 0; i < numRegions; i++) {
        cout << regions[i].region << " - " << regions[i].population << " жителей" << endl;
    }
}

// Функция для удаления всех городов указанного региона из списка
void deleteCitiesByRegion(City*& head, City*& tail, string region) {
    City* current = head;
    while (current != nullptr) {
        if (current->region == region) {
            if (current == head) {
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
                else {
                    tail = nullptr;
                }
                delete current;
                current = head;
            }
            else if (current == tail) {
                tail = current->prev;
                tail->next = nullptr;
                delete current;
                current = nullptr;
            }
            else {
                            current->prev->next = current->next;
            current->next->prev = current->prev;
            City* temp = current->next;
            delete current;
            current = temp;
        }
    }
    else {
        current = current->next;
    }
}
cout << "Все города из региона " << region << " удалены" << endl;
}

// Функция для очистки списка
void clearList(City*& head, City*& tail) {
while (head != nullptr) {
City* temp = head->next;
delete head;
head = temp;
}
tail = nullptr;
cout << "Список очищен" << endl;
}

int main() {
City* head = nullptr;
City* tail = nullptr;
while (true) {
cout << endl;
cout << "Выберите действие:" << endl;
cout << "1 - Добавить город" << endl;
cout << "2 - Вывести названия регионов в порядке убывания численности населения" << endl;
cout << "3 - Удалить города указанного региона" << endl;
cout << "4 - Очистить список" << endl;
cout << "5 - Выйти из программы" << endl;
int choice;
cin >> choice;
switch (choice) {
case 1:
addCity(head, tail);
break;
case 2:
printRegions(head);
break;
case 3: {
string region;
cout << "Введите название региона: ";
cin >> region;
deleteCitiesByRegion(head, tail, region);
break;
}
case 4:
clearList(head, tail);
break;
case 5:
return 0;
default:
cout << "Неверный выбор" << endl;
}
}
}


