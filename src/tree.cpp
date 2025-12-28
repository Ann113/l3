#include "tree.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>

Tree::Tree() : root(nullptr) {}

Tree::~Tree() {
    clear();
}

void Tree::clear() {
    destroyTree(root); 
    root = nullptr;
}

void Tree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

Tree::TreeNode* Tree::insertHelper(TreeNode* node, const std::string& value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }
    
    // Для полного бинарного дерева вставляем в первую доступную позицию
    // Используем обход в ширину для нахождения первой свободной позиции
    if (node->left == nullptr) {
        node->left = new TreeNode(value);
    } else if (node->right == nullptr) {
        node->right = new TreeNode(value);
    } else {
        // Если оба потомка существуют, рекурсивно вставляем в левое поддерево
        // Для поддержания свойства полноты
        if (heightHelper(node->left) <= heightHelper(node->right)) {
            node->left = insertHelper(node->left, value);
        } else {
            node->right = insertHelper(node->right, value);
        }
    }
    
    return node;
}

void Tree::insert(const std::string& value) {
    if (root == nullptr) {
        root = new TreeNode(value);
    } else {
        root = insertHelper(root, value);
    }
}

Tree::TreeNode* Tree::searchHelper(TreeNode* node, const std::string& value) const {
    if (node == nullptr || node->data == value) {
        return node;
    }
    
    TreeNode* leftResult = searchHelper(node->left, value);
    if (leftResult != nullptr) {
        return leftResult;
    }
    
    return searchHelper(node->right, value);
}

bool Tree::search(const std::string& value) const {
    return searchHelper(root, value) != nullptr;
}

Tree::TreeNode* Tree::findMin(TreeNode* node) const {
    if (node == nullptr) return nullptr;
    
    // Для небинарного дерева поиска просто ищем минимальное по алфавиту
    TreeNode* minNode = node;
    TreeNode* leftMin = findMin(node->left);
    TreeNode* rightMin = findMin(node->right);
    
    if (leftMin != nullptr && leftMin->data < minNode->data) {
        minNode = leftMin;
    }
    if (rightMin != nullptr && rightMin->data < minNode->data) {
        minNode = rightMin;
    }
    
    return minNode;
}

Tree::TreeNode* Tree::removeHelper(TreeNode* node, const std::string& value) {
    if (node == nullptr) return nullptr;
    
    if (node->data == value) {
        // Узел найден
        if (node->left == nullptr && node->right == nullptr) {
            // Лист
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            // Узел с двумя потомками
            // Для полного бинарного дерева просто удаляем
            // Можно заменить на самый нижний правый лист
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeHelper(node->right, temp->data);
        }
    } else {
        node->left = removeHelper(node->left, value);
        node->right = removeHelper(node->right, value);
    }
    
    return node;
}

void Tree::remove(const std::string& value) {
    root = removeHelper(root, value);
}

void Tree::inorderHelper(TreeNode* node, std::vector<std::string>& result) const {
    if (node != nullptr) {
        inorderHelper(node->left, result);
        result.push_back(node->data);
        inorderHelper(node->right, result);
    }
}

std::vector<std::string> Tree::inorder() const {
    std::vector<std::string> result;
    inorderHelper(root, result);
    return result;
}

void Tree::preorderHelper(TreeNode* node, std::vector<std::string>& result) const {
    if (node != nullptr) {
        result.push_back(node->data);
        preorderHelper(node->left, result);
        preorderHelper(node->right, result);
    }
}

std::vector<std::string> Tree::preorder() const {
    std::vector<std::string> result;
    preorderHelper(root, result);
    return result;
}

void Tree::postorderHelper(TreeNode* node, std::vector<std::string>& result) const {
    if (node != nullptr) {
        postorderHelper(node->left, result);
        postorderHelper(node->right, result);
        result.push_back(node->data);
    }
}

std::vector<std::string> Tree::postorder() const {
    std::vector<std::string> result;
    postorderHelper(root, result);
    return result;
}

std::vector<std::string> Tree::levelOrder() const {
    std::vector<std::string> result;
    if (root == nullptr) return result;
    
    std::queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        result.push_back(current->data);
        
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
    
    return result;
}

int Tree::heightHelper(TreeNode* node) const {
    if (node == nullptr) {
        return -1;
    }
    return 1 + std::max(heightHelper(node->left), heightHelper(node->right));
}

int Tree::height() const {
    return heightHelper(root);
}

int Tree::sizeHelper(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + sizeHelper(node->left) + sizeHelper(node->right);
}

int Tree::size() const {
    return sizeHelper(root);
}

bool Tree::isFullHelper(TreeNode* node) const {
    if (node == nullptr) {
        return true;
    }
    
    // Лист
    if (node->left == nullptr && node->right == nullptr) {
        return true;
    }
    
    // Узел с двумя потомками
    if (node->left != nullptr && node->right != nullptr) {
        return isFullHelper(node->left) && isFullHelper(node->right);
    }
    
    // Узел с одним потомком
    return false;
}
bool Tree::isFullBinaryTree() const {
    return isFullHelper(root);
}



int Tree::countNodesHelper(TreeNode* node) const {
    if (node == nullptr) return 0;
    return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
}

bool Tree::isCompleteHelper(TreeNode* node, int index, int nodeCount) const {
    if (node == nullptr) return true;
    
    if (index >= nodeCount) return false;
    
    return isCompleteHelper(node->left, 2 * index + 1, nodeCount) &&
           isCompleteHelper(node->right, 2 * index + 2, nodeCount);
}

bool Tree::isCompleteBinaryTree() const {
    int nodeCount = countNodesHelper(root);
    return isCompleteHelper(root, 0, nodeCount);
}

bool Tree::isPerfectBinaryTree() const {
    int h = height();
    int expectedNodes = (1 << (h + 1)) - 1; // 2^(h+1) - 1
    return size() == expectedNodes;
}

void Tree::printTreeHelper(TreeNode* node, int depth, bool isLeft) const {
    if (node == nullptr) return;
    
    printTreeHelper(node->right, depth + 1, false);
    
    std::string indent;
    for (int i = 0; i < depth; i++) {
        indent += "    ";
    }
    
    std::cout << indent;
    if (depth > 0) {
        std::cout << (isLeft ? "└── " : "┌── ");
    }
    
    std::cout << node->data << std::endl;
    
    printTreeHelper(node->left, depth + 1, true);
}

void Tree::printTree() const {
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    
    std::cout << "Binary Tree Structure:" << std::endl;
    printTreeHelper(root);
}

void Tree::serializeHelper(TreeNode* node, std::vector<std::string>& result) const {
    if (node == nullptr) {
        result.push_back("NULL");
        return;
    }
    
    result.push_back(node->data);
    serializeHelper(node->left, result);
    serializeHelper(node->right, result);
}

void Tree::serializeToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    std::vector<std::string> serializedData;
    serializeHelper(root, serializedData);
    
    int dataSize = serializedData.size();
    file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
    
    for (const auto& str : serializedData) {
        int strSize = str.size();
        file.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
        file.write(str.c_str(), strSize);
    }
    
    file.close();
}

Tree::TreeNode* Tree::deserializeHelper(const std::vector<std::string>& data, int& index) {
    if (index >= data.size() || data[index] == "NULL") {
        index++;
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(data[index]);
    index++;
    
    node->left = deserializeHelper(data, index);
    node->right = deserializeHelper(data, index);
    
    return node;
}

void Tree::deserializeFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    clear();
    
    int dataSize;
    file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
    
    std::vector<std::string> serializedData;
    for (int i = 0; i < dataSize; i++) {
        int strSize;
        file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
        
        std::string value(strSize, '\0');
        file.read(&value[0], strSize);
        serializedData.push_back(value);
    }
    
    int index = 0;
    root = deserializeHelper(serializedData, index);
    
    file.close();
}