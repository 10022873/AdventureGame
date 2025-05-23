#include <iostream>
using namespace std;

template<typename K, typename V>
class Node {
public:
    // Constructor
    Node(const K& key, const V& value, Node<K,V>* next = nullptr) : 
        m_key(key), m_value(value), m_next(next) {}

    // Getter for key
    const K& GetKey() const {
        return m_key;
    }

    // Getter for value
    const V& GetValue() const {
        return m_value;
    }

    // Getter for next node pointer
    Node<K,V>* GetNext() const {
        return m_next;
    }

    // Setter for value
    void SetValue(const V& value) {
        m_value = value;
    }

    // Setter for next node pointer
    void SetNext(Node<K,V>* next) {
        m_next = next;
    }
