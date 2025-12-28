cmake_minimum_required(VERSION 3.10)
project(l3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы
set(SRC_FILES
    src/array.cpp
    src/singly_list.cpp
    src/doubly_list.cpp
    src/serializer.cpp
    src/stack.cpp
    src/queue.cpp
    src/hash_table.cpp
    src/tree.cpp
)

# Основная программа
add_executable(main src/main.cpp ${SRC_FILES})

# Найти GTest
find_package(GTest REQUIRED) 
include_directories(${GTEST_INCLUDE_DIRS})

# Тесты
add_executable(test_array tests/test_array.cpp ${SRC_FILES})
target_link_libraries(test_array GTest::gtest GTest::gtest_main pthread)

add_executable(test_serializer tests/test_serializer.cpp ${SRC_FILES})
target_link_libraries(test_serializer GTest::gtest GTest::gtest_main pthread)

add_executable(test_list tests/test_list.cpp ${SRC_FILES})
target_link_libraries(test_list GTest::gtest GTest::gtest_main pthread)

add_executable(test_stack tests/test_stack.cpp ${SRC_FILES})
target_link_libraries(test_stack GTest::gtest GTest::gtest_main pthread)

add_executable(test_queue tests/test_queue.cpp ${SRC_FILES})
target_link_libraries(test_queue GTest::gtest GTest::gtest_main pthread)

add_executable(test_hash_table tests/test_hash_table.cpp ${SRC_FILES})
target_link_libraries(test_hash_table GTest::gtest GTest::gtest_main pthread)

add_executable(test_tree tests/test_tree.cpp ${SRC_FILES})
target_link_libraries(test_tree GTest::gtest GTest::gtest_main pthread)

# Добавить тесты
enable_testing()
add_test(NAME test_array COMMAND test_array)
add_test(NAME test_serializer COMMAND test_serializer)
add_test(NAME test_list COMMAND test_list)
add_test(NAME test_stack COMMAND test_stack)
add_test(NAME test_queue COMMAND test_queue)
add_test(NAME test_hash_table COMMAND test_hash_table)
add_test(NAME test_tree COMMAND test_tree)
