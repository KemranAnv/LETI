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
void printList(Node* head);

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
    cout << "Количество вхождений равно: " << numOccurrences << endl;

    deleteListRecursive(head);
    printList(head);

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
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    } while (value != 0);
}

void insertNodesBeforeNegative(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;
    do {
        if (current->data < 0) {
            Node* newNode = new Node;
            newNode->data = 1;
            newNode->next = current;
            if (prev == nullptr) {
                head = newNode;
            } else {
                prev->next = newNode;
            }
            break;
        }
        prev = current;
        current = current->next;
    } while (current != head);
}

void deleteNegativeNodes(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;
    do {
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
    } while (current != head);
}

int countOccurrences(Node* head) {
    int num;
    cout << "Введите число, чтобы посчитать его вхождения: ";
    cin >> num;

    Node* current = head;
    int count = 0;
    do {
        if (current->data == num) {
            count++;
        }
        current = current->next;
    } while (current != head);
    return count;
}

void deleteListRecursive(Node*& head) {
    if (head == nullptr) {
        return;
    }
    Node* current = head->next;
    Node* prev = head;
    do {
        delete prev;
        prev = current;
        current = current->next;
    } while (current != head);
    delete prev;
    head = nullptr;
}

void printList(Node* head) {
    int quan = 0;
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    cout << "Список содержит: ";
    Node* current = head;
    do {
        quan++;
        if (quan == 10)
            return;
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
    
}
