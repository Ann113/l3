# Основные исходные файлы
set(SOURCES
    array.cpp
    singly_list.cpp
    doubly_list.cpp
    stack.cpp
    queue.cpp
    hash_table.cpp
    tree.cpp
    serializer.cpp
    main.cpp
)
 
# Создаем основную программу
add_executable(main ${SOURCES})
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})