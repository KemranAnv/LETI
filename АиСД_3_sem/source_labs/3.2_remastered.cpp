#include <iostream>
#include <vector>

struct Node {
    int num;
    Node* next;
};

Node* createLinkedList(const std::vector<int>& arr) {
    if (arr.empty()) {
        return nullptr;
    }
    
    Node* head = new Node{arr[0], nullptr};
    Node* current = head;
    
    for (int i = 1; i < arr.size(); ++i) {
        current->next = new Node{arr[i], nullptr};
        current = current->next;
    }
    
    return head;
}

Node* rearrangeLinkedList(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* evenList = nullptr;
    Node* evenListTail = nullptr;
    Node* oddList = nullptr;
    Node* oddListTail = nullptr;
    
    while (head != nullptr) {
        if (head->num % 2 == 0) {
            if (evenList == nullptr) {
                evenList = evenListTail = head;
            } else {
                evenListTail->next = head;
                evenListTail = head;
            }
        } else {
            if (oddList == nullptr) {
                oddList = oddListTail = head;
            } else {
                oddListTail->next = head;
                oddListTail = head;
            }
        }
        
        head = head->next;
    }
    
    if (evenListTail != nullptr) {
        evenListTail->next = oddList;
        return evenList;
    } else {
        return oddList;
    }
}

void printLinkedList(Node* head) {
    while (head != nullptr) {
        std::cout << head->num << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

void printIndexList(const std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    Node* linkedList = createLinkedList(arr);
    std::cout << "Исходный список: ";
    printLinkedList(linkedList);
    
    Node* rearrangedList = rearrangeLinkedList(linkedList);
    std::cout << "Результирующий список: ";
    printLinkedList(rearrangedList);
    
    std::cout << "Индексы в результирующем списке: ";
    printIndexList(arr);
    
    return 0;
}

