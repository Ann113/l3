#include "queue.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

Queue::~Queue() {
    clear();
}

void Queue::clear() {
    while (!isEmpty()) {
        dequeue(); 
    }
}

void Queue::enqueue(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

std::string Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    Node* temp = front;
    std::string value = temp->data;
    front = front->next;
    
    if (front == nullptr) {
        rear = nullptr;
    }
    
    delete temp;
    size--;
    return value;
}

std::string Queue::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return front->data;
}

void Queue::print() const {
    Node* current = front;
    std::cout << "Front -> ";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << " -> Rear" << std::endl;
}

void Queue::serializeToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    Node* current = front;
    while (current != nullptr) {
        int strSize = current->data.size();
        file.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
        file.write(current->data.c_str(), strSize);
        current = current->next;
    }
    
    file.close();
}

void Queue::deserializeFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    clear();
    
    int newSize;
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    
    for (int i = 0; i < newSize; i++) {
        int strSize;
        file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
        
        std::string value(strSize, '\0');
        file.read(&value[0], strSize);
        
        enqueue(value);
    }
    
    file.close();
}