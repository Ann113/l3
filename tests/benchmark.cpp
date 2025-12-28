#include <benchmark/benchmark.h>
#include "../src/array.h"
#include "../src/singly_list.h"
#include "../src/doubly_list.h"
#include "../src/stack.h"
#include "../src/queue.h"
#include "../src/hash_table.h"
#include "../src/tree.h"
#include <string>
#include <vector>
#include <random>

// Генератор случайных строк
std::string generateRandomString(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ" 
        "abcdefghijklmnopqrstuvwxyz";
    
    std::string result;
    result.reserve(length);
    
    for (int i = 0; i < length; ++i) {
        result.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }
    
    return result;
}

// ==================== Array Benchmarks ====================

static void BM_ArrayPushBack(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        Array arr;
        state.ResumeTiming();
        
        for (int i = 0; i < num_elements; ++i) {
            arr.push_back("element_" + std::to_string(i));
        }
        
        benchmark::DoNotOptimize(arr);
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_ArrayPushBack)->Range(8, 8<<10)->Complexity();

static void BM_ArrayInsertAtBeginning(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        Array arr;
        // Сначала заполняем массив
        for (int i = 0; i < 1000; ++i) {
            arr.push_back("base_" + std::to_string(i));
        }
        state.ResumeTiming();
        
        // Вставляем в начало (дорогая операция)
        for (int i = 0; i < num_elements; ++i) {
            arr.insert(0, "inserted_" + std::to_string(i));
        }
        
        benchmark::DoNotOptimize(arr);
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_ArrayInsertAtBeginning)->Range(8, 512)->Complexity();

static void BM_ArrayAccessRandom(benchmark::State& state) {
    const int size = state.range(0);
    Array arr;
    
    // Заполняем массив
    for (int i = 0; i < size; ++i) {
        arr.push_back("element_" + std::to_string(i));
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    
    for (auto _ : state) {
        int index = dis(gen);
        benchmark::DoNotOptimize(arr.get(index));
    }
    
    state.SetComplexityN(size);
}
BENCHMARK(BM_ArrayAccessRandom)->Range(8, 8<<10)->Complexity();

// ==================== Singly Linked List Benchmarks ====================

static void BM_SinglyListInsertBack(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        SinglyList list;
        state.ResumeTiming();
        
        for (int i = 0; i < num_elements; ++i) {
            list.insertBack("element_" + std::to_string(i));
        }
        
        benchmark::DoNotOptimize(list);
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_SinglyListInsertBack)->Range(8, 8<<10)->Complexity();

static void BM_SinglyListInsertFront(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        SinglyList list;
        state.ResumeTiming();
        
        for (int i = 0; i < num_elements; ++i) {
            list.insertFront("element_" + std::to_string(i));
        }
        
        benchmark::DoNotOptimize(list);
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_SinglyListInsertFront)->Range(8, 8<<10)->Complexity();

static void BM_SinglyListSearch(benchmark::State& state) {
    const int size = state.range(0);
    SinglyList list;
    
    // Заполняем список
    for (int i = 0; i < size; ++i) {
        list.insertBack("element_" + std::to_string(i));
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    
    for (auto _ : state) {
        int target = dis(gen);
        benchmark::DoNotOptimize(list.search("element_" + std::to_string(target)));
    }
    
    state.SetComplexityN(size);
}
BENCHMARK(BM_SinglyListSearch)->Range(8, 8<<10)->Complexity();

// ==================== Doubly Linked List Benchmarks ====================

static void BM_DoublyListInsertBack(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        DoublyList list;
        state.ResumeTiming();
        
        for (int i = 0; i < num_elements; ++i) {
            list.insertBack("element_" + std::to_string(i));
        }
        
        benchmark::DoNotOptimize(list);
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_DoublyListInsertBack)->Range(8, 8<<10)->Complexity();

static void BM_DoublyListTraversal(benchmark::State& state) {
    const int size = state.range(0);
    DoublyList list;
    
    // Заполняем список
    for (int i = 0; i < size; ++i) {
        list.insertBack("element_" + std::to_string(i));
    }
    
    for (auto _ : state) {
        // Просто измеряем время создания (в реальности нужен итератор)
        benchmark::DoNotOptimize(list.getSize());
    }
    
    state.SetComplexityN(size);
}
BENCHMARK(BM_DoublyListTraversal)->Range(8, 8<<10)->Complexity();

// ==================== Stack Benchmarks ====================

static void BM_StackPushPop(benchmark::State& state) {
    const int num_operations = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        Stack stack;
        state.ResumeTiming();
        
        for (int i = 0; i < num_operations; ++i) {
            stack.push("element_" + std::to_string(i));
        }
        
        for (int i = 0; i < num_operations; ++i) {
            benchmark::DoNotOptimize(stack.pop());
        }
        
        benchmark::DoNotOptimize(stack);
    }
    
    state.SetComplexityN(num_operations);
}
BENCHMARK(BM_StackPushPop)->Range(8, 8<<10)->Complexity();

// ==================== Queue Benchmarks ====================

static void BM_QueueEnqueueDequeue(benchmark::State& state) {
    const int num_operations = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        Queue queue;
        state.ResumeTiming();
        
        for (int i = 0; i < num_operations; ++i) {
            queue.enqueue("element_" + std::to_string(i));
        }
        
        for (int i = 0; i < num_operations; ++i) {
            benchmark::DoNotOptimize(queue.dequeue());
        }
        
        benchmark::DoNotOptimize(queue);
    }
    
    state.SetComplexityN(num_operations);
}
BENCHMARK(BM_QueueEnqueueDequeue)->Range(8, 8<<10)->Complexity();

// ==================== Hash Table Benchmarks ====================

static void BM_HashTableInsert(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        HashTable ht(num_elements * 2); // Увеличиваем capacity для уменьшения коллизий
        state.ResumeTiming();
        
        for (int i = 0; i < num_elements; ++i) {
            ht.insert(i, "value_" + std::to_string(i));
        }
        
        benchmark::DoNotOptimize(ht);
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_HashTableInsert)->Range(8, 8<<10)->Complexity();

static void BM_HashTableSearch(benchmark::State& state) {
    const int size = state.range(0);
    HashTable ht(size * 2);
    
    // Заполняем таблицу
    for (int i = 0; i < size; ++i) {
        ht.insert(i, "value_" + std::to_string(i));
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    
    for (auto _ : state) {
        int key = dis(gen);
        benchmark::DoNotOptimize(ht.search(key));
    }
    
    state.SetComplexityN(size);
}
BENCHMARK(BM_HashTableSearch)->Range(8, 8<<10)->Complexity();

// ==================== Tree Benchmarks ====================

static void BM_TreeInsert(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        Tree tree;
        state.ResumeTiming();
        
        for (int i = 0; i < num_elements; ++i) {
            tree.insert("element_" + std::to_string(i));
        }
        
        benchmark::DoNotOptimize(tree);
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_TreeInsert)->Range(8, 8<<10)->Complexity();

static void BM_TreeSearch(benchmark::State& state) {
    const int size = state.range(0);
    Tree tree;
    
    // Заполняем дерево
    for (int i = 0; i < size; ++i) {
        tree.insert("element_" + std::to_string(i));
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    
    for (auto _ : state) {
        int target = dis(gen);
        benchmark::DoNotOptimize(tree.search("element_" + std::to_string(target)));
    }
    
    state.SetComplexityN(size);
}
BENCHMARK(BM_TreeSearch)->Range(8, 8<<10)->Complexity();

static void BM_TreeTraversal(benchmark::State& state) {
    const int size = state.range(0);
    Tree tree;
    
    // Заполняем дерево
    for (int i = 0; i < size; ++i) {
        tree.insert("element_" + std::to_string(i));
    }
    
    for (auto _ : state) {
        auto result = tree.inorder();
        benchmark::DoNotOptimize(result);
    }
    
    state.SetComplexityN(size);
}
BENCHMARK(BM_TreeTraversal)->Range(8, 8<<10)->Complexity();

// ==================== Comparison Benchmarks ====================

static void BM_CompareInsertion(benchmark::State& state) {
    const int num_elements = state.range(0);
    
    for (auto _ : state) {
        // Array
        state.PauseTiming();
        Array arr;
        state.ResumeTiming();
        for (int i = 0; i < num_elements; ++i) {
            arr.push_back("arr_" + std::to_string(i));
        }
        
        // Singly List
        state.PauseTiming();
        SinglyList slist;
        state.ResumeTiming();
        for (int i = 0; i < num_elements; ++i) {
            slist.insertBack("slist_" + std::to_string(i));
        }
        
        // Doubly List
        state.PauseTiming();
        DoublyList dlist;
        state.ResumeTiming();
        for (int i = 0; i < num_elements; ++i) {
            dlist.insertBack("dlist_" + std::to_string(i));
        }
    }
    
    state.SetComplexityN(num_elements);
}
BENCHMARK(BM_CompareInsertion)->Range(8, 1024)->Complexity();

BENCHMARK_MAIN();