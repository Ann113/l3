#include "doubly_list.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

DoublyList::DoublyList() : head(nullptr), tail(nullptr), size(0) {}

DoublyList::~DoublyList() {
    clear();
}

void DoublyList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

DoublyList::Node* DoublyList::findNode(const std::string& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DoublyList::insertFront(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

void DoublyList::insertBack(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void DoublyList::insertBefore(const std::string& target, const std::string& value) {
    Node* targetNode = findNode(target);
    if (targetNode == nullptr) {
        return;  // target не найден
    }
    
    Node* newNode = new Node(value);
    
    if (targetNode == head) {
        // Вставка перед головой
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else {
        // Вставка в середину
        newNode->prev = targetNode->prev;
        newNode->next = targetNode;
        targetNode->prev->next = newNode;
        targetNode->prev = newNode;
    }
    size++;
}

void DoublyList::insertAfter(const std::string& target, const std::string& value) {
    Node* targetNode = findNode(target);
    if (targetNode == nullptr) {
        return;  // target не найден
    }
    
    Node* newNode = new Node(value);
    
    if (targetNode == tail) {
        // Вставка после хвоста
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        // Вставка в середину
        newNode->prev = targetNode;
        newNode->next = targetNode->next;
        targetNode->next->prev = newNode;
        targetNode->next = newNode;
    }
    size++;
}

void DoublyList::removeFront() {
    if (head == nullptr) {
        return;  // Пустой список
    }
    
    Node* temp = head;
    head = head->next;
    
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;  // Список стал пустым
    }
    
    delete temp;
    size--;
}

void DoublyList::removeBack() {
    if (tail == nullptr) {
        return;  // Пустой список
    }
    
    Node* temp = tail;
    tail = tail->prev;
    
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;  // Список стал пустым
    }
    
    delete temp;
    size--;
}

void DoublyList::removeValue(const std::string& value) {
    Node* targetNode = findNode(value);
    if (targetNode == nullptr) {
        return;  // Элемент не найден
    }
    
    if (targetNode == head) {
        removeFront();
    } else if (targetNode == tail) {
        removeBack();
    } else {
        // Удаление из середины
        targetNode->prev->next = targetNode->next;
        targetNode->next->prev = targetNode->prev;
        delete targetNode;
        size--;
    }
}

void DoublyList::removeBefore(const std::string& target) {
    Node* targetNode = findNode(target);
    if (targetNode == nullptr || targetNode->prev == nullptr) {
        return;  // target не найден или перед ним нет элемента
    }
    
    Node* nodeToRemove = targetNode->prev;
    
    if (nodeToRemove == head) {
        removeFront();
    } else {
        // Удаление из середины
        nodeToRemove->prev->next = targetNode;
        targetNode->prev = nodeToRemove->prev;
        delete nodeToRemove;
        size--;
    }
}

void DoublyList::removeAfter(const std::string& target) {
    Node* targetNode = findNode(target);
    if (targetNode == nullptr || targetNode->next == nullptr) {
        return;  // target не найден или после него нет элемента
    }
    
    Node* nodeToRemove = targetNode->next;
    
    if (nodeToRemove == tail) {
        removeBack();
    } else {
        // Удаление из середины
        targetNode->next = nodeToRemove->next;
        nodeToRemove->next->prev = targetNode;
        delete nodeToRemove;
        size--;
    }
}

bool DoublyList::search(const std::string& value) const {
    return findNode(value) != nullptr;
}

void DoublyList::printForward() const {
    Node* current = head;
    std::cout << "[";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " <-> ";
        }
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

void DoublyList::printBackward() const {
    Node* current = tail;
    std::cout << "[";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->prev != nullptr) {
            std::cout << " <-> ";
        }
        current = current->prev;
    }
    std::cout << "]" << std::endl;
}

void DoublyList::serializeToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    Node* current = head;
    while (current != nullptr) {
        int strSize = current->data.size();
        file.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
        file.write(current->data.c_str(), strSize);
        current = current->next;
    }
    
    file.close();
}

void DoublyList::deserializeFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    clear();
    
    int newSize;
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    
    if (file.fail()) {
        throw std::runtime_error("Failed to read file size");
    }
    
    for (int i = 0; i < newSize; i++) {
        int strSize;
        file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
        
        if (file.fail() || strSize < 0) {
            throw std::runtime_error("Invalid string size in file");
        }
        
        std::string value(strSize, '\0');
        file.read(&value[0], strSize);
        
        if (file.fail()) {
            throw std::runtime_error("Failed to read string from file");
        }
        
        insertBack(value);
    }
    
    file.close();
}