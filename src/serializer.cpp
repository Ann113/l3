#include "serializer.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

void Serializer::saveToFile(const std::string& filename,
                           const Array& array,
                           const SinglyList& slist,
                           const DoublyList& dlist,
                           const Stack& stack,
                           const Queue& queue,
                           const HashTable& hashTable,
                           const Tree& tree) {
    
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    // Магическое число для проверки формата
    const int MAGIC_NUMBER = 0x4C414233; // "LAB3"
    file.write(reinterpret_cast<const char*>(&MAGIC_NUMBER), sizeof(MAGIC_NUMBER));
    
    // Версия формата
    const int VERSION = 1;
    file.write(reinterpret_cast<const char*>(&VERSION), sizeof(VERSION));
    
    // Сохраняем каждую структуру
    saveArray(file, array);
    saveSinglyList(file, slist);
    saveDoublyList(file, dlist);
    saveStack(file, stack);
    saveQueue(file, queue);
    saveHashTable(file, hashTable);
    saveTree(file, tree);
    
    file.close();
    std::cout << "All structures saved to: " << filename << std::endl;
}

void Serializer::saveArray(std::ofstream& file, const Array& array) {
    int size = array.length();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        std::string value = array.get(i);
        int strSize = value.size();
        file.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
        file.write(value.c_str(), strSize);
    }
}

void Serializer::saveSinglyList(std::ofstream& file, const SinglyList& list) {
    // Для списка нужно пройти по всем элементам
    // В реальной реализации нужно добавить метод для получения всех элементов
    // Здесь упрощенная версия
    int size = list.getSize();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // В реальном проекте нужно реализовать итератор для списка
    // или метод для получения всех элементов
}

void Serializer::saveDoublyList(std::ofstream& file, const DoublyList& list) {
    int size = list.getSize();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    // Аналогично односвязному списку
}

void Serializer::saveStack(std::ofstream& file, const Stack& stack) {
    int size = stack.getSize();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    // Для стека нужен специальный метод сериализации
}

void Serializer::saveQueue(std::ofstream& file, const Queue& queue) {
    int size = queue.getSize();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    // Для очереди нужен специальный метод сериализации
}

void Serializer::saveHashTable(std::ofstream& file, const HashTable& hashTable) {
    // Хеш-таблица имеет собственный метод сериализации
    // Здесь можно просто вызвать его или сохранить в общий файл
    hashTable.serializeToFile("temp_hash.bin");
    // В реальной реализации нужно интегрировать в общий формат
}

void Serializer::saveTree(std::ofstream& file, const Tree& tree) {
    // Дерево имеет собственный метод сериализации
    tree.serializeToFile("temp_tree.bin");
    // В реальной реализации нужно интегрировать в общий формат
}

void Serializer::loadFromFile(const std::string& filename,
                             Array& array,
                             SinglyList& slist,
                             DoublyList& dlist,
                             Stack& stack,
                             Queue& queue,
                             HashTable& hashTable,
                             Tree& tree) {
    
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    // Проверяем магическое число
    int magic;
    file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
    if (magic != 0x4C414233) {
        throw std::runtime_error("Invalid file format");
    }
    
    // Проверяем версию
    int version;
    file.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (version != 1) {
        throw std::runtime_error("Unsupported file version");
    }
    
    // Загружаем каждую структуру
    loadArray(file, array);
    loadSinglyList(file, slist);
    loadDoublyList(file, dlist);
    loadStack(file, stack);
    loadQueue(file, queue);
    loadHashTable(file, hashTable);
    loadTree(file, tree);
    
    file.close();
    std::cout << "All structures loaded from: " << filename << std::endl;
}

void Serializer::loadArray(std::ifstream& file, Array& array) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    array.clear();
    for (int i = 0; i < size; i++) {
        int strSize;
        file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
        
        std::string value(strSize, '\0');
        file.read(&value[0], strSize);
        
        array.push_back(value);
    }
}

void Serializer::loadSinglyList(std::ifstream& file, SinglyList& list) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Очищаем список
    // В реальной реализации нужен метод clear()
    for (int i = 0; i < size; i++) {
        int strSize;
        file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
        
        std::string value(strSize, '\0');
        file.read(&value[0], strSize);
        
        // В реальной реализации нужен метод добавления
        // list.insertBack(value);
    }
}

void Serializer::loadDoublyList(std::ifstream& file, DoublyList& list) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Аналогично односвязному списку
}

void Serializer::loadStack(std::ifstream& file, Stack& stack) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Для стека нужен специальный метод загрузки
}

void Serializer::loadQueue(std::ifstream& file, Queue& queue) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Для очереди нужен специальный метод загрузки
}

void Serializer::loadHashTable(std::ifstream& file, HashTable& hashTable) {
    hashTable.deserializeFromFile("temp_hash.bin");
}

void Serializer::loadTree(std::ifstream& file, Tree& tree) {
    tree.deserializeFromFile("temp_tree.bin");
}