#include <gtest/gtest.h>
#include "../src/queue.h"
#include <stdexcept>

TEST(QueueTest, DefaultConstructor) {
    Queue queue;
    EXPECT_EQ(queue.getSize(), 0);
    EXPECT_TRUE(queue.isEmpty());
}

TEST(QueueTest, Enqueue) {
    Queue queue;
    queue.enqueue("first");
    
    EXPECT_EQ(queue.getSize(), 1);
    EXPECT_FALSE(queue.isEmpty());
    
    queue.enqueue("second");
    EXPECT_EQ(queue.getSize(), 2);
}

TEST(QueueTest, Dequeue) {
    Queue queue;
    queue.enqueue("first");
    queue.enqueue("second");
    
    EXPECT_EQ(queue.dequeue(), "first");
    EXPECT_EQ(queue.getSize(), 1);
    
    EXPECT_EQ(queue.dequeue(), "second");
    EXPECT_EQ(queue.getSize(), 0);
    EXPECT_TRUE(queue.isEmpty());
}

TEST(QueueTest, DequeueFromEmptyQueue) {
    Queue queue;
    EXPECT_THROW(queue.dequeue(), std::runtime_error);
}

TEST(QueueTest, Peek) {
    Queue queue;
    queue.enqueue("first");
    queue.enqueue("second");
    
    EXPECT_EQ(queue.peek(), "first");
    EXPECT_EQ(queue.getSize(), 2); // peek не должен удалять
    
    queue.dequeue();
    EXPECT_EQ(queue.peek(), "second");
}

TEST(QueueTest, PeekEmptyQueue) {
    Queue queue;
    EXPECT_THROW(queue.peek(), std::runtime_error);
}

TEST(QueueTest, MultipleOperations) {
    Queue queue;
    
    // Серия операций
    queue.enqueue("a");
    queue.enqueue("b");
    EXPECT_EQ(queue.peek(), "a");
    
    queue.enqueue("c");
    EXPECT_EQ(queue.getSize(), 3);
    
    EXPECT_EQ(queue.dequeue(), "a");
    EXPECT_EQ(queue.dequeue(), "b");
    EXPECT_EQ(queue.dequeue(), "c");
    
    EXPECT_TRUE(queue.isEmpty());
}

TEST(QueueTest, FIFOProperty) {
    Queue queue;
    
    // Проверяем свойство FIFO (First In, First Out)
    queue.enqueue("1");
    queue.enqueue("2");
    queue.enqueue("3");
    
    EXPECT_EQ(queue.dequeue(), "1");
    EXPECT_EQ(queue.dequeue(), "2");
    EXPECT_EQ(queue.dequeue(), "3");
}

TEST(QueueTest, PrintQueue) {
    Queue queue;
    queue.enqueue("a");
    queue.enqueue("b");
    queue.enqueue("c");
    
    // Проверяем, что функция не падает
    EXPECT_NO_THROW(queue.print());
}

TEST(QueueTest, Serialization) {
    Queue queue;
    queue.enqueue("first");
    queue.enqueue("second");
    queue.enqueue("third");
    
    // Сериализация
    queue.serializeToFile("test_queue.bin");
    
    // Десериализация в новую очередь
    Queue queue2;
    queue2.deserializeFromFile("test_queue.bin");
    
    // Проверяем FIFO свойство
    EXPECT_EQ(queue2.getSize(), 3);
    EXPECT_EQ(queue2.dequeue(), "first");
    EXPECT_EQ(queue2.dequeue(), "second");
    EXPECT_EQ(queue2.dequeue(), "third");
    
    // Очистка
    remove("test_queue.bin");
}

TEST(QueueTest, EmptyQueueSerialization) {
    Queue queue;
    
    // Сериализация пустой очереди
    queue.serializeToFile("test_empty_queue.bin");
    
    Queue queue2;
    queue2.deserializeFromFile("test_empty_queue.bin");
    
    EXPECT_TRUE(queue2.isEmpty());
    EXPECT_EQ(queue2.getSize(), 0);
    
    remove("test_empty_queue.bin");
}

TEST(QueueTest, LargeQueue) {
    Queue queue;
    const int N = 1000;
    
    // Добавляем много элементов
    for (int i = 0; i < N; i++) {
        queue.enqueue("element_" + std::to_string(i));
    }
    
    EXPECT_EQ(queue.getSize(), N);
    
    // Извлекаем все элементы
    for (int i = 0; i < N; i++) {
        EXPECT_EQ(queue.dequeue(), "element_" + std::to_string(i));
    }
    
    EXPECT_TRUE(queue.isEmpty());
}

TEST(QueueTest, InterleavedOperations) {
    Queue queue;
    
    // Чередуем операции enqueue и dequeue
    queue.enqueue("a");
    queue.enqueue("b");
    EXPECT_EQ(queue.dequeue(), "a");
    
    queue.enqueue("c");
    queue.enqueue("d");
    EXPECT_EQ(queue.dequeue(), "b");
    EXPECT_EQ(queue.dequeue(), "c");
    
    queue.enqueue("e");
    EXPECT_EQ(queue.dequeue(), "d");
    EXPECT_EQ(queue.dequeue(), "e");
    
    EXPECT_TRUE(queue.isEmpty());
}

TEST(QueueTest, ClearQueue) {
    Queue queue;
    queue.enqueue("a");
    queue.enqueue("b");
    queue.enqueue("c");
    
    // Очищаем очередь
    while (!queue.isEmpty()) {
        queue.dequeue();
    }
    
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.getSize(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}