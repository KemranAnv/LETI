#include <iostream>

using namespace std;

// определение структуры узла списка
struct Node {
    int data;
    Node* next;
};

// функция добавления элемента в конец списка
void enqueue(Node*& front, Node*& rear, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    if (rear == nullptr) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

// функция удаления элемента из начала списка
int dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) {
        return 0;
    }
    int value = front->data;
    Node* temp = front;
    if (front == rear) {
        front = rear = nullptr;
    }
    else {
        front = front->next;
    }
    delete temp;
    return value;
}

// функция вывода списка на экран
void printList(Node* front) {
    cout << "List: ";
    while (front != nullptr) {
        cout << front->data << " ";
        front = front->next;
    }
    cout << endl;
}

// функция вставки узла с информационной частью = 1 во все позиции списка,
// предшествующие узлам с отрицательной информационной частью
void insertBeforeNegative(Node*& front, Node*& rear) {
    Node* current = front;
    while (current != nullptr) {
        if (current->data < 0) {
            break;
        }
        Node* newNode = new Node;
        newNode->data = 1;
        newNode->next = current;
        if (current == front) {
            front = newNode;
        }
        current = current->next;
    }
}

// функция удаления всех узлов списка, содержащих в информационной части отрицательные числа
void removeNegative(Node*& front, Node*& rear) {
    Node* current = front;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data < 0) {
            Node* temp = current;
            current = current->next;
            if (prev == nullptr) {
                front = current;
            }
            else {
                prev->next = current;
            }
            if (temp == rear) {
                rear = prev;
            }
            delete temp;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

// функция расчета количества вхождений заданного с клавиатуры числа в информационные поля узлов
int countOccurrences(Node* front, int value) {
    int count = 0;
    while (front != nullptr) {
        if (front->data == value) {
            count++;
        }
        front = front->next;
    }
    return count;
}

// функция рекурсивного удаления всех узлов списка
void deleteList(Node*& front) {
    if (front != nullptr) {
            deleteList(front->next);
    delete front;
    front = nullptr;
}
}

int main() {
// построение списка
Node* front = nullptr;
Node* rear = nullptr;
int value;
do {
cout << "Enter a value (0 to end): ";
cin >> value;
if (value != 0) {
enqueue(front, rear, value);
}
} while (value != 0);
// вывод исходного списка
printList(front);

// вставка узлов с информационной частью = 1 во все позиции списка,
// предшествующие узлам с отрицательной информационной частью
insertBeforeNegative(front, rear);

// вывод списка после вставки узлов
printList(front);

// удаление всех узлов списка, содержащих в информационной части отрицательные числа
removeNegative(front, rear);

// вывод списка после удаления узлов
printList(front);

// расчет количества вхождений заданного с клавиатуры числа в информационные поля узлов
int searchValue;
cout << "Enter a value to search: ";
cin >> searchValue;
int count = countOccurrences(front, searchValue);
cout << "Occurrences of " << searchValue << ": " << count << endl;

// рекурсивное удаление всех узлов списка
deleteList(front);

return 0;
}