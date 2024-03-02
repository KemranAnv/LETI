#include <iostream>
#include <fstream>
using namespace std;

// Функция для замены значений переменных
void swap(int& a, int& b) {
    int temp = a; // Вводим промежуточную переменную
    a = b;
    b = temp;
}

// Пузырьковая сортировка
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Проверяем следующий элемент с предыдущим, и по условию
            // если следующий элемент больше предыдущего, то меняем их местами
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Метод выбора
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        // Находим индекс минимального элемента для текущего подмассива
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Меняем местами текущий элемент и минимальный элемент
        swap(arr[i], arr[minIndex]);
    }
}

// Метод вставки
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        // Сравниваем текущий элемент с предыдущим и меняем местами, пока нужно
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Метод Шелла
void shellSort(int arr[], int size) {
    int gap = 1;
    while (gap < size / 3) {
        gap = gap * 3 + 1;
    }
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap /= 3;
    }
}

// Метод Хоара (быстрая сортировка)
int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (arr[j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int* a = nullptr;
    int* b = nullptr;
    int* c = nullptr;
    int* d = nullptr;
    int* e = nullptr;
    int size = 0;

    string menu = "Menu:\n1. Initialize arrays\n2. Result of bubble sort\n3. Result of selection sort\n4. Result of insertion sort\n5. Result of Shell sort\n6. Result of Hoare sort\n7. Exit";

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
                    cin >> a[i];
                }
                cout << "Enter elements for array B: ";
                for (int i = 0; i < size; i++) {
                    cin >> b[i];
                }
                cout << "Enter elements for array C: ";
                for (int i = 0; i < size; i++) {
                    cin >> c[i];
                }
                cout << "Enter elements for array D: ";
                for (int i = 0; i < size; i++) {
                    cin >> d[i];
                }
                cout << "Enter elements for array E: ";
                for (int i = 0; i < size; i++) {
                    cin >> e[i];
                }
                cout << "Arrays initialized." << endl;
                break;
            }
            case 2: {
                cout << "Result of bubble sort:" << endl;
                bubbleSort(a, size);
                for (int i = 0; i < size; i++) {
                    cout << a[i] << " ";
                }
                cout << endl;
                break;
            }
            case 3: {
                cout << "Result of selection sort:" << endl;
                selectionSort(b, size);
                for (int i = 0; i < size; i++) {
                    cout << b[i] << " ";
                }
                cout << endl;
                break;
            }
            case 4: {
                cout << "Result of insertion sort:" << endl;
                insertionSort(c, size);
                for (int i = 0; i < size; i++) {
                    cout << c[i] << " ";
                }
                cout << endl;
                break;
            }
            case 5: {
                cout << "Result of Shell sort:" << endl;
                shellSort(d, size);
                for (int i = 0; i < size; i++) {
                    cout << d[i] << " ";
                }
                cout << endl;
                break;
            }
            case 6: {
                cout << "Result of Hoare sort (Quick sort):" << endl;
                quickSort(e, 0, size - 1);
                for (int i = 0; i < size; i++) {
                    cout << e[i] << " ";
                }
                cout << endl;
                break;
            }
            case 7: {
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

