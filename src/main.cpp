#include <iostream>
#include <string>
#include "array.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "stack.h"
#include "queue.h"
#include "hash_table.h"
#include "tree.h"
#include "serializer.h"

void demonstrateArray() {
    std::cout << "\n=== Demonstrating Array ===" << std::endl;
    
    Array arr;
    arr.push_back("First");
    arr.push_back("Second");
    arr.push_back("Third");
    
    std::cout << "Array after push_back: ";
    arr.print();
    
    arr.insert(1, "Inserted");
    std::cout << "After insert at index 1: ";
    arr.print();
    
    std::cout << "Element at index 2: " << arr.get(2) << std::endl;
    
    arr.remove(0);
    std::cout << "After removing index 0: ";
    arr.print();
    
    // Сериализация
    arr.serializeToFile("array_data.bin");
    
    // Десериализация
    Array arr2;
    arr2.deserializeFromFile("array_data.bin");
    std::cout << "Array after deserialization: ";
    arr2.print();
}

void demonstrateSinglyList() {
    std::cout << "\n=== Demonstrating Singly Linked List ===" << std::endl;
    
    SinglyList list;
    list.insertBack("A");
    list.insertBack("B");
    list.insertBack("C");
    
    std::cout << "List after insertBack: ";
    list.printForward();
    
    list.insertFront("Start");
    std::cout << "After insertFront: ";
    list.printForward();
    
    list.insertBefore("B", "BeforeB");
    std::cout << "After insertBefore 'B': ";
    list.printForward();
    
    list.insertAfter("B", "AfterB");
    std::cout << "After insertAfter 'B': ";
    list.printForward();
    
    list.removeValue("B");
    std::cout << "After removing 'B': ";
    list.printForward();
    
    std::cout << "Search 'BeforeB': " << (list.search("BeforeB") ? "Found" : "Not Found") << std::endl;
}

void demonstrateDoublyList() {
    std::cout << "\n=== Demonstrating Doubly Linked List ===" << std::endl;
    
    DoublyList list;
    list.insertBack("X");
    list.insertBack("Y");
    list.insertBack("Z");
    
    std::cout << "Forward: ";
    list.printForward();
    
    std::cout << "Backward: ";
    list.printBackward();
    
    list.insertBefore("Y", "BeforeY");
    std::cout << "After insertBefore 'Y': ";
    list.printForward();
    
    list.insertAfter("Y", "AfterY");
    std::cout << "After insertAfter 'Y': ";
    list.printForward();
    
    list.removeBefore("Y");
    std::cout << "After removeBefore 'Y': ";
    list.printForward();
    
    list.removeAfter("Y");
    std::cout << "After removeAfter 'Y': ";
    list.printForward();
}

void demonstrateStack() {
    std::cout << "\n=== Demonstrating Stack ===" << std::endl;
    
    Stack stack;
    stack.push("First");
    stack.push("Second");
    stack.push("Third");
    
    std::cout << "Stack after pushes: ";
    stack.print();
    
    std::cout << "Peek: " << stack.peek() << std::endl;
    
    std::cout << "Pop: " << stack.pop() << std::endl;
    std::cout << "After pop: ";
    stack.print();
}

void demonstrateQueue() {
    std::cout << "\n=== Demonstrating Queue ===" << std::endl;
    
    Queue queue;
    queue.enqueue("Customer1");
    queue.enqueue("Customer2");
    queue.enqueue("Customer3");
    
    std::cout << "Queue after enqueue: ";
    queue.print();
    
    std::cout << "Peek: " << queue.peek() << std::endl;
    
    std::cout << "Dequeue: " << queue.dequeue() << std::endl;
    std::cout << "After dequeue: ";
    queue.print();
}

void demonstrateHashTable() {
    std::cout << "\n=== Demonstrating Hash Table ===" << std::endl;
    
    HashTable hashTable(8, 0.75);
    
    hashTable.insert(1, "Alice");
    hashTable.insert(2, "Bob");
    hashTable.insert(3, "Charlie");
    hashTable.insert(17, "David"); // Коллизия с 1 при capacity=8
    
    std::cout << "Hash table contents:" << std::endl;
    hashTable.print();
    
    std::cout << "Search key 2: " << hashTable.search(2) << std::endl;
    std::cout << "Search key 10: " << hashTable.search(10) << std::endl;
    
    hashTable.remove(2);
    std::cout << "After removing key 2:" << std::endl;
    hashTable.print();
    
    hashTable.printStats();
}

void demonstrateTree() {
    std::cout << "\n=== Demonstrating Binary Tree ===" << std::endl;
    
    Tree tree;
    
    // Вставляем элементы для создания полного бинарного дерева
    tree.insert("F");
    tree.insert("B");
    tree.insert("G");
    tree.insert("A");
    tree.insert("D");
    tree.insert("I");
    tree.insert("C");
    tree.insert("E");
    tree.insert("H");
    
    std::cout << "Tree structure:" << std::endl;
    tree.printTree();
    
    std::cout << "Inorder traversal: ";
    auto inorder = tree.inorder();
    for (const auto& val : inorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Preorder traversal: ";
    auto preorder = tree.preorder();
    for (const auto& val : preorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Postorder traversal: ";
    auto postorder = tree.postorder();
    for (const auto& val : postorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Level order traversal: ";
    auto levelorder = tree.levelOrder();
    for (const auto& val : levelorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Tree height: " << tree.height() << std::endl;
    std::cout << "Tree size: " << tree.size() << std::endl;
    
    std::cout << "Is full binary tree? " << (tree.isFullBinaryTree() ? "Yes" : "No") << std::endl;
    std::cout << "Is complete binary tree? " << (tree.isCompleteBinaryTree() ? "Yes" : "No") << std::endl;
    std::cout << "Is perfect binary tree? " << (tree.isPerfectBinaryTree() ? "Yes" : "No") << std::endl;
    
    std::cout << "Search 'D': " << (tree.search("D") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'Z': " << (tree.search("Z") ? "Found" : "Not Found") << std::endl;
    
    tree.remove("D");
    std::cout << "After removing 'D':" << std::endl;
    tree.printTree();
}

int main() {
    std::cout << "=== Data Structures Laboratory 3 ===" << std::endl;
    std::cout << "Demonstrating all implemented data structures:" << std::endl;
    
    demonstrateArray();
    demonstrateSinglyList();
    demonstrateDoublyList();
    demonstrateStack();
    demonstrateQueue();
    demonstrateHashTable();
    demonstrateTree();
    
    std::cout << "\n=== End of Demonstration ===" << std::endl;
    
    return 0;
}