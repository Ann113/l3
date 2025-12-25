#include "stack.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

Stack::Stack() : top(nullptr), size(0) {}

Stack::~Stack() {
    clear();
}

void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(const std::string& value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    size++;
}

std::string Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    
    Node* temp = top;
    std::string value = temp->data;
    top = top->next;
    delete temp;
    size--;
    
    return value;
}

std::string Stack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top->data;
}

void Stack::print() const {
    Node* current = top;
    std::cout << "Top -> ";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << " -> Bottom" << std::endl;
}

void Stack::serializeToFile(const std::string& filename) const {
    // Для стека сохраняем в обратном порядке, чтобы при загрузке восстановить порядок
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    // Сначала собираем все элементы в вектор
    std::vector<std::string> elements;
    Node* current = top;
    while (current != nullptr) {
        elements.push_back(current->data);
        current = current->next;
    }
    
    // Сохраняем в обратном порядке (чтобы при загрузке push восстанавливал порядок)
    int elemSize = elements.size();
    file.write(reinterpret_cast<const char*>(&elemSize), sizeof(elemSize));
    
    for (int i = elemSize - 1; i >= 0; i--) {
        int strSize = elements[i].size();
        file.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
        file.write(elements[i].c_str(), strSize);
    }
    
    file.close();
}

void Stack::deserializeFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    clear();
    
    int elemSize;
    file.read(reinterpret_cast<char*>(&elemSize), sizeof(elemSize));
    
    for (int i = 0; i < elemSize; i++) {
        int strSize;
        file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
        
        std::string value(strSize, '\0');
        file.read(&value[0], strSize);
        
        // Push в стек (восстанавливаем порядок)
        push(value);
    }
    
    file.close();
}