#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <vector>
#include <iostream>

class Array {
private:
    std::vector<std::string> data;
    int capacity;
    int size;

    void resize();

public:
    // Конструкторы
    Array();
    explicit Array(int initialCapacity);
    ~Array();

    // Основные операции
    void push_back(const std::string& value);
    void insert(int index, const std::string& value);
    std::string get(int index) const;
    void remove(int index);
    void replace(int index, const std::string& value);
    int length() const;
    bool isEmpty() const;
    void clear();
    
    // Для сериализации
    void serializeToFile(const std::string& filename) const;
    void deserializeFromFile(const std::string& filename);
    
    // Утилиты
    void print() const;
    std::vector<std::string> getAllData() const;

    // Операторы
    std::string& operator[](int index);
    const std::string& operator[](int index) const;
    
    // Для тестирования
    int getCapacity() const { return capacity; }
};

#endif