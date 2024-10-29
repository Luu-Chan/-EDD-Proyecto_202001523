#include "graph.h"
#include <algorithm>
#include <unordered_set>
#include "qdebug.h"


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
                text +=  users[current->value] + " " + "\n";
                current = current->next;
            }
        }
    }
    return text;
}


// Encontrar el índice de un usuario por su correo
int Graph::getUserIndex(const std::string& email) {
    auto it = std::find(users.begin(), users.end(), email);
    if (it != users.end()) {
        return std::distance(users.begin(), it);
    }
    return -1;  // No encontrado
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
        text +=  users[suggestion.first] + " (" +  std::to_string(suggestion.second) + " amigos en común)" + "\n";
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

// Genera el archivo .dot para la lista de adyacencia del grafo
void Graph::generateAdjacencyListGraph(const std::string& filename) {
    std::ofstream outFile(filename);
    outFile << "digraph g {\n";
    outFile << "  rankdir=LR;\n";  // Dirección de izquierda a derecha para mostrar listas

    Node* currentNode = head;
    while (currentNode) {
        // Nodo principal con su valor
        outFile << "  \"Nodo" << currentNode->value << "\" [label=\""
                << users[currentNode->value] << "\", shape=box];\n";

        // Genera la lista de vecinos horizontalmente
        Neighbor* neighbor = currentNode->neighbors;
        std::string previousNeighbor = "Nodo" + std::to_string(currentNode->value);
        while (neighbor) {
            std::string neighborLabel = "Nodo" + std::to_string(currentNode->value) + "_Amigo" + std::to_string(neighbor->value);

            outFile << "  \"" << neighborLabel << "\" [label=\""
                    << users[neighbor->value] << "\", shape=ellipse, style=filled, fillcolor=lightgray];\n";

            // Conectar nodo principal con su primer vecino y luego en cadena a cada vecino siguiente
            outFile << "  \"" << previousNeighbor << "\" -> \"" << neighborLabel << "\" [dir=none];\n";
            previousNeighbor = neighborLabel;

            neighbor = neighbor->next;
        }

        currentNode = currentNode->next;
    }

    outFile << "}\n";
    outFile.close();
    // Generar la imagen utilizando Graphviz
    std::string comando = "dot -Tpng " + filename + " -o " + filename + ".png";
    system(comando.c_str());

    qDebug() << "Archivo DOT generado con éxito: "<< filename<< ".png" ;
}

// Genera el archivo .dot para el grafo completo
void Graph::generateCompleteGraph(const std::string& filename) {
    std::ofstream outFile(filename);
    outFile << "graph G {\n";

    Node* currentNode = head;
    std::unordered_set<std::string> edges;

    while (currentNode) {
        Neighbor* neighbor = currentNode->neighbors;
        while (neighbor) {
            std::string edge = users[currentNode->value] < users[neighbor->value]
                                   ? users[currentNode->value] + "--" + users[neighbor->value]
                                   : users[neighbor->value] + "--" + users[currentNode->value];

            if (edges.find(edge) == edges.end()) {
                outFile << "  \"" << users[currentNode->value] << "\" -- \""
                        << users[neighbor->value] << "\";\n";
                edges.insert(edge);
            }
            neighbor = neighbor->next;
        }
        currentNode = currentNode->next;
    }

    outFile << "}\n";
    outFile.close();
    // Generar la imagen utilizando Graphviz
    std::string comando = "dot -Tpng " + filename + " -o " + filename + ".png";
    system(comando.c_str());

    qDebug() << "Archivo DOT generado con éxito: "<< filename<< ".png" ;
}

// Genera el archivo .dot resaltando un usuario específico, amigos y sugerencias
void Graph::generateHighlightedGraph(const std::string& filename, const std::string& email) {
    std::ofstream outFile(filename);
    outFile << "graph G {\n";

    int idx = getUserIndex(email);
    if (idx == -1) return;

    Node* userNode = findNode(idx);
    if (!userNode) return;

    // Agregar todo el grafo
    Node* currentNode = head;
    std::unordered_set<std::string> edges;
    while (currentNode) {
        Neighbor* neighbor = currentNode->neighbors;
        while (neighbor) {
            std::string edge = users[currentNode->value] < users[neighbor->value]
                                   ? users[currentNode->value] + "--" + users[neighbor->value]
                                   : users[neighbor->value] + "--" + users[currentNode->value];

            if (edges.find(edge) == edges.end()) {
                outFile << "  \"" << users[currentNode->value] << "\" -- \""
                        << users[neighbor->value] << "\";\n";
                edges.insert(edge);
            }
            neighbor = neighbor->next;
        }
        currentNode = currentNode->next;
    }

    // 1. Resaltar el usuario principal
    outFile << "  \"" << users[idx] << "\" [style=filled, fillcolor=lightblue, color=blue, fontcolor=white];\n";

    // 2. Resaltar los amigos directos en color verde
    Neighbor* directFriend = userNode->neighbors;
    while (directFriend) {
        outFile << "  \"" << users[directFriend->value] << "\" [style=filled, fillcolor=lightgreen, color=green];\n";
        outFile << "  \"" << users[idx] << "\" -- \"" << users[directFriend->value] << "\" [color=green];\n";
        directFriend = directFriend->next;
    }

    // 3. Resaltar amigos de amigos (sugerencias) en color amarillo con intensidad basada en amigos en común
    std::unordered_map<int, int> suggestionScores;
    directFriend = userNode->neighbors;
    while (directFriend) {
        Node* friendNode = findNode(directFriend->value);
        Neighbor* friendsOfFriend = friendNode->neighbors;

        while (friendsOfFriend) {
            if (friendsOfFriend->value != idx && !isDirectFriend(userNode, friendsOfFriend->value)) {
                suggestionScores[friendsOfFriend->value]++;
            }
            friendsOfFriend = friendsOfFriend->next;
        }
        directFriend = directFriend->next;
    }

    // Agregar sugerencias con colores según la ponderación
    for (const auto& suggestion : suggestionScores) {
        std::string color = (suggestion.second > 2) ? "goldenrod" : "yellow";
        outFile << "  \"" << users[suggestion.first] << "\" [style=filled, fillcolor=" << color << "];\n";
        outFile << "  \"" << users[idx] << "\" -- \"" << users[suggestion.first] << "\" [style=dashed, color=orange];\n";
    }

    outFile << "}\n";
    outFile.close();
    // Generar la imagen utilizando Graphviz
    std::string comando = "dot -Tpng " + filename + " -o " + filename + ".png";
    system(comando.c_str());

    qDebug() << "Archivo DOT generado con éxito: "<< filename<< ".png" ;

}
