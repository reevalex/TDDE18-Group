#include "list.h"
using namespace std;

Sorted_List::Sorted_List() : head(nullptr) {}

Sorted_List::~Sorted_List()
{
    while (head != nullptr)
    {
        auto *temp = head;
        head = head->next;
        delete temp;
    }
}

Sorted_List::Sorted_List(const Sorted_List &other) : head(nullptr)
{
    head = copyNodes(other.head);
}

Sorted_List &Sorted_List::operator=(const Sorted_List &other)
{
    if (this == &other)
    {
        return *this;
    }

    while (head)
    {
        auto *temp = head;
        head = head->next;
        delete temp;
    }

    head = copyNodes(other.head);

    return *this;
}

Sorted_List::Sorted_List(Sorted_List &&other) noexcept : head(other.head)
{
    other.head = nullptr;
}

Sorted_List &Sorted_List::operator=(Sorted_List &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    while (head)
    {
        auto *temp = head;
        head = head->next;
        delete temp;
    }

    head = other.head;
    other.head = nullptr;

    return *this;
}

size_t Sorted_List::size() const
{
    size_t count = 0;
    Node *current = head;

    while (current != nullptr)
    {
        ++count;
        current = current->next;
    }
    return count;
}

int Sorted_List::at(size_t index) const
{
    size_t i = 0;
    Node *current = head;

    while (current != nullptr && i < index)
    {
        current = current->next;
        ++i;
    }

    if (current == nullptr)
    {
        throw out_of_range("Index out of range");
    }

    return current->value;
}

void Sorted_List::insert(int value)
{
    Node *n = new Node(value);

    if (!head || value < head->value)
    {
        n->next = head;
        head = n;
        return;
    }

    Node *current = head;

    while (current->next && current->next->value < value)
    {
        current = current->next;
    }

    n->next = current->next;
    current->next = n;
}

bool Sorted_List::remove(int value)
{
    if (!head) // empty list nothing to remove
    {
        return false;
    }

    if (head->value == value)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node *current = head;
    while (current->next && current->next->value != value)
    {
        current = current->next;
    }

    if (!current->next) // not found
    {
        return false;
    }

    Node *temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

Sorted_List::Node *Sorted_List::copyNodes(const Node *src)
{
    if (!src)
    {
        return nullptr;
    }

    Node *newHead = new Node(src->value);
    Node *tail = newHead;

    for (const Node *n = src->next; n; n = n->next)
    {
        tail->next = new Node(n->value);
        tail = tail->next;
    }
    return newHead;
}

void Sorted_List::print() const
{
    printRecursive(head);
    std::cout << std::endl;
}

void Sorted_List::printRecursive(const Node *n) const
{
    if (!n)
    {
        return;
    }

    std::cout << n->value;
    if (n->next)
    {
        std::cout << " ";
    }
    printRecursive(n->next);
}