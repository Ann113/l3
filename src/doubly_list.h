#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <string>

class DoublyList {
private:
    struct Node {
        std::string data;
        Node* prev;
        Node* next;
        Node(const std::string& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;
    
    Node* findNode(const std::string& value) const;
    
public:
    DoublyList();
    ~DoublyList();
    
    // Запрет копирования
    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;
    
    // Основные операции
    void insertFront(const std::string& value);
    void insertBack(const std::string& value);
    void insertBefore(const std::string& target, const std::string& value);
    void insertAfter(const std::string& target, const std::string& value);
    
    void removeFront();
    void removeBack();
    void removeValue(const std::string& value);
    void removeBefore(const std::string& target);
    void removeAfter(const std::string& target);
    
    // Поиск
    bool search(const std::string& value) const;
    
    // Утилиты
    void printForward() const;
    void printBackward() const;
    int getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }
    void clear();
    
    // Сериализация
    void serializeToFile(const std::string& filename) const;
    void deserializeFromFile(const std::string& filename);
};

#endif