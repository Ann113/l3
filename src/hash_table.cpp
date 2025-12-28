#include "hash_table.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iomanip>

HashTable::HashTable(int initialCapacity, double threshold) 
    : capacity(initialCapacity > 0 ? initialCapacity : 8),
      size(0),
      loadFactorThreshold(threshold > 0.1 && threshold < 1.0 ? threshold : 0.75) {
    
    table.resize(capacity, nullptr);
} 

HashTable::~HashTable() {
    clear();
}

int HashTable::hashFunction(int key) const {
    return std::abs(key) % capacity;
}

int HashTable::hashFunction2(int key) const {
    return 1 + (std::abs(key) % (capacity - 1));
}

double HashTable::getLoadFactor() const {
    return static_cast<double>(size) / capacity;
}

void HashTable::rehash() {
    int oldCapacity = capacity;
    capacity *= 2;
    
    std::vector<HashNode*> oldTable = std::move(table);
    table.resize(capacity, nullptr);
    size = 0;
    
    // Перехешируем все элементы
    for (int i = 0; i < oldCapacity; i++) {
        HashNode* current = oldTable[i];
        while (current != nullptr) {
            HashNode* next = current->next;
            insert(current->key, current->value);
            delete current;
            current = next;
        }
    }
}

void HashTable::insert(int key, const std::string& value) {
    if (getLoadFactor() >= loadFactorThreshold) {
        rehash();
    }
    
    int index = hashFunction(key);
    int step = hashFunction2(key);
    int originalIndex = index;
    int probeCount = 0;
    
    // Линейное пробирование для разрешения коллизий
    while (table[index] != nullptr && table[index]->key != key) {
        index = (originalIndex + probeCount * step) % capacity;
        probeCount++;
        
        if (probeCount >= capacity) {
            rehash();
            insert(key, value);
            return;
        }
    }
    
    if (table[index] == nullptr) {
        table[index] = new HashNode(key, value);
        size++;
    } else {
        // Обновляем существующий ключ
        table[index]->value = value;
    }
}

std::string HashTable::search(int key) const {
    int index = hashFunction(key);
    int step = hashFunction2(key);
    int originalIndex = index;
    int probeCount = 0;
    
    while (probeCount < capacity) {
        if (table[index] == nullptr) {
            return "Not Found";
        }
        
        if (table[index]->key == key) {
            return table[index]->value;
        }
        
        index = (originalIndex + probeCount * step) % capacity;
        probeCount++;
    }
    
    return "Not Found";
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    int step = hashFunction2(key);
    int originalIndex = index;
    int probeCount = 0;
    
    while (probeCount < capacity) {
        if (table[index] == nullptr) {
            return; // Ключ не найден
        }
        
        if (table[index]->key == key) {
            delete table[index];
            table[index] = nullptr;
            size--;
            
            // Обработка кластеризации (опционально)
            // Можно выполнить повторную вставку последующих элементов
            return;
        }
        
        index = (originalIndex + probeCount * step) % capacity;
        probeCount++;
    }
}

void HashTable::clear() {
    for (int i = 0; i < capacity; i++) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    size = 0;
}

void HashTable::print() const {
    std::cout << "\nHash Table Contents:" << std::endl;
    std::cout << "Capacity: " << capacity << ", Size: " << size << std::endl;
    std::cout << "Load Factor: " << std::fixed << std::setprecision(2) << getLoadFactor() << std::endl;
    
    for (int i = 0; i < capacity; i++) {
        std::cout << "[" << i << "]: ";
        if (table[i] == nullptr) {
            std::cout << "empty";
        } else {
            HashNode* current = table[i];
            while (current != nullptr) {
                std::cout << "{" << current->key << ": '" << current->value << "'}";
                if (current->next != nullptr) {
                    std::cout << " -> ";
                }
                current = current->next;
            }
        }
        std::cout << std::endl;
    }
}

void HashTable::printStats() const {
    int emptyBuckets = 0;
    int maxChainLength = 0;
    
    for (int i = 0; i < capacity; i++) {
        if (table[i] == nullptr) {
            emptyBuckets++;
        } else {
            int chainLength = 0;
            HashNode* current = table[i];
            while (current != nullptr) {
                chainLength++;
                current = current->next;
            }
            if (chainLength > maxChainLength) {
                maxChainLength = chainLength;
            }
        }
    }
    
    std::cout << "\nHash Table Statistics:" << std::endl;
    std::cout << "Size: " << size << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Load Factor: " << std::fixed << std::setprecision(2) << getLoadFactor() << std::endl;
    std::cout << "Empty Buckets: " << emptyBuckets << " (" 
              << (emptyBuckets * 100.0 / capacity) << "%)" << std::endl;
    std::cout << "Max Chain Length: " << maxChainLength << std::endl;
}

void HashTable::serializeToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    // Сохраняем параметры таблицы
    file.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(reinterpret_cast<const char*>(&loadFactorThreshold), sizeof(loadFactorThreshold));
    
    // Сохраняем элементы
    for (int i = 0; i < capacity; i++) {
        HashNode* current = table[i];
        int chainLength = 0;
        
        // Сначала считаем длину цепочки
        HashNode* counter = current;
        while (counter != nullptr) {
            chainLength++;
            counter = counter->next;
        }
        
        file.write(reinterpret_cast<const char*>(&chainLength), sizeof(chainLength));
        
        // Теперь сохраняем элементы цепочки
        while (current != nullptr) {
            file.write(reinterpret_cast<const char*>(&current->key), sizeof(current->key));
            
            int strSize = current->value.size();
            file.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
            file.write(current->value.c_str(), strSize);
            
            current = current->next;
        }
    }
    
    file.close();
}

void HashTable::deserializeFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    clear();
    
    // Читаем параметры таблицы
    int newCapacity, newSize;
    double newThreshold;
    
    file.read(reinterpret_cast<char*>(&newCapacity), sizeof(newCapacity));
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    file.read(reinterpret_cast<char*>(&newThreshold), sizeof(newThreshold));
    
    // Пересоздаем таблицу с новыми параметрами
    capacity = newCapacity;
    size = 0;
    loadFactorThreshold = newThreshold;
    table.resize(capacity, nullptr);
    
    // Читаем элементы
    for (int i = 0; i < capacity; i++) {
        int chainLength;
        file.read(reinterpret_cast<char*>(&chainLength), sizeof(chainLength));
        
        HashNode** currentPtr = &table[i];
        for (int j = 0; j < chainLength; j++) {
            int key;
            file.read(reinterpret_cast<char*>(&key), sizeof(key));
            
            int strSize;
            file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
            
            std::string value(strSize, '\0');
            file.read(&value[0], strSize);
            
            // Создаем новый узел
            *currentPtr = new HashNode(key, value);
            currentPtr = &((*currentPtr)->next);
            size++;
        }
    }
    
    file.close();
}