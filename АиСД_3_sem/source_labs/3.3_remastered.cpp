#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Исходный массив целых чисел
    int dataArr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(dataArr) / sizeof(dataArr[0]);

    // Создаем массив индексов для представления списка
    vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        indices[i] = i;
    }

    // Переупорядочиваем массив индексов
    vector<int> evenIndices;
    vector<int> oddIndices;

    // Разделяем индексы на четные и нечетные
    for (int i = 0; i < n; ++i) {
        if (dataArr[indices[i]] % 2 == 0) {
            evenIndices.push_back(indices[i]);
        } else {
            oddIndices.push_back(indices[i]);
        }
    }

    // Обновляем массив индексов в нужном порядке
    evenIndices.insert(evenIndices.end(), oddIndices.begin(), oddIndices.end());

    // Выводим результирующий массив индексов
    cout << "Результат:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << evenIndices[i] << " ";
    }
    cout << endl;

    return 0;
}

