#include <iostream>
#include <string>
 
using namespace std;

struct CityNode {
    string name;
    string region;
    int population;
    CityNode* prev;
    CityNode* next;
};

class CityList {
private:
    CityNode* head;
    CityNode* tail;

public:
    CityList() {
        head = nullptr;
        tail = nullptr;
    }

    ~CityList() {
        CityNode* current_node = head;
        while (current_node != nullptr) {
            CityNode* next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
    }

    void add_city(string name, string region, int population) {
        CityNode* new_node = new CityNode;
        new_node->name = name;
        new_node->region = region;
        new_node->population = population;
        new_node->prev = nullptr;

        if (tail == nullptr) {
            new_node->next = nullptr;
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = tail->next;
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }

    void print_regions_by_population() {
        // Создаем массив регионов и заполняем его суммарной численностью населения
        struct RegionPopulation {
            string region;
            int population;
        };
        const int MAX_REGIONS = 100;
        RegionPopulation regions[MAX_REGIONS];
        int regions_count = 0;

        CityNode* current_node = head;
        while (current_node != nullptr) {
            bool found_region = false;
            for (int i = 0; i < regions_count; i++) {
                if (regions[i].region == current_node->region) {
                    regions[i].population += current_node->population;
                    found_region = true;
                    break;
                }
            }
            if (!found_region) {
                regions[regions_count].region = current_node->region;
                regions[regions_count].population = current_node->population;
                regions_count++;
            }
            current_node = current_node->next;
        }

        // Сортируем массив регионов по убыванию численности населения
        for (int i = 0; i < regions_count - 1; i++) {
            for (int j = i + 1; j < regions_count; j++) {
                if (regions[j].population > regions[i].population) {
                    RegionPopulation temp = regions[i];
                    regions[i] = regions[j];
                    regions[j] = temp;
                }
            }
        }

        // Выводим отсортированный массив регионов
        for (int i = 0; i < regions_count; i++) {
            cout << regions[i].region << ": " << regions[i].population << endl;
        }
    }

    void remove_cities_by_region(string region) {
        CityNode* current_node = head;
        while (current_node != nullptr) {
            if (current_node->region == region) {
                CityNode* node_to_delete = current_node;

                if (current_node == head) {
                    head = current_node->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    }
                } else if (current_node == tail) {
                    tail = current_node->prev;
                    tail->next = nullptr;
                } else {
                    current_node->prev->next = current_node->next;
                    current_node->next->prev = current_node->prev;
                }

                current_node = current_node->next;
                delete node_to_delete;
            } else {
                current_node = current_node->next;
            }
        }
    }

    void clear() {
        CityNode* current_node = head;
        while (current_node != nullptr) {
            CityNode* node_to_delete = current_node;
            current_node = current_node->next;
            delete node_to_delete;
        }
        head = nullptr;
        tail = nullptr;
    }
};

int main() {
    CityList cities;

    // Попросим пользователя добавлять города в список, пока он не введет пустое название
    while (true) {
        string name, region;
        int population;
        cout << "Введите название города (пустая строка для завершения): ";
        getline(cin, name);
        if (name.empty()) {
            break;
        }
        cout << "Введите название региона: ";
        getline(cin, region);
        cout << "Введите количество жителей: ";
        cin >> population;
        cin.ignore();

        cities.add_city(name, region, population);
    }

    // Выведем регионы по численности населения
    cout << "Регионы по численности населения: " << endl;
    cities.print_regions_by_population();

    // Попросим пользователя удалить города определенного региона
    string region_to_delete;
    cout << "Введите название региона, из которого нужно удалить города: ";
    getline(cin, region_to_delete);
    cities.remove_cities_by_region(region_to_delete);

    //Заново выводим регионы
    cities.print_regions_by_population();

    cout << "Очистка списка...\n";
    // Очистим список
    cities.clear();
    cout << "Список очищен";

    return 0;
}

