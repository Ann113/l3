#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <functional>

class HashTable {
private:
    // Структура для элемента цепочки
    struct HashNode {
        int key;
        std::string value;
        HashNode* next;
        HashNode(int k, const std::string& v) : key(k), value(v), next(nullptr) {}
    };
    
    std::vector<HashNode*> table;
    int capacity;
    int size;
    double loadFactorThreshold;
    
    // Хеш-функции
    int hashFunction(int key) const;
    int hashFunction2(int key) const;
    
    // Вспомогательные методы
    void rehash();
    double getLoadFactor() const;
    
public:
    // Конструкторы
    HashTable(int initialCapacity = 8, double threshold = 0.75);
    ~HashTable();
    
    // Запрет копирования
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    
    // Основные операции
    void insert(int key, const std::string& value);
    std::string search(int key) const;
    void remove(int key);
    
    // Утилиты
    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    void clear();
    void print() const;
    
    // Статистика
    void printStats() const;
    
    // Сериализация
    void serializeToFile(const std::string& filename) const;
    void deserializeFromFile(const std::string& filename);
};

#endif