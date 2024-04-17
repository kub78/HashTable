#include "HashTable.h"

#include <stdexcept>

HashTable::HashTable(size_t size) noexcept : _capacity(size), _filled(0), table(size) {}

HashTable::~HashTable() {
}

void HashTable::insert(const KeyType &key, const ValueType &value) {
    double loadFactor = getLoadFactor();
    if (loadFactor > 0.75) {
        _capacity *= 2;
        std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(_capacity);
        for (auto list = table.begin(); list != table.end(); ++list) {
            for (auto pair  = list->begin(); pair != list->end(); ++pair) {
                size_t index = hash_function(pair->first) % _capacity;
                newTable[index].push_back(*pair);
            }
        }
        table = newTable;
    }
    size_t index = hash_function(key) % _capacity;
    auto &list = table[index];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == key) {
            it->second = value;
            return;
        }
    }
    list.push_back(std::make_pair(key, value));
    ++_filled;
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
 	size_t index = hash_function(key) % _capacity;
	auto &list = table[index];
	for (auto it = list.begin(); it != list.end(); ++it){
		if (it->first == key){
			return true;
		}
	}
	return false;
}

void HashTable::remove(const KeyType &key) {
    size_t index = hash_function(key) % _capacity;
    auto &list = table[index];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == key) {
            list.erase(it);
            --_filled;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key) {
    size_t index = hash_function(key) % _capacity;
    auto &list = table[index];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == key) {
            return it->second;
        }
    }
    list.emplace_back(key, ValueType());
    ++_filled;
    return list.back().second;
}

double HashTable::getLoadFactor() {
    return static_cast<double>(_filled) / _capacity;
}

size_t HashTable::hash_function(const KeyType &key) const {
    size_t hash = 0;
    for (size_t i = 0; i < key.size(); i++) {
        char c = key[i];
        hash = hash * 31 + c;
    }
    return hash;
}