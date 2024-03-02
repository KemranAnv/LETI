#include <iostream>

// Структура для представления узла в бинарном дереве
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Функция для вставки элемента в упорядоченное бинарное дерево
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Функция для обхода бинарного дерева в прямом порядке (preorder)
void preorderTraversal(Node* root) {
    if (root != nullptr) {
        std::cout << root->data << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Функция для обхода бинарного дерева в симметричном порядке (inorder)
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

// Функция для обхода бинарного дерева в обратном порядке (postorder)
void postorderTraversal(Node* root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << root->data << " ";
    }
}

int main() {
    int n;
    std::cout << "Введите количество элементов множества: ";
    std::cin >> n;

    Node* root = nullptr;

    std::cout << "Введите элементы множества: ";
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        root = insert(root, value);
    }

    std::cout << "Прямой обход дерева: ";
    preorderTraversal(root);
    std::cout << std::endl;

    std::cout << "Симметричный обход дерева: ";
    inorderTraversal(root);
    std::cout << std::endl;

    std::cout << "Обратный обход дерева: ";
    postorderTraversal(root);
    std::cout << std::endl;

    return 0;
}

