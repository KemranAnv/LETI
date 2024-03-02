#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Функция для замены значений переменных
void swap(int& a, int& b) {
    int temp = a; // Сохраняем значение a в промежуточной переменной temp
    a = b;        // Присваиваем a значение b
    b = temp;     // Присваиваем b значение temp (старое значение a)
}

// Пузырьковая сортировка
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Проверяем следующий элемент с предыдущим, и по условию
            // если следующий элемент больше предыдущего, то меняем их местами
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); // Используем функцию swap для обмена элементов
            }
        }
    }
}

// Метод выбора
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i; // Предполагаем, что текущий элемент минимальный
        // Находим индекс минимального элемента для текущего подмассива
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // Обновляем индекс минимального элемента
            }
        }
        // Меняем местами текущий элемент и минимальный элемент
        swap(arr[i], arr[minIndex]); // Используем функцию swap для обмена элементов
    }
}

// Метод вставки
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i]; // Запоминаем текущий элемент
        int j = i - 1;
        // Сравниваем текущий элемент с предыдущим и меняем местами, пока нужно
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Перемещаем элементы вправо
            j--;
        }
        arr[j + 1] = key; // Вставляем текущий элемент на правильное место
    }
}

// Метод Шелла
void shellSort(int arr[], int size) {
    int gap = 1;
    while (gap < size / 3) {
        gap = gap * 3 + 1; // Вычисление интервала Шелла
    }
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i]; // Запоминаем текущий элемент
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap]; // Перемещаем элементы вправо
                j -= gap;
            }
            arr[j] = temp; // Вставляем текущий элемент на правильное место
        }
        gap /= 3; // Уменьшаем интервал
    }
}

// Метод Хоара (быстрая сортировка)
int partition(int arr[], int low, int high) {
    int pivot = arr[low]; // Выбираем опорный элемент
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot); // Находим элемент, больший или равный опорному, слева
        do {
            j--;
        } while (arr[j] > pivot); // Находим элемент, меньший или равный опорному, справа
        if (i >= j) {
            return j; // Возвращаем индекс разделения
        }
        swap(arr[i], arr[j]); // Меняем местами элементы
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Получаем индекс разделения
        quickSort(arr, low, pi); // Рекурсивно сортируем левую часть
        quickSort(arr, pi + 1, high); // Рекурсивно сортируем правую часть
    }
}

// Функция для записи массива в файл
void writeArrayToFile(int arr[], int size, const string& fileName) {
    ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (int i = 0; i < size; i++) {
            outFile << arr[i] << " "; // Записываем элементы массива в файл
        }
        outFile.close();
    }
}

// Последовательный поиск
int sequentialSearch(int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}

// Бинарный поиск
int binarySearch(int arr[], int size, int target) {
    int count = 0;
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            count++;
            // Ищем дополнительные совпадения влево и вправо от найденной позиции
            int leftIdx = mid - 1;
            int rightIdx = mid + 1;
            while (leftIdx >= 0 && arr[leftIdx] == target) {
                count++;
                leftIdx--;
            }
            while (rightIdx < size && arr[rightIdx] == target) {
                count++;
                rightIdx++;
            }
            break;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return count;
}

int main() {
    int* a = nullptr;
    int* b = nullptr;
    int* c = nullptr;
    int* d = nullptr;
    int* e = nullptr;
    int size = 0;

    string menu = "Menu:\n1. Initialize arrays\n2. Result of bubble sort\n3. Result of selection sort\n4. Result of insertion sort\n5. Result of Shell sort\n6. Result of Hoare sort\n7. Search\n8. Exit";

    while (true) {
        cout << menu << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "Enter the size of the arrays: ";
                cin >> size;
                a = new int[size];
                b = new int[size];
                c = new int[size];
                d = new int[size];
                e = new int[size];
                cout << "Enter elements for array A: ";
                for (int i = 0; i < size; i++) {
                    cin >> a[i]; // Ввод элементов массива A
                }
                cout << "Enter elements for array B: ";
                for (int i = 0; i < size; i++) {
                    cin >> b[i]; // Ввод элементов массива B
                }
                cout << "Enter elements for array C: ";
                for (int i = 0; i < size; i++) {
                    cin >> c[i]; // Ввод элементов массива C
                }
                cout << "Enter elements for array D: ";
                for (int i = 0; i < size; i++) {
                    cin >> d[i]; // Ввод элементов массива D
                }
                cout << "Enter elements for array E: ";
                for (int i = 0; i < size; i++) {
                    cin >> e[i]; // Ввод элементов массива E
                }
                cout << "Arrays initialized." << endl;
                break;
            }
            case 2: {
                cout << "Result of bubble sort:" << endl;
                bubbleSort(a, size); // Сортировка массива A методом пузырьковой сортировки
                writeArrayToFile(a, size, "bubble_sort_result.txt"); // Запись результатов в файл
                for (int i = 0; i < size; i++) {
                    cout << a[i] << " "; // Вывод отсортированных элементов массива A
                }
                cout << endl;
                break;
            }
            case 3: {
                cout << "Result of selection sort:" << endl;
                selectionSort(b, size); // Сортировка массива B методом выбора
                writeArrayToFile(b, size, "selection_sort_result.txt"); // Запись результатов в файл
                for (int i = 0; i < size; i++) {
                    cout << b[i] << " "; // Вывод отсортированных элементов массива B
                }
                cout << endl;
                break;
            }
            case 4: {
                cout << "Result of insertion sort:" << endl;
                insertionSort(c, size); // Сортировка массива C методом вставки
                writeArrayToFile(c, size, "insertion_sort_result.txt"); // Запись результатов в файл
                for (int i = 0; i < size; i++) {
                    cout << c[i] << " "; // Вывод отсортированных элементов массива C
                }
                cout << endl;
                break;
            }
            case 5: {
                cout << "Result of Shell sort:" << endl;
                shellSort(d, size); // Сортировка массива D методом Шелла
                writeArrayToFile(d, size, "shell_sort_result.txt"); // Запись результатов в файл
                for (int i = 0; i < size; i++) {
                    cout << d[i] << " "; // Вывод отсортированных элементов массива D
                }
                cout << endl;
                break;
            }
            case 6: {
                cout << "Result of Hoare sort (Quick sort):" << endl;
                quickSort(e, 0, size - 1); // Сортировка массива E методом Хоара (быстрая сортировка)
                writeArrayToFile(e, size, "hoare_sort_result.txt"); // Запись результатов в файл
                for (int i = 0; i < size; i++) {
                    cout << e[i] << " "; // Вывод отсортированных элементов массива E
                }
                cout << endl;
                break;
            }
            case 7: {
                int searchTarget;
                cout << "Enter the element to search for: ";
                cin >> searchTarget;

                // Последовательный поиск
                int sequentialCountA = sequentialSearch(a, size, searchTarget);
                int sequentialCountB = sequentialSearch(b, size, searchTarget);
                int sequentialCountC = sequentialSearch(c, size, searchTarget);
                int sequentialCountD = sequentialSearch(d, size, searchTarget);
                int sequentialCountE = sequentialSearch(e, size, searchTarget);

                // Бинарный поиск (для отсортированных массивов)
                int binaryCountA = 0;
                int binaryCountB = 0;
                int binaryCountC = 0;
                int binaryCountD = 0;
                int binaryCountE = 0;

                int* sortedArrays[5] = { a, b, c, d, e };

                for (int i = 0; i < 5; i++) {
                    if (is_sorted(sortedArrays[i], sortedArrays[i] + size)) {
                        int binaryCount = binarySearch(sortedArrays[i], size, searchTarget);
                        switch (i) {
                            case 0: binaryCountA = binaryCount; break;
                            case 1: binaryCountB = binaryCount; break;
                            case 2: binaryCountC = binaryCount; break;
                            case 3: binaryCountD = binaryCount; break;
                            case 4: binaryCountE = binaryCount; break;
                        }
                    }
                }

                // Вывод результатов поиска
                cout << "Sequential Search Results:" << endl;
                cout << "Array A: " << sequentialCountA << " occurrences" << endl;
                cout << "Array B: " << sequentialCountB << " occurrences" << endl;
                cout << "Array C: " << sequentialCountC << " occurrences" << endl;
                cout << "Array D: " << sequentialCountD << " occurrences" << endl;
                cout << "Array E: " << sequentialCountE << " occurrences" << endl;

                cout << "Binary Search Results:" << endl;
                cout << "Array A: " << binaryCountA << " occurrences" << endl;
                cout << "Array B: " << binaryCountB << " occurrences" << endl;
                cout << "Array C: " << binaryCountC << " occurrences" << endl;
                cout << "Array D: " << binaryCountD << " occurrences" << endl;
                cout << "Array E: " << binaryCountE << " occurrences" << endl;

                // Запись результатов в файл
                ofstream searchResultFile("search_results.txt");
                if (searchResultFile.is_open()) {
                    searchResultFile << "Sequential Search Results:" << endl;
                    searchResultFile << "Array A: " << sequentialCountA << " occurrences" << endl;
                    searchResultFile << "Array B: " << sequentialCountB << " occurrences" << endl;
                    searchResultFile << "Array C: " << sequentialCountC << " occurrences" << endl;
                    searchResultFile << "Array D: " << sequentialCountD << " occurrences" << endl;
                    searchResultFile << "Array E: " << sequentialCountE << " occurrences" << endl;

                    searchResultFile << "Binary Search Results:" << endl;
                    searchResultFile << "Array A: " << binaryCountA << " occurrences" << endl;
                    searchResultFile << "Array B: " << binaryCountB << " occurrences" << endl;
                    searchResultFile << "Array C: " << binaryCountC << " occurrences" << endl;
                    searchResultFile << "Array D: " << binaryCountD << " occurrences" << endl;
                    searchResultFile << "Array E: " << binaryCountE << " occurrences" << endl;

                    searchResultFile.close();
                    cout << "Search results written to 'search_results.txt'." << endl;
                }
                else {
                    cout << "Error: Unable to write search results to file." << endl;
                }
                break;
            }
            case 8: {
                delete[] a;
                delete[] b;
                delete[] c;
                delete[] d;
                delete[] e;
                cout << "Exiting the program." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
    return 0;
}

