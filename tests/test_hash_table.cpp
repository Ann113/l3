#include <gtest/gtest.h>
#include "../src/hash_table.h"
#include <string>

TEST(HashTableTest, DefaultConstructor) {
    HashTable ht;
    EXPECT_EQ(ht.getSize(), 0);
    EXPECT_EQ(ht.getCapacity(), 8);
    EXPECT_TRUE(ht.isEmpty());
}

TEST(HashTableTest, ParameterizedConstructor) {
    HashTable ht(16, 0.5);
    EXPECT_EQ(ht.getCapacity(), 16);
    EXPECT_EQ(ht.getSize(), 0);
}

TEST(HashTableTest, Insert) {
    HashTable ht;
    ht.insert(1, "Alice");
    
    EXPECT_EQ(ht.getSize(), 1);
    EXPECT_FALSE(ht.isEmpty());
    
    ht.insert(2, "Bob");
    EXPECT_EQ(ht.getSize(), 2);
}

TEST(HashTableTest, InsertDuplicateKey) {
    HashTable ht;
    ht.insert(1, "Alice");
    ht.insert(1, "Alice Updated"); // Обновление
    
    EXPECT_EQ(ht.getSize(), 1); // Размер не должен увеличиться
    EXPECT_EQ(ht.search(1), "Alice Updated");
}

TEST(HashTableTest, SearchExisting) {
    HashTable ht;
    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie");
    
    EXPECT_EQ(ht.search(1), "Alice");
    EXPECT_EQ(ht.search(2), "Bob");
    EXPECT_EQ(ht.search(3), "Charlie");
}

TEST(HashTableTest, SearchNonExistent) {
    HashTable ht;
    ht.insert(1, "Alice");
    
    EXPECT_EQ(ht.search(2), "Not Found");
    EXPECT_EQ(ht.search(999), "Not Found");
}

TEST(HashTableTest, SearchAfterRehash) {
    HashTable ht(4, 0.75); // Маленькая таблица для теста rehash
    
    // Добавляем элементы, чтобы вызвать rehash
    ht.insert(1, "A");
    ht.insert(2, "B");
    ht.insert(3, "C"); // Должен вызвать rehash
    
    // После rehash все элементы должны быть доступны
    EXPECT_EQ(ht.search(1), "A");
    EXPECT_EQ(ht.search(2), "B");
    EXPECT_EQ(ht.search(3), "C");
}

TEST(HashTableTest, Remove) {
    HashTable ht;
    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie");
    
    ht.remove(2);
    EXPECT_EQ(ht.getSize(), 2);
    EXPECT_EQ(ht.search(2), "Not Found");
    EXPECT_EQ(ht.search(1), "Alice");
    EXPECT_EQ(ht.search(3), "Charlie");
}

TEST(HashTableTest, RemoveNonExistent) {
    HashTable ht;
    ht.insert(1, "Alice");
    
    // Удаление несуществующего ключа не должно падать
    EXPECT_NO_THROW(ht.remove(999));
    EXPECT_EQ(ht.getSize(), 1);
}

TEST(HashTableTest, CollisionHandling) {
    HashTable ht(4, 0.75); // Маленькая таблица для создания коллизий
    
    // Эти ключи могут создать коллизии при capacity=4
    ht.insert(1, "A");
    ht.insert(5, "B"); // Возможная коллизия с 1
    ht.insert(9, "C"); // Возможная коллизия с 1 и 5
    
    EXPECT_EQ(ht.getSize(), 3);
    EXPECT_EQ(ht.search(1), "A");
    EXPECT_EQ(ht.search(5), "B");
    EXPECT_EQ(ht.search(9), "C");
}

TEST(HashTableTest, Clear) {
    HashTable ht;
    ht.insert(1, "A");
    ht.insert(2, "B");
    ht.insert(3, "C");
    
    EXPECT_EQ(ht.getSize(), 3);
    ht.clear();
    EXPECT_EQ(ht.getSize(), 0);
    EXPECT_TRUE(ht.isEmpty());
    EXPECT_EQ(ht.search(1), "Not Found");
}

TEST(HashTableTest, LoadFactor) {
    HashTable ht(8, 0.75);
    
    // Добавляем элементы, но не до rehash
    for (int i = 0; i < 5; i++) {
        ht.insert(i, "Value" + std::to_string(i));
    }
    
    EXPECT_EQ(ht.getSize(), 5);
    EXPECT_EQ(ht.getCapacity(), 8);
    
    // Добавляем еще, чтобы вызвать rehash
    ht.insert(5, "Value5");
    ht.insert(6, "Value6"); // Должен вызвать rehash
    
    EXPECT_GE(ht.getCapacity(), 16); // Емкость должна увеличиться
}

TEST(HashTableTest, PrintAndStats) {
    HashTable ht;
    ht.insert(1, "A");
    ht.insert(2, "B");
    ht.insert(3, "C");
    
    // Проверяем, что функции не падают
    EXPECT_NO_THROW(ht.print());
    EXPECT_NO_THROW(ht.printStats());
}

TEST(HashTableTest, Serialization) {
    HashTable ht;
    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie");
    
    // Сериализация
    ht.serializeToFile("test_hash.bin");
    
    // Десериализация в новую таблицу
    HashTable ht2;
    ht2.deserializeFromFile("test_hash.bin");
    
    // Проверка
    EXPECT_EQ(ht2.getSize(), 3);
    EXPECT_EQ(ht2.search(1), "Alice");
    EXPECT_EQ(ht2.search(2), "Bob");
    EXPECT_EQ(ht2.search(3), "Charlie");
    
    // Очистка
    remove("test_hash.bin");
}

TEST(HashTableTest, EmptyTableSerialization) {
    HashTable ht;
    
    // Сериализация пустой таблицы
    ht.serializeToFile("test_empty_hash.bin");
    
    HashTable ht2;
    ht2.deserializeFromFile("test_empty_hash.bin");
    
    EXPECT_TRUE(ht2.isEmpty());
    EXPECT_EQ(ht2.getSize(), 0);
    
    remove("test_empty_hash.bin");
}

TEST(HashTableTest, LargeTable) {
    HashTable ht;
    const int N = 100;
    
    // Добавляем много элементов
    for (int i = 0; i < N; i++) {
        ht.insert(i, "Value_" + std::to_string(i));
    }
    
    EXPECT_EQ(ht.getSize(), N);
    
    // Проверяем все элементы
    for (int i = 0; i < N; i++) {
        EXPECT_EQ(ht.search(i), "Value_" + std::to_string(i));
    }
    
    // Удаляем половину
    for (int i = 0; i < N/2; i++) {
        ht.remove(i);
    }
    
    EXPECT_EQ(ht.getSize(), N/2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}