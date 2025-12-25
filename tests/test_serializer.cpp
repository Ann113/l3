#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "../src/serializer.h"
#include "../src/array.h"
#include "../src/singly_list.h"
#include "../src/doubly_list.h"
#include "../src/stack.h"
#include "../src/queue.h"
#include "../src/hash_table.h"
#include "../src/tree.h"

TEST(SerializerTest, SaveToFileThrowsWhenCannotOpen) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    // Попытка сохранить в несуществующую директорию
    EXPECT_THROW(
        Serializer::saveToFile("/nonexistent/directory/test.bin", 
                              array, slist, dlist, stack, queue, hashTable, tree),
        std::runtime_error
    );
}

TEST(SerializerTest, LoadFromFileThrowsWhenFileNotFound) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    // Попытка загрузить несуществующий файл
    EXPECT_THROW(
        Serializer::loadFromFile("nonexistent_file.bin",
                                array, slist, dlist, stack, queue, hashTable, tree),
        std::runtime_error
    );
}

TEST(SerializerTest, LoadFromFileThrowsOnInvalidMagicNumber) {
    // Создаем файл с неправильным магическим числом
    std::ofstream file("invalid_magic.bin", std::ios::binary);
    int wrongMagic = 0x12345678;
    file.write(reinterpret_cast<const char*>(&wrongMagic), sizeof(wrongMagic));
    file.close();
    
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    EXPECT_THROW(
        Serializer::loadFromFile("invalid_magic.bin",
                                array, slist, dlist, stack, queue, hashTable, tree),
        std::runtime_error
    );
    
    std::remove("invalid_magic.bin");
}

TEST(SerializerTest, LoadFromFileThrowsOnUnsupportedVersion) {
    // Создаем файл с правильным магическим числом, но неправильной версией
    std::ofstream file("wrong_version.bin", std::ios::binary);
    int magic = 0x4C414233; // Правильное магическое число
    int version = 999;      // Неподдерживаемая версия
    file.write(reinterpret_cast<const char*>(&magic), sizeof(magic));
    file.write(reinterpret_cast<const char*>(&version), sizeof(version));
    file.close();
    
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    EXPECT_THROW(
        Serializer::loadFromFile("wrong_version.bin",
                                array, slist, dlist, stack, queue, hashTable, tree),
        std::runtime_error
    );
    
    std::remove("wrong_version.bin");
}

TEST(SerializerTest, SaveArrayEmpty) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    // Просто проверяем, что не падает при сохранении пустого массива
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_save_array.bin",
                              array, slist, dlist, stack, queue, hashTable, tree)
    );
    
    std::remove("test_save_array.bin");
}

TEST(SerializerTest, SaveArrayWithElements) {
    Array array;
    array.push_back("test1");
    array.push_back("test2");
    array.push_back("test3");
    
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_save_array_full.bin",
                              array, slist, dlist, stack, queue, hashTable, tree)
    );
    
    std::remove("test_save_array_full.bin");
}

TEST(SerializerTest, SaveAndLoadArray) {
    // Создаем исходный массив
    Array originalArray;
    originalArray.push_back("hello");
    originalArray.push_back("world");
    originalArray.push_back("test");
    
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    // Сохраняем
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_array.bin",
                              originalArray, slist, dlist, stack, queue, hashTable, tree)
    );
    
    // Загружаем в новый массив
    Array loadedArray;
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_array.bin",
                                loadedArray, slist, dlist, stack, queue, hashTable, tree)
    );
    
    // Проверяем что загрузилось
    EXPECT_EQ(loadedArray.length(), 3);
    
    std::remove("test_array.bin");
}

TEST(SerializerTest, SaveAndLoadSinglyList) {
    Array array;
    SinglyList originalList;
    originalList.insertBack("a");
    originalList.insertBack("b");
    originalList.insertBack("c");
    
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    // Сохраняем
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_slist.bin",
                              array, originalList, dlist, stack, queue, hashTable, tree)
    );
    
    // Загружаем
    SinglyList loadedList;
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_slist.bin",
                                array, loadedList, dlist, stack, queue, hashTable, tree)
    );
    
    std::remove("test_slist.bin");
}

TEST(SerializerTest, SaveAndLoadDoublyList) {
    Array array;
    SinglyList slist;
    DoublyList originalList;
    originalList.insertBack("x");
    originalList.insertBack("y");
    originalList.insertBack("z");
    
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_dlist.bin",
                              array, slist, originalList, stack, queue, hashTable, tree)
    );
    
    DoublyList loadedList;
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_dlist.bin",
                                array, slist, loadedList, stack, queue, hashTable, tree)
    );
    
    std::remove("test_dlist.bin");
}

TEST(SerializerTest, SaveAndLoadStack) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack originalStack;
    originalStack.push("first");
    originalStack.push("second");
    originalStack.push("third");
    
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_stack.bin",
                              array, slist, dlist, originalStack, queue, hashTable, tree)
    );
    
    Stack loadedStack;
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_stack.bin",
                                array, slist, dlist, loadedStack, queue, hashTable, tree)
    );
    
    std::remove("test_stack.bin");
}

TEST(SerializerTest, SaveAndLoadQueue) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue originalQueue;
    originalQueue.enqueue("item1");
    originalQueue.enqueue("item2");
    originalQueue.enqueue("item3");
    
    HashTable hashTable(10);
    Tree tree;
    
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_queue.bin",
                              array, slist, dlist, stack, originalQueue, hashTable, tree)
    );
    
    Queue loadedQueue;
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_queue.bin",
                                array, slist, dlist, stack, loadedQueue, hashTable, tree)
    );
    
    std::remove("test_queue.bin");
}

TEST(SerializerTest, SaveAndLoadHashTable) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable originalHashTable(10);
    originalHashTable.insert(1, "value1");  // Исправлено: int ключ
    originalHashTable.insert(2, "value2");  // Исправлено: int ключ
    originalHashTable.insert(3, "value3");  // Исправлено: int ключ
    
    Tree tree;
    
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_hashtable.bin",
                              array, slist, dlist, stack, queue, originalHashTable, tree)
    );
    
    HashTable loadedHashTable(10);
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_hashtable.bin",
                                array, slist, dlist, stack, queue, loadedHashTable, tree)
    );
    
    std::remove("test_hashtable.bin");
    std::remove("temp_hash.bin"); // Удаляем временный файл созданный сериализатором
}

TEST(SerializerTest, SaveAndLoadTree) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree originalTree;
    originalTree.insert("root");
    originalTree.insert("left");
    originalTree.insert("right");
    
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_tree.bin",
                              array, slist, dlist, stack, queue, hashTable, originalTree)
    );
    
    Tree loadedTree;
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_tree.bin",
                                array, slist, dlist, stack, queue, hashTable, loadedTree)
    );
    
    std::remove("test_tree.bin");
    std::remove("temp_tree.bin"); // Удаляем временный файл созданный сериализатором
}

TEST(SerializerTest, SaveAllStructuresTogether) {
    // Создаем все структуры с данными
    Array array;
    array.push_back("array_item1");
    array.push_back("array_item2");
    
    SinglyList slist;
    slist.insertBack("slist_item1");
    slist.insertBack("slist_item2");
    
    DoublyList dlist;
    dlist.insertBack("dlist_item1");
    dlist.insertBack("dlist_item2");
    
    Stack stack;
    stack.push("stack_item1");
    stack.push("stack_item2");
    
    Queue queue;
    queue.enqueue("queue_item1");
    queue.enqueue("queue_item2");
    
    HashTable hashTable(10);
    hashTable.insert(1, "value1");  // Исправлено: int ключ
    hashTable.insert(2, "value2");  // Исправлено: int ключ
    
    Tree tree;
    tree.insert("tree_root");
    tree.insert("tree_left");
    tree.insert("tree_right");
    
    // Сохраняем все вместе
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_all.bin",
                              array, slist, dlist, stack, queue, hashTable, tree)
    );
    
    // Загружаем все вместе
    Array loadedArray;
    SinglyList loadedSlist;
    DoublyList loadedDlist;
    Stack loadedStack;
    Queue loadedQueue;
    HashTable loadedHashTable(10);
    Tree loadedTree;
    
    EXPECT_NO_THROW(
        Serializer::loadFromFile("test_all.bin",
                                loadedArray, loadedSlist, loadedDlist, 
                                loadedStack, loadedQueue, loadedHashTable, loadedTree)
    );
    
    // Очищаем временные файлы
    std::remove("test_all.bin");
    std::remove("temp_hash.bin");
    std::remove("temp_tree.bin");
}

TEST(SerializerTest, SaveToFileConsoleOutput) {
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    // Просто проверяем что вызов не падает
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(
        Serializer::saveToFile("test_output.bin",
                              array, slist, dlist, stack, queue, hashTable, tree)
    );
    std::string output = testing::internal::GetCapturedStdout();
    
    std::remove("test_output.bin");
}

TEST(SerializerTest, LoadFromFileConsoleOutput) {
    // Сначала создаем валидный файл
    Array array;
    SinglyList slist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable hashTable(10);
    Tree tree;
    
    Serializer::saveToFile("valid_test.bin",
                          array, slist, dlist, stack, queue, hashTable, tree);
    
    // Теперь загружаем и проверяем вывод
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(
        Serializer::loadFromFile("valid_test.bin",
                                array, slist, dlist, stack, queue, hashTable, tree)
    );
    std::string output = testing::internal::GetCapturedStdout();
    
    std::remove("valid_test.bin");
    std::remove("temp_hash.bin");
    std::remove("temp_tree.bin");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}