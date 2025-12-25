#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <string>

class SinglyList {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;
    
    Node* findNode(const std::string& value) const;
    Node* findNodeBefore(const std::string& value) const;
    
public:
    SinglyList();
    ~SinglyList();
    
    SinglyList(const SinglyList&) = delete;
    SinglyList& operator=(const SinglyList&) = delete;
    
    void insertFront(const std::string& value);
    void insertBack(const std::string& value);
    void insertBefore(const std::string& target, const std::string& value);
    void insertAfter(const std::string& target, const std::string& value);
    
    void removeFront();
    void removeBack();
    void removeValue(const std::string& value);
    void removeBefore(const std::string& target);
    void removeAfter(const std::string& target);
    
    bool search(const std::string& value) const;
    
    void printForward() const;
    int getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }
    void clear();
    
    void serializeToFile(const std::string& filename) const;
    void deserializeFromFile(const std::string& filename);
};

#endif