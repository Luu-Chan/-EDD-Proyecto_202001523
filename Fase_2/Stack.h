#ifndef STACK_H
#define STACK_H

#include <string>

class Stack {
private:
    struct Node {
        std::string email;
        Node* next;

        Node(const std::string& email) : email(email), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const std::string& email) {
        Node* newNode = new Node(email);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    std::string peek() const {
        if (top) {
            return top->email;
        }
        return "";
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    std::string display() const {
        std::string text = "";

        text += "Solicitudes Recibidas: \n";

        Node* current = top;
        while (current) {
            text += current->email;
            current = current->next;
        }
        return text;
    }
};

#endif // STACK_H

