#include "graph.h"
#include <algorithm>


// Encontrar el nodo por su valor (índice)
Node* Graph::findNode(int value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value)
            return current;
        current = current->next;
    }
    return nullptr;
}

// Agregar un usuario al grafo
void Graph::addUser(const std::string& email) {
    users.push_back(email);
    Node* newNode = new Node(users.size() - 1);  // El valor es el índice del usuario
    newNode->next = head;
    head = newNode;
}

// Encontrar el índice de un usuario por su correo
int Graph::getUserIndex(const std::string& email) {
    auto it = std::find(users.begin(), users.end(), email);
    if (it != users.end()) {
        return std::distance(users.begin(), it);
    }
    return -1;  // No encontrado
}

// Crear una amistad entre dos usuarios
void Graph::addFriendship(const std::string& email1, const std::string& email2) {
    int idx1 = getUserIndex(email1);
    int idx2 = getUserIndex(email2);

    if (idx1 != -1 && idx2 != -1) {
        Node* user1 = findNode(idx1);
        Node* user2 = findNode(idx2);
        if (user1 && user2) {
            user1->insertNeighbor(idx2);
            user2->insertNeighbor(idx1);  // Como es no dirigido, se agrega la arista en ambos
        }
    }
}

// Mostrar las amistades de un usuario
std::string Graph::displayFriends(const std::string& email) {
    std::string text = "";

    int idx = getUserIndex(email);
    if (idx != -1) {
        Node* user = findNode(idx);
        if (user) {
            text += + "Amigos de " + email + ": " + "\n";
            Neighbor* current = user->neighbors;
            while (current != nullptr) {
                text +=  users[current->value] + " ";
                current = current->next;
            }
        }
    }
    return text;
}

// Sugerencias de amistad basadas en amigos en común
std::string Graph::suggestFriends(const std::string& email) {
    std::string text = "";
    int idx = getUserIndex(email);
    if (idx == -1) return text;

    Node* user = findNode(idx);
    if (!user) return text;

    std::vector<int> suggestionScores(users.size(), 0);
    Neighbor* directFriend = user->neighbors;

    // Recorre los amigos directos y cuenta los amigos de amigos
    while (directFriend != nullptr) {
        Node* friendNode = findNode(directFriend->value);
        Neighbor* friendNeighbor = friendNode->neighbors;

        while (friendNeighbor != nullptr) {
            if (friendNeighbor->value != idx && !isDirectFriend(user, friendNeighbor->value)) {
                suggestionScores[friendNeighbor->value]++;
            }
            friendNeighbor = friendNeighbor->next;
        }
        directFriend = directFriend->next;
    }

    // Ordenar y mostrar sugerencias
    std::vector<std::pair<int, int>> suggestions;
    for (int i = 0; i < suggestionScores.size(); ++i) {
        if (suggestionScores[i] > 0) {
            suggestions.emplace_back(i, suggestionScores[i]);
        }
    }

    std::sort(suggestions.begin(), suggestions.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;  // Ordenar por puntuación de mayor a menor
    });

    text +=  "Sugerencias de amistad para " + email + ":\n";
    for (const auto& suggestion : suggestions) {
        text +=  users[suggestion.first] + " (" +  std::to_string(suggestion.second) + " amigos en común)";
    }
    return text;
}

// Verificar si un usuario ya es amigo directo de otro
bool Graph::isDirectFriend(Node* user, int target) {
    Neighbor* current = user->neighbors;
    while (current != nullptr) {
        if (current->value == target) {
            return true;
        }
        current = current->next;
    }
    return false;
}

