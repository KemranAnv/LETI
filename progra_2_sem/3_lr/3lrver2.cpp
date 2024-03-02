#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertNodes(Node*& head, Node*& tail);

void insertNodesBeforeNegative(Node*& head);

void deleteNegativeNodes(Node*& head);

int countOccurrences(Node* head);

void deleteListRecursive(Node*& head);

void printList(Node* head, Node* tail);

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    insertNodes(head, tail);
    printList(head, tail);

    insertNodesBeforeNegative(head);
    printList(head, tail);

    deleteNegativeNodes(head);
    printList(head, tail);

    int numOccurrences = countOccurrences(head);
    cout << "Количество вхождений равно: " << numOccurrences << endl;

    deleteListRecursive(head);
    printList(head, tail);

    return 0;
}
void insertNodes(Node*& head, Node*& tail) {
    int value;
    do {
        cout << "Введите значение (0 для окончания ввода): ";
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
            Node* newNode = new Node;
            newNode->data = 1;
            newNode->next = current;
            if (prev == nullptr) {
                head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
        }
        prev = current;
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
    cout << "Введите число, чтобы посчитать его вхождения: ";
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

void printList(Node* head, Node* tail) {
    if ( head == nullptr) {
        cout << "Список пуст" << endl;
    } else {
        cout << "Список содержит: ";
        Node* current = head;
        while (current != tail -> next) {
            cout << current -> data << " ";
            current = current->next;
        }
        cout << endl;
    }
}