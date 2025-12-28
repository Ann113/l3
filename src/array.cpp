#include "array.h"
#include <fstream>
#include <vector>
#include <stdexcept>

Array::Array() : capacity(10), size(0) {
    data.resize(capacity);
}

Array::Array(int initialCapacity) : capacity(initialCapacity), size(0) {
    if (initialCapacity <= 0) {
        capacity = 10;
    }
    data.resize(capacity);
}
 
Array::~Array() {
    // vector сам очистит память
}

void Array::resize() {
    capacity *= 2;
    data.resize(capacity);
}

void Array::push_back(const std::string& value) {
    if (size >= capacity) {
        resize();
    }
    data[size] = value;
    size++;
}

void Array::insert(int index, const std::string& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range");
    }
    
    if (size >= capacity) {
        resize();
    }
    
    // Сдвигаем элементы вправо
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    
    data[index] = value;
    size++;
}

std::string Array::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Array::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    // Сдвигаем элементы влево
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

void Array::replace(int index, const std::string& value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

int Array::length() const {
    return size;
}

bool Array::isEmpty() const {
    return size == 0;
}

void Array::clear() {
    size = 0;
    // Не уменьшаем capacity, только сбрасываем size
}

void Array::serializeToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    // Записываем размер массива
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // Записываем каждый элемент
    for (int i = 0; i < size; i++) {
        int strSize = data[i].size();
        file.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
        file.write(data[i].c_str(), strSize);
    }
    
    file.close();
}

void Array::deserializeFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    // Читаем размер
    int newSize;
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    
    if (newSize < 0) {
        throw std::runtime_error("Invalid file format");
    }
    
    // Очищаем текущий массив
    clear();
    
    // Изменяем размер при необходимости
    if (newSize > capacity) {
        capacity = newSize;
        data.resize(capacity);
    }
    
    // Читаем элементы
    for (int i = 0; i < newSize; i++) {
        int strSize;
        file.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
        
        if (strSize < 0 || strSize > 10000) { // Защита от некорректных данных
            throw std::runtime_error("Invalid string size in file");
        }
        
        std::string element(strSize, '\0');
        file.read(&element[0], strSize);
        
        data[i] = element;
    }
    
    size = newSize;
    file.close();
}

void Array::print() const {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << data[i];
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

std::vector<std::string> Array::getAllData() const {
    return std::vector<std::string>(data.begin(), data.begin() + size);
}

std::string& Array::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const std::string& Array::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}