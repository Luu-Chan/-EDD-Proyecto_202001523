#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <string>

class ListaSimple {
private:
    struct Node {
        std::string email;
        Node* next;

        Node(const std::string& email) : email(email), next(nullptr) {}
    };

    Node* head;

public:
    ListaSimple() : head(nullptr) {}

    ~ListaSimple() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(const std::string& email) {
        Node* newNode = new Node(email);
        newNode->next = head;
        head = newNode;
    }

    std::string display() const {
        std::string text = "";

        text += "Solicitudes Enviadas: \n";

        Node* current = head;
        while (current) {
            text += current->email + "\n" ;
            current = current->next;
        }
        return text;
    }

    bool find(const std::string& email) const {
        Node* current = head;
        while (current) {
            if (current->email == email) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(const std::string& email) {
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->email == email) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};


#endif // LISTASIMPLE_H
