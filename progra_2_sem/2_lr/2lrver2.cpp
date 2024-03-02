#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertNodes(Node*& head, Node*& tail) {
    int value;
    do {
        cout << "Enter a value (0 to end input): ";
        cin >> value;
        if (value == 0) {
            break;
        }
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    } while (value != 0);
}

void insertNodesBeforeNegative(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data < 0) {
            break;
        }
        if (current->data == 1) {
            Node* newNode = new Node;
            newNode->data = 1;
            newNode->next = current;
            if (prev == nullptr) {
                head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
        } else {
            prev = current;
        }
        current = current->next;
    }
}

void deleteNegativeNodes(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data < 0) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            Node* temp = current;
            current = current->next;
            delete temp;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int countOccurrences(Node* head) {
    int num;
    cout << "Enter a number to count its occurrences: ";
    cin >> num;

    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        if (current->data == num) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void deleteListRecursive(Node*& head) {
    if (head == nullptr) {
        return;
    }
    deleteListRecursive(head->next);
    delete head;
    head = nullptr;
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "The list is empty" << endl;
    } else {
        cout << "The list contains: ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    insertNodes(head, tail);
    printList(head);

    insertNodesBeforeNegative(head);
    printList(head);

    deleteNegativeNodes(head);
    printList(head);

    int numOccurrences = countOccurrences(head);
    cout << "The number of occurrences is: " << numOccurrences << endl;

    deleteListRecursive(head);
    printList(head);

    return 0;
}

/*
Программа сначала создает пустой список и запрашивает у пользователя ввод целочисленных значений. После ввода каждого значения оно добавляется в конец списка с помощью функции `enqueue`. Ввод прекращается, когда пользователь вводит число 0.

Затем программа выводит содержимое списка на экран и выполняет функцию `insertOnes`, которая вставляет новые узлы со значением 1 перед узлами со значением меньше 0.

После этого программа выполняет функцию `deleteNegatives`, которая удаляет все узлы со значением меньше 0 из списка.

Затем программа запрашивает у пользователя число для поиска и выполняет функцию `countOccurrences`, которая подсчитывает количество вхождений числа в список.

Наконец, программа выполняет функцию `deleteList`, которая рекурсивно удаляет все узлы списка, освобождая выделенную для них память.

Код написан на языке C++ с использованием стандартных библиотек ввода-вывода и операций со строками, поэтому для его компиляции и запуска необходимо использовать компилятор C++ (например, g++ или clang++) и входные/выходные потоки cin и cout.
*/

