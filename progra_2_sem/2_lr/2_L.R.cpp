#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void push(Node** head, int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = (*head);
    (*head) = newNode;
}

void insertNodes(Node** head) {
    int data;
    cout << "Введите значения для списка (0 для окончания ввода): ";
    cin >> data;
    while (data != 0) {
        push(head, data);
        cin >> data;
    }
}

void printList(Node* node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

void insertOnesBeforeNegatives(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* current = *head;
    while (current != NULL) {
        if (current->data < 0) {
            break;
        }
        Node* newNode = new Node;
        newNode->data = 1;
        newNode->next = current;
        if (current == *head) {
            *head = newNode;
        } else {
            Node* prev = *head;
            while (prev->next != current) {
                prev = prev->next;
            }
            prev->next = newNode;
        }
        current = newNode->next;
    }
    
}

void deleteNegatives(Node** head) {
    Node* current = *head;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->data < 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            Node* tmp = current;
            current = current->next;
            delete tmp;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int countOccurrence(Node* head, int key) {
    int count = 0;
    while (head != NULL) {
        if (head->data == key) {
            count++;
        }
        head = head->next;
    }
    return count;
}

void recursiveDelete(Node** head) {
    if (*head == NULL) {
        return;
    }
    recursiveDelete(&((*head)->next));
    delete *head;
    *head = NULL;
}

int main() {
    Node* head = NULL;
    insertNodes(&head);

    cout << "Исходный список: ";
    printList(head);

    insertOnesBeforeNegatives(&head);
    cout << "Список после вставки единиц перед отрицательными числами: ";
    printList(head);

    deleteNegatives(&head);
    cout << "Список после удаления отрицательных чисел: ";
    printList(head);

    int key;
    cout << "Введите число для поиска в списке: ";
    cin >> key;
    int count = countOccurrence(head, key);
    cout << "Число " << key << " встречается в списке " << count << " раз(а)." << endl;

    recursiveDelete(&head);
    cout << "Список после рекурсивного удаления всех узлов: ";
    printList(head);

    return 0;
}