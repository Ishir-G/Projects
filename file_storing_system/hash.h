#ifndef HASH_H
#define HASH_H

#include <vector>
#include <string>

struct Hash {
    size_t operator()(const std::string& key) const;

    template<typename Key>
    size_t operator()(const Key* ptr) const;

    size_t operator()(int key) const;
};

template<typename Key, typename Value>
class HashMap {
    struct Node {
        Key key;
        Value value;
        Node* next;
        Node(const Key& k, const Value& v);
    };

    std::vector<Node*> buckets;
    int bucket_count;

    size_t hash_key(const Key& key) const;
    Hash hasher;

public:
    HashMap(int size = 101);
    bool find(const Key& key) const;
    Value& operator[](const Key& key);
    void erase(const Key& key);
    std::vector<Value> return_values();
    ~HashMap();
};

#endif
