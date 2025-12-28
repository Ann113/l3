#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <vector>
#include <memory>
#include "array.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "stack.h"
#include "queue.h"
#include "hash_table.h"
#include "tree.h"

class Serializer {
public:
    // Универсальная сериализация структур
    static void saveToFile(const std::string& filename, 
                          const Array& array,
                          const SinglyList& slist,
                          const DoublyList& dlist,
                          const Stack& stack,
                          const Queue& queue,
                          const HashTable& hashTable,
                          const Tree& tree);
    
    static void loadFromFile(const std::string& filename,
                            Array& array,
                            SinglyList& slist,
                            DoublyList& dlist,
                            Stack& stack,
                            Queue& queue,
                            HashTable& hashTable,
                            Tree& tree);
    
private: 
    static void saveArray(std::ofstream& file, const Array& array);
    static void saveSinglyList(std::ofstream& file, const SinglyList& list);
    static void saveDoublyList(std::ofstream& file, const DoublyList& list);
    static void saveStack(std::ofstream& file, const Stack& stack);
    static void saveQueue(std::ofstream& file, const Queue& queue);
    static void saveHashTable(std::ofstream& file, const HashTable& hashTable);
    static void saveTree(std::ofstream& file, const Tree& tree);
    
    static void loadArray(std::ifstream& file, Array& array);
    static void loadSinglyList(std::ifstream& file, SinglyList& list);
    static void loadDoublyList(std::ifstream& file, DoublyList& list);
    static void loadStack(std::ifstream& file, Stack& stack);
    static void loadQueue(std::ifstream& file, Queue& queue);
    static void loadHashTable(std::ifstream& file, HashTable& hashTable);
    static void loadTree(std::ifstream& file, Tree& tree);
};

#endif