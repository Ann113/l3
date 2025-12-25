#include <gtest/gtest.h>
#include "../src/array.h"
#include <stdexcept>

TEST(ArrayTest, DefaultConstructor) {
    Array arr;
    EXPECT_EQ(arr.length(), 0);
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_GE(arr.getCapacity(), 10);
}

TEST(ArrayTest, ParameterizedConstructor) {
    Array arr(20);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_GE(arr.getCapacity(), 20);
}

TEST(ArrayTest, PushBack) {
    Array arr;
    arr.push_back("test1");
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.get(0), "test1");
    
    arr.push_back("test2");
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.get(1), "test2");
}

TEST(ArrayTest, InsertAtBeginning) {
    Array arr;
    arr.push_back("b");
    arr.push_back("c");
    arr.insert(0, "a");
    
    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.get(0), "a");
    EXPECT_EQ(arr.get(1), "b");
    EXPECT_EQ(arr.get(2), "c");
}

TEST(ArrayTest, InsertAtMiddle) {
    Array arr;
    arr.push_back("a");
    arr.push_back("c");
    arr.insert(1, "b");
    
    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.get(0), "a");
    EXPECT_EQ(arr.get(1), "b");
    EXPECT_EQ(arr.get(2), "c");
}

TEST(ArrayTest, InsertAtEnd) {
    Array arr;
    arr.push_back("a");
    arr.push_back("b");
    arr.insert(2, "c");
    
    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.get(2), "c");
}

TEST(ArrayTest, InsertOutOfBounds) {
    Array arr;
    EXPECT_THROW(arr.insert(5, "test"), std::out_of_range);
    
    arr.push_back("a");
    EXPECT_THROW(arr.insert(2, "test"), std::out_of_range);
}

TEST(ArrayTest, GetValidIndex) {
    Array arr;
    arr.push_back("first");
    arr.push_back("second");
    
    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "second");
}

TEST(ArrayTest, GetInvalidIndex) {
    Array arr;
    arr.push_back("test");
    
    EXPECT_THROW(arr.get(-1), std::out_of_range);
    EXPECT_THROW(arr.get(5), std::out_of_range);
}

TEST(ArrayTest, RemoveFromBeginning) {
    Array arr;
    arr.push_back("a");
    arr.push_back("b");
    arr.push_back("c");
    
    arr.remove(0);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.get(0), "b");
    EXPECT_EQ(arr.get(1), "c");
}

TEST(ArrayTest, RemoveFromMiddle) {
    Array arr;
    arr.push_back("a");
    arr.push_back("b");
    arr.push_back("c");
    
    arr.remove(1);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.get(0), "a");
    EXPECT_EQ(arr.get(1), "c");
}

TEST(ArrayTest, RemoveFromEnd) {
    Array arr;
    arr.push_back("a");
    arr.push_back("b");
    arr.push_back("c");
    
    arr.remove(2);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.get(0), "a");
    EXPECT_EQ(arr.get(1), "b");
}

TEST(ArrayTest, RemoveInvalidIndex) {
    Array arr;
    arr.push_back("test");
    
    EXPECT_THROW(arr.remove(-1), std::out_of_range);
    EXPECT_THROW(arr.remove(5), std::out_of_range);
}

TEST(ArrayTest, ReplaceElement) {
    Array arr;
    arr.push_back("old");
    arr.replace(0, "new");
    
    EXPECT_EQ(arr.get(0), "new");
}

TEST(ArrayTest, ReplaceInvalidIndex) {
    Array arr;
    arr.push_back("test");
    
    EXPECT_THROW(arr.replace(-1, "new"), std::out_of_range);
    EXPECT_THROW(arr.replace(5, "new"), std::out_of_range);
}

TEST(ArrayTest, ClearArray) {
    Array arr;
    arr.push_back("a");
    arr.push_back("b");
    arr.push_back("c");
    
    EXPECT_EQ(arr.length(), 3);
    arr.clear();
    EXPECT_EQ(arr.length(), 0);
    EXPECT_TRUE(arr.isEmpty());
}

TEST(ArrayTest, ArrayResize) {
    Array arr(2); // Начальная емкость 2
    arr.push_back("a");
    arr.push_back("b");
    
    // Должен произойти resize
    arr.push_back("c");
    EXPECT_EQ(arr.length(), 3);
    EXPECT_GE(arr.getCapacity(), 3);
    
    // Проверяем, что элементы сохранились
    EXPECT_EQ(arr.get(0), "a");
    EXPECT_EQ(arr.get(1), "b");
    EXPECT_EQ(arr.get(2), "c");
}

TEST(ArrayTest, OperatorAccess) {
    Array arr;
    arr.push_back("first");
    arr.push_back("second");
    
    // Неизменяемый доступ
    EXPECT_EQ(arr[0], "first");
    EXPECT_EQ(arr[1], "second");
    
    // Изменяемый доступ
    arr[0] = "modified";
    EXPECT_EQ(arr[0], "modified");
}

TEST(ArrayTest, OperatorAccessOutOfBounds) {
    Array arr;
    arr.push_back("test");
    
    EXPECT_THROW(arr[-1], std::out_of_range);
    EXPECT_THROW(arr[5], std::out_of_range);
}

TEST(ArrayTest, Serialization) {
    Array arr;
    arr.push_back("test1");
    arr.push_back("test2");
    arr.push_back("test3 with spaces");
    
    // Сериализация
    arr.serializeToFile("test_array.bin");
    
    // Десериализация в новый массив
    Array arr2;
    arr2.deserializeFromFile("test_array.bin");
    
    // Проверка
    EXPECT_EQ(arr2.length(), 3);
    EXPECT_EQ(arr2.get(0), "test1");
    EXPECT_EQ(arr2.get(1), "test2");
    EXPECT_EQ(arr2.get(2), "test3 with spaces");
    
    // Очистка
    remove("test_array.bin");
}

TEST(ArrayTest, PrintFunction) {
    Array arr;
    arr.push_back("a");
    arr.push_back("b");
    arr.push_back("c");
    
    // Проверяем, что функция не падает
    EXPECT_NO_THROW(arr.print());
    
    // Проверяем getAllData
    auto data = arr.getAllData();
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], "a");
    EXPECT_EQ(data[1], "b");
    EXPECT_EQ(data[2], "c");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}