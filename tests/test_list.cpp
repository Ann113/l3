#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "../src/singly_list.h"
#include "../src/doubly_list.h"

// ==================== Singly Linked List Tests ====================

TEST(SinglyListTest, DefaultConstructor) {
    SinglyList list;
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SinglyListTest, InsertFrontEmpty) {
    SinglyList list;
    list.insertFront("a");
    EXPECT_EQ(list.getSize(), 1); 
    EXPECT_FALSE(list.isEmpty());
}

TEST(SinglyListTest, InsertFrontMultiple) {
    SinglyList list;
    list.insertFront("c");
    list.insertFront("b");
    list.insertFront("a");
    EXPECT_EQ(list.getSize(), 3);
}

TEST(SinglyListTest, InsertBackEmpty) {
    SinglyList list;
    list.insertBack("a");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(SinglyListTest, InsertBackMultiple) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    EXPECT_EQ(list.getSize(), 3);
}

TEST(SinglyListTest, InsertBeforeEmpty) {
    SinglyList list;
    list.insertBefore("target", "value");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SinglyListTest, InsertBeforeFirst) {
    SinglyList list;
    list.insertBack("b");
    list.insertBefore("b", "a");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
}

TEST(SinglyListTest, InsertBeforeMiddle) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("c");
    list.insertBefore("c", "b");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_TRUE(list.search("b"));
}

TEST(SinglyListTest, InsertBeforeNonExistent) {
    SinglyList list;
    list.insertBack("a");
    list.insertBefore("nonexistent", "b");
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_FALSE(list.search("b"));
}

TEST(SinglyListTest, InsertAfterEmpty) {
    SinglyList list;
    list.insertAfter("target", "value");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SinglyListTest, InsertAfterFirst) {
    SinglyList list;
    list.insertBack("a");
    list.insertAfter("a", "b");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("b"));
}

TEST(SinglyListTest, InsertAfterMiddle) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertAfter("a", "middle");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_TRUE(list.search("middle"));
}

TEST(SinglyListTest, InsertAfterLast) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertAfter("b", "c");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_TRUE(list.search("c"));
}

TEST(SinglyListTest, InsertAfterNonExistent) {
    SinglyList list;
    list.insertBack("a");
    list.insertAfter("nonexistent", "b");
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_FALSE(list.search("b"));
}

TEST(SinglyListTest, RemoveFrontEmpty) {
    SinglyList list;
    EXPECT_NO_THROW(list.removeFront());
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SinglyListTest, RemoveFrontSingle) {
    SinglyList list;
    list.insertBack("a");
    list.removeFront();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SinglyListTest, RemoveFrontMultiple) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeFront();
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_FALSE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(SinglyListTest, RemoveBackEmpty) {
    SinglyList list;
    EXPECT_NO_THROW(list.removeBack());
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SinglyListTest, RemoveBackSingle) {
    SinglyList list;
    list.insertBack("a");
    list.removeBack();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SinglyListTest, RemoveBackMultiple) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeBack();
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_FALSE(list.search("c"));
}

TEST(SinglyListTest, RemoveValueEmpty) {
    SinglyList list;
    list.removeValue("anything");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SinglyListTest, RemoveValueFirst) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeValue("a");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_FALSE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(SinglyListTest, RemoveValueMiddle) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeValue("b");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_FALSE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(SinglyListTest, RemoveValueLast) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeValue("c");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_FALSE(list.search("c"));
}

TEST(SinglyListTest, RemoveValueNonExistent) {
    SinglyList list;
    list.insertBack("a");
    list.removeValue("nonexistent");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(SinglyListTest, RemoveBeforeEmpty) {
    SinglyList list;
    list.removeBefore("target");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SinglyListTest, RemoveBeforeSingle) {
    SinglyList list;
    list.insertBack("a");
    list.removeBefore("a");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(SinglyListTest, RemoveBeforeFirst) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.removeBefore("a");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(SinglyListTest, RemoveBeforeSecond) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeBefore("c");  // Должен удалить "b" (перед "c")
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));  // "a" должен остаться
    EXPECT_FALSE(list.search("b")); // "b" должен быть удален
    EXPECT_TRUE(list.search("c"));  // "c" должен остаться
}

TEST(SinglyListTest, RemoveBeforeNonExistent) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.removeBefore("nonexistent");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(SinglyListTest, RemoveAfterEmpty) {
    SinglyList list;
    list.removeAfter("target");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SinglyListTest, RemoveAfterSingle) {
    SinglyList list;
    list.insertBack("a");
    list.removeAfter("a");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(SinglyListTest, RemoveAfterFirst) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeAfter("a");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_FALSE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(SinglyListTest, RemoveAfterLast) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.removeAfter("b");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(SinglyListTest, RemoveAfterNonExistent) {
    SinglyList list;
    list.insertBack("a");
    list.removeAfter("nonexistent");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(SinglyListTest, SearchEmpty) {
    SinglyList list;
    EXPECT_FALSE(list.search("anything"));
}

TEST(SinglyListTest, SearchFound) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    EXPECT_TRUE(list.search("b"));
}

TEST(SinglyListTest, SearchNotFound) {
    SinglyList list;
    list.insertBack("a");
    EXPECT_FALSE(list.search("b"));
}

TEST(SinglyListTest, ClearEmpty) {
    SinglyList list;
    list.clear();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SinglyListTest, ClearNonEmpty) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.clear();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SinglyListTest, PrintForwardEmpty) {
    SinglyList list;
    EXPECT_NO_THROW(list.printForward());
}

TEST(SinglyListTest, PrintForwardNonEmpty) {
    SinglyList list;
    list.insertBack("a");
    list.insertBack("b");
    EXPECT_NO_THROW(list.printForward());
}

TEST(SinglyListTest, SerializeEmpty) {
    SinglyList list;
    EXPECT_NO_THROW(list.serializeToFile("empty_test.bin"));
    
    SinglyList newList;
    EXPECT_NO_THROW(newList.deserializeFromFile("empty_test.bin"));
    EXPECT_EQ(newList.getSize(), 0);
    
    std::remove("empty_test.bin");
}

TEST(SinglyListTest, SerializeNonEmpty) {
    SinglyList list;
    list.insertBack("hello");
    list.insertBack("world");
    list.insertBack("test");
    
    EXPECT_NO_THROW(list.serializeToFile("test.bin"));
    
    SinglyList newList;
    EXPECT_NO_THROW(newList.deserializeFromFile("test.bin"));
    
    EXPECT_EQ(newList.getSize(), 3);
    EXPECT_TRUE(newList.search("hello"));
    EXPECT_TRUE(newList.search("world"));
    EXPECT_TRUE(newList.search("test"));
    
    std::remove("test.bin");
}

TEST(SinglyListTest, SerializeInvalidFile) {
    SinglyList list;
    list.insertBack("test");
    EXPECT_THROW(list.serializeToFile("/invalid/path/test.bin"), std::runtime_error);
}

TEST(SinglyListTest, DeserializeNonExistentFile) {
    SinglyList list;
    EXPECT_THROW(list.deserializeFromFile("nonexistent.bin"), std::runtime_error);
}

TEST(SinglyListTest, DeserializeCorruptedFile) {
    // Создаем битый файл
    std::ofstream file("corrupted.bin", std::ios::binary);
    file.write("corrupted data", 14);
    file.close();
    
    SinglyList list;
    EXPECT_THROW(list.deserializeFromFile("corrupted.bin"), std::runtime_error);
    
    std::remove("corrupted.bin");
}

// ==================== Doubly Linked List Tests ====================

TEST(DoublyListTest, DefaultConstructor) {
    DoublyList list;
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyListTest, InsertFrontEmpty) {
    DoublyList list;
    list.insertFront("a");
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(DoublyListTest, InsertFrontMultiple) {
    DoublyList list;
    list.insertFront("c");
    list.insertFront("b");
    list.insertFront("a");
    EXPECT_EQ(list.getSize(), 3);
}

TEST(DoublyListTest, InsertBackEmpty) {
    DoublyList list;
    list.insertBack("a");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(DoublyListTest, InsertBackMultiple) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    EXPECT_EQ(list.getSize(), 3);
}

TEST(DoublyListTest, InsertBeforeEmpty) {
    DoublyList list;
    list.insertBefore("target", "value");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyListTest, InsertBeforeFirst) {
    DoublyList list;
    list.insertBack("b");
    list.insertBefore("b", "a");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
}

TEST(DoublyListTest, InsertBeforeMiddle) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("c");
    list.insertBefore("c", "b");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_TRUE(list.search("b"));
}

TEST(DoublyListTest, InsertBeforeNonExistent) {
    DoublyList list;
    list.insertBack("a");
    list.insertBefore("nonexistent", "b");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(DoublyListTest, InsertAfterEmpty) {
    DoublyList list;
    list.insertAfter("target", "value");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyListTest, InsertAfterFirst) {
    DoublyList list;
    list.insertBack("a");
    list.insertAfter("a", "b");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("b"));
}

TEST(DoublyListTest, InsertAfterMiddle) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("c");
    list.insertAfter("a", "b");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_TRUE(list.search("b"));
}

TEST(DoublyListTest, InsertAfterLast) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertAfter("b", "c");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_TRUE(list.search("c"));
}

TEST(DoublyListTest, InsertAfterNonExistent) {
    DoublyList list;
    list.insertBack("a");
    list.insertAfter("nonexistent", "b");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(DoublyListTest, RemoveFrontEmpty) {
    DoublyList list;
    EXPECT_NO_THROW(list.removeFront());
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyListTest, RemoveFrontSingle) {
    DoublyList list;
    list.insertBack("a");
    list.removeFront();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyListTest, RemoveFrontMultiple) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeFront();
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_FALSE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(DoublyListTest, RemoveBackEmpty) {
    DoublyList list;
    EXPECT_NO_THROW(list.removeBack());
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyListTest, RemoveBackSingle) {
    DoublyList list;
    list.insertBack("a");
    list.removeBack();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyListTest, RemoveBackMultiple) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeBack();
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_FALSE(list.search("c"));
}

TEST(DoublyListTest, RemoveValueEmpty) {
    DoublyList list;
    list.removeValue("anything");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyListTest, RemoveValueFirst) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeValue("a");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_FALSE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(DoublyListTest, RemoveValueMiddle) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeValue("b");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_FALSE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(DoublyListTest, RemoveValueLast) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeValue("c");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_TRUE(list.search("b"));
    EXPECT_FALSE(list.search("c"));
}

TEST(DoublyListTest, RemoveValueNonExistent) {
    DoublyList list;
    list.insertBack("a");
    list.removeValue("nonexistent");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(DoublyListTest, RemoveBeforeEmpty) {
    DoublyList list;
    list.removeBefore("target");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyListTest, RemoveBeforeFirst) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.removeBefore("a");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(DoublyListTest, RemoveBeforeSecond) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeBefore("c");  // Должен удалить "b" (перед "c")
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));  // "a" должен остаться
    EXPECT_FALSE(list.search("b")); // "b" должен быть удален
    EXPECT_TRUE(list.search("c"));  // "c" должен остаться
}

TEST(DoublyListTest, RemoveBeforeNonExistent) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.removeBefore("nonexistent");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(DoublyListTest, RemoveAfterEmpty) {
    DoublyList list;
    list.removeAfter("target");
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyListTest, RemoveAfterFirst) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.removeAfter("a");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_TRUE(list.search("a"));
    EXPECT_FALSE(list.search("b"));
    EXPECT_TRUE(list.search("c"));
}

TEST(DoublyListTest, RemoveAfterLast) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.removeAfter("b");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(DoublyListTest, RemoveAfterNonExistent) {
    DoublyList list;
    list.insertBack("a");
    list.removeAfter("nonexistent");
    EXPECT_EQ(list.getSize(), 1);
}

TEST(DoublyListTest, SearchEmpty) {
    DoublyList list;
    EXPECT_FALSE(list.search("anything"));
}

TEST(DoublyListTest, SearchFound) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    EXPECT_TRUE(list.search("b"));
}

TEST(DoublyListTest, SearchNotFound) {
    DoublyList list;
    list.insertBack("a");
    EXPECT_FALSE(list.search("b"));
}

TEST(DoublyListTest, ClearEmpty) {
    DoublyList list;
    list.clear();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyListTest, ClearNonEmpty) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    list.insertBack("c");
    list.clear();
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyListTest, PrintForwardEmpty) {
    DoublyList list;
    EXPECT_NO_THROW(list.printForward());
}

TEST(DoublyListTest, PrintForwardNonEmpty) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    EXPECT_NO_THROW(list.printForward());
}

TEST(DoublyListTest, PrintBackwardEmpty) {
    DoublyList list;
    EXPECT_NO_THROW(list.printBackward());
}

TEST(DoublyListTest, PrintBackwardNonEmpty) {
    DoublyList list;
    list.insertBack("a");
    list.insertBack("b");
    EXPECT_NO_THROW(list.printBackward());
}

TEST(DoublyListTest, SerializeEmpty) {
    DoublyList list;
    EXPECT_NO_THROW(list.serializeToFile("empty_dbl_test.bin"));
    
    DoublyList newList;
    EXPECT_NO_THROW(newList.deserializeFromFile("empty_dbl_test.bin"));
    EXPECT_EQ(newList.getSize(), 0);
    
    std::remove("empty_dbl_test.bin");
}

TEST(DoublyListTest, SerializeNonEmpty) {
    DoublyList list;
    list.insertBack("hello");
    list.insertBack("world");
    list.insertBack("test");
    
    EXPECT_NO_THROW(list.serializeToFile("dbl_test.bin"));
    
    DoublyList newList;
    EXPECT_NO_THROW(newList.deserializeFromFile("dbl_test.bin"));
    
    EXPECT_EQ(newList.getSize(), 3);
    EXPECT_TRUE(newList.search("hello"));
    EXPECT_TRUE(newList.search("world"));
    EXPECT_TRUE(newList.search("test"));
    
    std::remove("dbl_test.bin");
}

TEST(DoublyListTest, SerializeInvalidFile) {
    DoublyList list;
    list.insertBack("test");
    EXPECT_THROW(list.serializeToFile("/invalid/path/test.bin"), std::runtime_error);
}

TEST(DoublyListTest, DeserializeNonExistentFile) {
    DoublyList list;
    EXPECT_THROW(list.deserializeFromFile("nonexistent_dbl.bin"), std::runtime_error);
}

TEST(DoublyListTest, DeserializeCorruptedFile) {
    std::ofstream file("corrupted_dbl.bin", std::ios::binary);
    file.write("corrupted data", 14);
    file.close();
    
    DoublyList list;
    EXPECT_THROW(list.deserializeFromFile("corrupted_dbl.bin"), std::runtime_error);
    
    std::remove("corrupted_dbl.bin");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}