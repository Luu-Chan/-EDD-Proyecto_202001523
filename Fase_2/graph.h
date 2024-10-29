#ifndef GRAPH_H
#define GRAPH_H

#include "nodoG.h"
#include <string>
#include <vector>
class Graph
{

private:

    Node* head;  // Cabeza de la lista de usuarios
    std::vector<std::string> users;  // Lista de correos electrónicos para referencia por índice
    Node* findNode(int value);


public:
    Graph() : head(nullptr) {}

    void addUser(const std::string& email);
    int getUserIndex(const std::string& email);
    void addFriendship(const std::string& email1, const std::string& email2);
    std::string displayFriends(const std::string& email);
    std::string suggestFriends(const std::string& email);
    bool isDirectFriend(Node* user, int target);

    void generateAdjacencyListGraph(const std::string& filename);
    void generateCompleteGraph(const std::string& filename);
    void generateHighlightedGraph(const std::string& filename, const std::string& email);
};

#endif // GRAPH_H
