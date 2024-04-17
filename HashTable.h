#pragma once
#include <vector>
#include <list>
#include <string>
#include <utility>

using KeyType = std::string;
using ValueType = double;

class HashTable 
{
public:
    explicit HashTable(size_t size = 100) noexcept;
    ~HashTable();
    void insert(const KeyType &key, const ValueType &value);
    bool find(const KeyType &key, ValueType &value) const;
    void remove(const KeyType &key);
    ValueType& operator[](const KeyType &key);
    double getLoadFactor();

private:
    int32_t _capacity;
    int32_t _filled;

    std::vector<std::list<std::pair<KeyType, ValueType>>> table;
    size_t hash_function(const KeyType &key) const; 
};