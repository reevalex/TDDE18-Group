#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstddef>
#include <stdexcept>

class Sorted_List
{
private:
    struct Node
    {
        int value;
        Node *next;

        Node(int v, Node *n = nullptr) : value(v), next(n) {}
    };

    Node *head;

    Node *copyNodes(const Node *src);

public:
    Sorted_List();                                    // Constructor
    ~Sorted_List();                                   // Destructor
    Sorted_List(const Sorted_List &other);            // Constructor Copy
    Sorted_List &operator=(const Sorted_List &other); // Assigment Copy
    Sorted_List(Sorted_List &&other) noexcept;
    Sorted_List &operator=(Sorted_List &&other) noexcept;

    std::size_t size() const;
    int at(std::size_t index) const;

    void insert(int value);
    bool remove(int value);
    void print() const;
    void printRecursive(const Node *n) const;
};

#endif