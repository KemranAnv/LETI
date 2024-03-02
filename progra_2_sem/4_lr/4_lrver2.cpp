#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct City {
    string name;
    string region;
    int population;
    City* next;
    City* prev;
};
void addCity(City*& head, City*& tail);
void printRegions(City* head); 
void deleteCitiesByRegion(City*& head, City*& tail, const string& region); 
void clearList(City*& head, City*& tail); 

int main() {
    City* head = nullptr;
    City* tail = nullptr;
    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить город" << endl;
		cout << "2. Вывести названия регионов в порядке убывания численности населения" << endl;
		cout << "3. Удалить все города из региона" << endl;
		cout << "4. Очистить список" << endl;
		cout << "5. Выйти" << endl;
		int choice;
    	cin >> choice;
		if (choice == 1) {
		    addCity(head, tail);
		}
		else if (choice == 2) {
		    printRegions(head);
		}
		else if (choice == 3) {
		    cout << "Введите название региона: ";
		    string region;
		    cin >> region;
		    deleteCitiesByRegion(head, tail, region);
		}
		else if (choice == 4) {
		    clearList(head, tail);
		}
		else if (choice == 5) {
		    break;
		}
		else {
		    cout << "Некорректный выбор" << endl;
		}
	}
	return 0;
}

void addCity(City*& head, City*& tail) {
    City* city = new City;
    cout << "Введите название города: ";
    cin >> city->name;
    cout << "Введите название региона: ";
    cin >> city->region;
    cout << "Введите количество жителей: ";
    cin >> city->population;
    city->next = nullptr;
    city->prev = tail;
    if (tail != nullptr) {
        tail->next = city;
    }
    tail = city;
    if (head == nullptr) {
        head = city;
    }
    cout << "Город добавлен" << endl;
}

void printRegions(City* head) {
    struct Region {
        string name;
        int population = 0;
        bool operator<(const Region& other) const {
            return population > other.population;
        }
    };
    Region* regions = nullptr;
    int count = 0;
    City* current = head;
    while (current != nullptr) {
        Region* region = nullptr;
        for (int i = 0; i < count; i++) {
            if (regions[i].name == current->region) {
                region = &regions[i];
                break;
            }
        }
        if (region == nullptr) {
            count++;
            regions = (Region*) realloc(regions, count * sizeof(Region));
            region = &regions[count - 1];
            region->name = current->region;
        }
        region->population += current->population;
        current = current->next;
    }
    if (count == 0) {
        cout << "Список пуст" << endl;
        return;
    }
    sort(regions, regions + count);
    cout << "Названия регионов в порядке убывания численности населения:" << endl;
    for (int i = 0; i < count; i++) {
        cout << regions[i].name << endl;
    }
    free(regions);
}

void deleteCitiesByRegion(City*& head, City*& tail, const string& region) {
    City* current = head;
    while (current != nullptr) {
        if (current->region == region) {
            if (current == head) {
                head = current->next;
            }
            if (current == tail) {
                tail = current->prev;
            }
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            City* temp = current->next;
            delete current;
            current = temp;
        }
        else {
            current = current->next;
        }
    }
    cout << "Все города из региона " << region << " удалены" << endl;
}

void clearList(City*& head, City*& tail) {
    while (head != nullptr) {
        City* temp = head->next;
        delete head;
        head = temp;
    }
    tail = nullptr;
    cout << "Список очищен" << endl;
}


       

