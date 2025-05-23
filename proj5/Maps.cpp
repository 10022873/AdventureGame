#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include "Node.cpp"
using namespace std;

template <typename K, typename V>
class Map {
public:
    /* Constructors/Destructor */
    
    // Name: Map()
    // Description: Default constructs an empty map.
    // Preconditions: None.
    // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
    Map() : m_head(nullptr), m_size(0) {}

    // Name: ~Map()
    // Description: Destroys the map, freeing all nodes.
    // Preconditions: None.
    // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
    ~Map() {
        Clear();
    }

    // Name: Map(const Map& other)
    // Description: Copy constructor; deep copies another map's contents.
    // Preconditions: other must be a valid Map<K,V>.
    // Postconditions: This map contains the same key/value pairs, in order.
    Map(const Map& other) : m_head(nullptr), m_size(0) {
        Node<K,V>* current = other.m_head;
        while(current != nullptr) {
            Insert(current->GetKey(), current->GetValue());
            current = current->GetNext();
        }
    }

    /* Operators */

    // Name: operator=(const Map& other)
    // Description: Assignment operator; clears this map and deep copies other.
    // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
    // Postconditions: This map contains a copy of other's elements.
    Map<K,V>& operator=(const Map& other) {
        if (this != &other) {
            Clear();
            Node<K,V>* current = other.m_head;
            while (current != nullptr) {
                Insert(current->GetKey(), current->GetValue());
                current = current->GetNext();
            }
        }
        return *this;
    }

    /* Accessors */

    // Name: ValueAt(const K& key) const
    // Description: Retrieves a const reference to the value for key.
    // Preconditions: key must exist in the map.
    // Postconditions: Returns reference to the value;
    //                 throws out_of_range if not found.
    const V& ValueAt(const K& key) const {
        Node<K,V>* node = At(key);
        return node->GetValue();
    }

    // Name: At(const K& key) const
    // Description: Returns a pointer to the node for key.
    // Preconditions: key must exist in the map.
    // Postconditions: Returns pointer to the Node<K,V>;
    //                 throws out_of_range if not found.
    Node<K,V>* At(const K& key) const {
        Node<K,V>* current = m_head;
        while (current != nullptr) {
            if (current->GetKey() == key) {
                return current;
            }
            current = current->GetNext();
        }
        throw out_of_range("Key not found");
    }

    // Name: GetSize() const
    // Description: Reports the number of key-value pairs in the map.
    // Preconditions: None.
    // Postconditions: Returns the value of m_size.
    int GetSize() const {
        return m_size;
    }

    // Name: IsEmpty() const
    // Description: Checks whether the map contains no elements.
    // Preconditions: None.
    // Postconditions: Returns true if m_size == 0
    //                 (m_head == nullptr); false otherwise.
    bool IsEmpty() const {
        return m_size == 0;
    }

    /* Mutators */

    // Name: Insert(const K& key, const V& value)
    // Description: Inserts or updates a key → value pair, keeping
    //              nodes ordered by key.
    // Preconditions: key and value are valid; map may be empty.
    // Postconditions: New node inserted at sorted position, or
    //                 existing node's value updated; m_size adjusted.
    void Insert(const K& key, const V& value) {
        Node<K,V>* newNode = new Node<K,V>(key, value);
        
        // Case 1: Empty list
        if (m_head == nullptr) {
            m_head = newNode;
            m_size++;
            return;
        }
        
        // Case 2: New key is smaller than head's key
        if (key < m_head->GetKey()) {
            newNode->SetNext(m_head);
            m_head = newNode;
            m_size++;
            return;
        }
        
        // Case 3: Key already exists at head
        if (key == m_head->GetKey()) {
            m_head->SetValue(value);
            delete newNode;
            return;
        }

        // Case 4: Traverse to find insertion point
        Node<K,V>* current = m_head;
        while (current->GetNext() != nullptr) {
            // Key already exists - update value
            if (key == current->GetNext()->GetKey()) {
                current->GetNext()->SetValue(value);
                delete newNode;
                return;
            }
            // Found insertion point
            if (key < current->GetNext()->GetKey()) {
                newNode->SetNext(current->GetNext());
                current->SetNext(newNode);
                m_size++;
                return;
            }
            current = current->GetNext();
        }

        // Case 5: Add at end of list
        current->SetNext(newNode);
        m_size++;
    }

    // Name: Update(const K& key, const V& value)
    // Description: Changes the value for an existing key.
    // Preconditions: key must exist in the map.
    // Postconditions: Corresponding node's value is set to
    //                 value; throws out_of_range if key not found.
    void Update(const K& key, const V& value) {
        Node<K,V>* node = At(key); // Will throw if key not found
        node->SetValue(value);
    }

    /* Utility Functions */

    // Name: Display() const
    // Description: Prints each key:value pair to cout, one per line.
    // Preconditions: ostream cout is available.
    // Postconditions: Map contents are written to standard output.
    void Display() const {
        Node<K,V>* current = m_head;
        while (current != nullptr) {
            cout << current->GetKey() << ":" << current->GetValue() << endl;
            current = current->GetNext();
        }
    }

    // Name: Clear()
    // Description: Deletes all nodes in the linked list,
    //              freeing their memory and resetting the map.
    // Preconditions: None.
    // Postconditions: All dynamically allocated nodes are deleted;
    //                 m_head is set to nullptr; m_size is reset to 0.
    void Clear() {
        Node<K,V>* current = m_head;
        while (current != nullptr) {
            Node<K,V>* next = current->GetNext();
            delete current;
            current = next;
        }
        m_head = nullptr;
        m_size = 0;
    }

    /* Provided Operator */

    friend ostream& operator<<(ostream& os, const Map<K, V>& map) {
        Node<K,V>* current = map.m_head;
        while (current != nullptr) {
            os << current->GetKey() << ":" << current->GetValue() << endl;
            current = current->GetNext();
        }
        return os;
    }

private:
    Node<K,V>* m_head; // Pointer to the first node in the Map
    int m_size;        // Tracks the size of the Map (number of nodes)
};

#endif
