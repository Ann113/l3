#include <gtest/gtest.h>
#include "../src/stack.h"
#include <stdexcept>

TEST(StackTest, DefaultConstructor) {
    Stack stack;
    EXPECT_EQ(stack.getSize(), 0);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, Push) {
    Stack stack;
    stack.push("first");
    
    EXPECT_EQ(stack.getSize(), 1);
    EXPECT_FALSE(stack.isEmpty());
    
    stack.push("second");
    EXPECT_EQ(stack.getSize(), 2);
}

TEST(StackTest, Pop) {
    Stack stack;
    stack.push("first");
    stack.push("second");
    
    EXPECT_EQ(stack.pop(), "second");
    EXPECT_EQ(stack.getSize(), 1);
    
    EXPECT_EQ(stack.pop(), "first");
    EXPECT_EQ(stack.getSize(), 0);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, PopFromEmptyStack) {
    Stack stack;
    EXPECT_THROW(stack.pop(), std::runtime_error);
}

TEST(StackTest, Peek) {
    Stack stack;
    stack.push("first");
    stack.push("second");
    
    EXPECT_EQ(stack.peek(), "second");
    EXPECT_EQ(stack.getSize(), 2); // peek не должен удалять
    
    stack.pop();
    EXPECT_EQ(stack.peek(), "first");
}

TEST(StackTest, PeekEmptyStack) {
    Stack stack;
    EXPECT_THROW(stack.peek(), std::runtime_error);
}

TEST(StackTest, MultipleOperations) {
    Stack stack;
    
    // Серия операций
    stack.push("a");
    stack.push("b");
    EXPECT_EQ(stack.peek(), "b");
    
    stack.push("c");
    EXPECT_EQ(stack.getSize(), 3);
    
    EXPECT_EQ(stack.pop(), "c");
    EXPECT_EQ(stack.pop(), "b");
    EXPECT_EQ(stack.pop(), "a");
    
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, ClearStack) {
    Stack stack;
    stack.push("a");
    stack.push("b");
    stack.push("c");
    
    // В текущей реализации нет явного clear
    // Но можно очистить через pop
    while (!stack.isEmpty()) {
        stack.pop();
    }
    
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.getSize(), 0);
}

TEST(StackTest, LIFOProperty) {
    Stack stack;
    
    // Проверяем свойство LIFO (Last In, First Out)
    stack.push("1");
    stack.push("2");
    stack.push("3");
    
    EXPECT_EQ(stack.pop(), "3");
    EXPECT_EQ(stack.pop(), "2");
    EXPECT_EQ(stack.pop(), "1");
}

TEST(StackTest, PrintStack) {
    Stack stack;
    stack.push("a");
    stack.push("b");
    stack.push("c");
    
    // Проверяем, что функция не падает
    EXPECT_NO_THROW(stack.print());
}

TEST(StackTest, Serialization) {
    Stack stack;
    stack.push("first");
    stack.push("second");
    stack.push("third");
    
    // Сериализация
    stack.serializeToFile("test_stack.bin");
    
    // Десериализация в новый стек
    Stack stack2;
    stack2.deserializeFromFile("test_stack.bin");
    
    // Проверяем LIFO свойство
    EXPECT_EQ(stack2.getSize(), 3);
    EXPECT_EQ(stack2.pop(), "third");
    EXPECT_EQ(stack2.pop(), "second");
    EXPECT_EQ(stack2.pop(), "first");
    
    // Очистка
    remove("test_stack.bin");
}

TEST(StackTest, EmptyStackSerialization) {
    Stack stack;
    
    // Сериализация пустого стека
    stack.serializeToFile("test_empty_stack.bin");
    
    Stack stack2;
    stack2.deserializeFromFile("test_empty_stack.bin");
    
    EXPECT_TRUE(stack2.isEmpty());
    EXPECT_EQ(stack2.getSize(), 0);
    
    remove("test_empty_stack.bin");
}

TEST(StackTest, LargeStack) {
    Stack stack;
    const int N = 1000;
    
    // Добавляем много элементов
    for (int i = 0; i < N; i++) {
        stack.push("element_" + std::to_string(i));
    }
    
    EXPECT_EQ(stack.getSize(), N);
    
    // Извлекаем все элементы
    for (int i = N - 1; i >= 0; i--) {
        EXPECT_EQ(stack.pop(), "element_" + std::to_string(i));
    }
    
    EXPECT_TRUE(stack.isEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}