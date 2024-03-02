#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // Максимальный размер очереди

struct Queue {
    int front, rear;
    char elements[MAX_SIZE];

    Queue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (rear == MAX_SIZE - 1);
    }

    bool isEmpty() {
        return (front == -1);
    }

    void enqueue(char item) {
        if (isFull()) {
            cout << "Ошибка: очередь переполнена." << endl;
        } else {
            if (front == -1) {
                front = 0;
            }
            rear++;
            elements[rear] = item;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Очередь пуста." << endl;
        } else {
            cout << "Содержимое очереди: ";
            for (int i = front; i <= rear; i++) {
                cout << elements[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Queue q;
    int maxSize;
    char target, symbol;

    cout << "Введите максимальный размер очереди: ";
    cin >> maxSize;

    cout << "Введите эталонный символ: ";
    cin >> target;

    cout << "Введите символы (до встречи эталонного символа или достижения максимального размера очереди): ";
    while (cin >> symbol) {
        if (symbol == target || q.rear == maxSize - 1) {
            break;
        }
        q.enqueue(symbol);
    }

    q.display();

    return 0;
}

