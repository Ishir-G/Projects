#include "Hash.h"
#include "File.h"
#include <vector>
#include <string>
#include <cstdint>

size_t Hash::operator()(const std::string& key) const {
    size_t hash_val = 0;
    size_t prime = 10039;
    for (char c : key) {
        hash_val = hash_val * prime + c;
    }
    return hash_val;
}

template<typename Key>
size_t Hash::operator()(const Key* ptr) const {
    return Hash()((size_t)ptr);
}

size_t Hash::operator()(int key) const {
    size_t hash_val = 0;
    size_t prime = 10039;
    while (key > 0) {
        hash_val = hash_val * prime + ((size_t)key % 10);
        key /= 10;
    }
    return hash_val;
}

template<typename Key, typename Value>
HashMap<Key, Value>::Node::Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::hash_key(const Key& key) const {
    return hasher(key) % bucket_count;
}

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(int size) : bucket_count(size), buckets(size, nullptr) {}

template<typename Key, typename Value>
bool HashMap<Key, Value>::find(const Key& key) const {
    
	int idx = hash_key(key);
    Node* node = buckets[idx];
    
	while (node) {
        if (node->key == key) {
            return true;
        }
        node = node->next;
    }
    
	return false;
}

template<typename Key, typename Value>
Value& HashMap<Key, Value>::operator[](const Key& key) {

    int idx = hash_key(key);
    Node* node = buckets[idx];
    
	while (node) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }

    Node* new_node = new Node(key, Value());
    new_node->next = buckets[idx];
    buckets[idx] = new_node;
    
	return new_node->value;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::erase(const Key& key) {
    
	int idx = hash_key(key);
    Node* node = buckets[idx];
    Node* prev = nullptr;
    
	while (node) {
        if (node->key == key) {
            if (prev) prev->next = node->next;
            else buckets[idx] = node->next;
            delete node;
            return;
        }
        prev = node;
        node = node->next;
    }
	return;
}

template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap() {
    
	for (auto node : buckets) {
        while (node) {
            Node* tmp = node;
            node = node->next;
            delete tmp;
        }
    }
}

template<typename Key, typename Value>
std::vector<Value> HashMap<Key, Value>::return_values() {

    std::vector<Value> values;
    
	for (auto node : buckets) {
        while (node) {
            values.push_back(node->value);
            node = node->next;
        }
    }
    
	return values;
}

template class HashMap<std::string, int>;
template class HashMap<std::string, File*>;
template class HashMap<File*, int>;
template class HashMap<int, Version*>;
