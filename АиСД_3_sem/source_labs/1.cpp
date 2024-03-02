#include <iostream>
using namespace std;

class CharStack {
private:
    int maxSize;
    int top;
    char* stackArray;

public:
    CharStack(int size) {
        maxSize = size;
        top = -1;
        stackArray = new char[maxSize];
    }

    ~CharStack() {
        delete[] stackArray;
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == maxSize - 1);
    }

    void push(char value) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push element " << value << endl;
        }
        else {
            top++;
            stackArray[top] = value;
        }
    }

    char pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Cannot pop element." << endl;
            return '\0';
        }
        else {
            char value = stackArray[top];
            top--;
            return value;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
        }
        else {
            cout << "Stack elements: ";
            for (int i = top; i >= 0; i--) {
                cout << stackArray[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int maxSize;
    char target;

    cout << "Enter the maximum size of the stack: ";
    cin >> maxSize;

    CharStack stack(maxSize);

    cout << "Enter the target character: ";
    cin >> target;

    char input;
    cout << "Enter characters to push into the stack (stop when you encounter the target character): ";
    while (cin >> input && input != target) {
        stack.push(input);
    }

    cout << "Stack contents: ";
    stack.display();

    return 0;
}

