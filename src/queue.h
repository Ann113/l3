#ifndef QUEUE_H
#define QUEUE_H

#include <string>

class Queue {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& value) : data(value), next(nullptr) {}
    };
    
    Node* front;
    Node* rear;
    int size;
    
public:
    // Конструкторы и деструктор
    Queue();
    ~Queue();
    
    // Запрет копирования
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    
    // Основные операции
    void enqueue(const std::string& value);
    std::string dequeue();
    std::string peek() const;
    
    // Утилиты
    bool isEmpty() const { return front == nullptr; }
    int getSize() const { return size; }
    void clear();
    void print() const;
    
    // Сериализация
    void serializeToFile(const std::string& filename) const;
    void deserializeFromFile(const std::string& filename);
};

#endif