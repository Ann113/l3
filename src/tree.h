#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

class Tree {
private:
    struct TreeNode {
        std::string data;
        TreeNode* left;
        TreeNode* right;
        
        TreeNode(const std::string& value) 
            : data(value), left(nullptr), right(nullptr) {}
    };
    
    TreeNode* root;
    
    // Вспомогательные рекурсивные методы
    TreeNode* insertHelper(TreeNode* node, const std::string& value);
    TreeNode* searchHelper(TreeNode* node, const std::string& value) const;
    TreeNode* findMin(TreeNode* node) const;
    TreeNode* removeHelper(TreeNode* node, const std::string& value);
    void destroyTree(TreeNode* node);
    void inorderHelper(TreeNode* node, std::vector<std::string>& result) const;
    void preorderHelper(TreeNode* node, std::vector<std::string>& result) const;
    void postorderHelper(TreeNode* node, std::vector<std::string>& result) const;
    int heightHelper(TreeNode* node) const;
    int sizeHelper(TreeNode* node) const;
    bool isFullHelper(TreeNode* node) const;
    bool isCompleteHelper(TreeNode* node, int index, int nodeCount) const;
    int countNodesHelper(TreeNode* node) const;
    void serializeHelper(TreeNode* node, std::vector<std::string>& result) const;
    TreeNode* deserializeHelper(const std::vector<std::string>& data, int& index);
    void printTreeHelper(TreeNode* node, int depth = 0, bool isLeft = false) const;
    
public:
    // Конструкторы и деструктор
    Tree();
    ~Tree();
    
    // Запрет копирования
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;
    
    // Основные операции
    void insert(const std::string& value);
    bool search(const std::string& value) const;
    void remove(const std::string& value);
    
    // Обходы дерева
    std::vector<std::string> inorder() const;
    std::vector<std::string> preorder() const;
    std::vector<std::string> postorder() const;
    std::vector<std::string> levelOrder() const;
    
    // Проверки свойств
    bool isFullBinaryTree() const;
    bool isCompleteBinaryTree() const;
    bool isPerfectBinaryTree() const;
    
    // Утилиты
    int height() const;
    int size() const;
    bool isEmpty() const { return root == nullptr; }
    void clear();
    void printTree() const;
    
    // Сериализация
    void serializeToFile(const std::string& filename) const;
    void deserializeFromFile(const std::string& filename);
    
    // Для тестирования
    const TreeNode* getRoot() const { return root; }
};

#endif