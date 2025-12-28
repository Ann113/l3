# Находим GoogleTest
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

# Тесты для массива
add_executable(test_array test_array.cpp)
target_link_libraries(test_array GTest::gtest GTest::gtest_main)
target_include_directories(test_array PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_array COMMAND test_array)

# Тесты для списков
add_executable(test_list test_list.cpp)
target_link_libraries(test_list GTest::gtest GTest::gtest_main)
target_include_directories(test_list PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_list COMMAND test_list)

# Тесты для стека
add_executable(test_stack test_stack.cpp)
target_link_libraries(test_stack GTest::gtest GTest::gtest_main)
target_include_directories(test_stack PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_stack COMMAND test_stack)

# Тесты для очереди
add_executable(test_queue test_queue.cpp)
target_link_libraries(test_queue GTest::gtest GTest::gtest_main)
target_include_directories(test_queue PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_queue COMMAND test_queue)

# Тесты для хеш-таблицы
add_executable(test_hash_table test_hash_table.cpp)
target_link_libraries(test_hash_table GTest::gtest GTest::gtest_main)
target_include_directories(test_hash_table PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_hash_table COMMAND test_hash_table)

# Тесты для дерева
add_executable(test_tree test_tree.cpp)
target_link_libraries(test_tree GTest::gtest GTest::gtest_main)
target_include_directories(test_tree PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_tree COMMAND test_tree)

# Общий тестовый запускатель
add_executable(run_tests
    test_array.cpp
    test_list.cpp
    test_stack.cpp
    test_queue.cpp
    test_hash_table.cpp
    test_tree.cpp 
)
target_link_libraries(run_tests GTest::gtest GTest::gtest_main)
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Бенчмарки
if(BENCHMARK)
    add_executable(benchmark benchmark.cpp)
    target_link_libraries(benchmark benchmark::benchmark)
    target_include_directories(benchmark PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()