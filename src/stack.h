#ifndef STACK_H
#define STACK_H

#include <string>

class Stack {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& value) : data(value), next(nullptr) {}
    };
    
    Node* top;
    int size;
    
public:
    // Конструкторы и деструктор
    Stack();
    ~Stack();
    
    // Запрет копирования
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    
    // Основные операции
    void push(const std::string& value);
    std::string pop();
    std::string peek() const; 
    
    // Утилиты
    bool isEmpty() const { return top == nullptr; }
    int getSize() const { return size; }
    void clear();
    void print() const;
    
    // Сериализация
    void serializeToFile(const std::string& filename) const;
    void deserializeFromFile(const std::string& filename);
};

#endif