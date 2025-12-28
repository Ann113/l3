#include "singly_list.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

SinglyList::SinglyList() : head(nullptr), tail(nullptr), size(0) {}

SinglyList::~SinglyList() {
    clear();
}

void SinglyList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

SinglyList::Node* SinglyList::findNode(const std::string& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

SinglyList::Node* SinglyList::findNodeBefore(const std::string& value) const {
    if (head == nullptr || head->data == value) {
        return nullptr;  // Элемент в голове или список пуст
    }
    
    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;  // Элемент не найден
}

void SinglyList::insertFront(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

void SinglyList::insertBack(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void SinglyList::insertBefore(const std::string& target, const std::string& value) {
    if (head == nullptr) {
        return;  // Пустой список
    }
    
    if (head->data == target) {
        insertFront(value);
        return;
    }
    
    Node* prevNode = findNodeBefore(target);
    if (prevNode == nullptr) {
        return;  // target не найден
    }
    
    Node* newNode = new Node(value);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    size++;
}

void SinglyList::insertAfter(const std::string& target, const std::string& value) {
    Node* targetNode = findNode(target);
    if (targetNode == nullptr) {
        return;  // target не найден
    }
    
    Node* newNode = new Node(value);
    newNode->next = targetNode->next;
    targetNode->next = newNode;
    
    if (targetNode == tail) {
        tail = newNode;
    }
    size++;
}

void SinglyList::removeFront() {
    if (head == nullptr) {
        return;  // Пустой список
    }
    
    Node* temp = head;
    head = head->next;
    
    if (head == nullptr) {
        tail = nullptr;  // Список стал пустым
    }
    
    delete temp;
    size--;
}

void SinglyList::removeBack() {
    if (head == nullptr) {
        return;  // Пустой список
    }
    
    if (head == tail) {
        // Один элемент
        delete head;
        head = tail = nullptr;
    } else {
        // Несколько элементов
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    size--;
}

void SinglyList::removeValue(const std::string& value) {
    if (head == nullptr) {
        return;  // Пустой список
    }
    
    if (head->data == value) {
        removeFront();
        return;
    }
    
    Node* prevNode = findNodeBefore(value);
    if (prevNode == nullptr) {
        return;  // Элемент не найден
    }
    
    Node* temp = prevNode->next;
    prevNode->next = temp->next;
    
    if (temp == tail) {
        tail = prevNode;
    }
    
    delete temp;
    size--;
}

void SinglyList::removeBefore(const std::string& target) {
    if (head == nullptr || head->next == nullptr) {
        return;  // Менее двух элементов
    }
    
    if (head->next->data == target) {
        removeFront();
        return;
    }
    
    // Ищем элемент, который находится за два узла до target
    Node* current = head;
    while (current->next != nullptr && current->next->next != nullptr) {
        if (current->next->next->data == target) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            size--;
            return;
        }
        current = current->next;
    }
}

void SinglyList::removeAfter(const std::string& target) {
    Node* targetNode = findNode(target);
    if (targetNode == nullptr || targetNode->next == nullptr) {
        return;  // target не найден или нет элемента после него
    }
    
    Node* temp = targetNode->next;
    targetNode->next = temp->next;
    
    if (temp == tail) {
        tail = targetNode;
    }
    
    delete temp;
    size--;
}

bool SinglyList::search(const std::string& value) const {
    return findNode(value) != nullptr;
}

void SinglyList::printForward() const {
    Node* current = head;
    std::cout << "[";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

void SinglyList::serializeToFile(const std::string& filename) const {
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

void SinglyList::deserializeFromFile(const std::string& filename) {
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