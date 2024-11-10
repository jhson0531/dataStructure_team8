#include <iostream>
#include <string>

using namespace std;

const int BUCKET_SIZE = 10;

// Linked list Node
class Node {
public:
    int key;
    string value;
    Node* next;

    Node(int k, string v) : key(k), value(v), next(nullptr) {}
};

// HashTable
class HashTable {
private:
    Node* table[BUCKET_SIZE];

    // Hash Function : Division Method
    int hashFunction(int key) {
        return key % BUCKET_SIZE;
    }

public:
    // initializing table
    HashTable() {
        for (int i = 0; i < BUCKET_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // insert
    void insert(int key, string value) {
        int hashIndex = hashFunction(key);
        Node* newNode = new Node(key, value);

        if (table[hashIndex] == nullptr) {
            table[hashIndex] = newNode;
        }
        else {
            newNode->next = table[hashIndex];
            table[hashIndex] = newNode;
        }
    }

    // search
    string search(int key) {
        int hashIndex = hashFunction(key);
        Node* current = table[hashIndex];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "Key not found";
    }

    // delete
    void remove(int key) {
        int hashIndex = hashFunction(key);
        Node* current = table[hashIndex];
        Node* previous = nullptr;

        while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Key not found" << endl;
            return;
        }

        if (previous == nullptr) {
            table[hashIndex] = current->next;
        }
        else {
            previous->next = current->next;
        }

        delete current;
        cout << "Key " << key << " removed" << endl;
    }

    // print table
    void display() {
        for (int i = 0; i < BUCKET_SIZE; i++) {
            cout << "Index " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }

    // node delete
    ~HashTable() {
        for (int i = 0; i < BUCKET_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }
};

int main() {
    HashTable hashTable;
    hashTable.insert(1, "박석환");
    hashTable.insert(11, "손정훈");
    hashTable.insert(21, "임승현");
    hashTable.insert(2, "정은택");
    hashTable.insert(3, "황지웅");
    hashTable.insert(7, "이순원");
    hashTable.insert(8, "박준하");

    hashTable.display();
    cout << endl;
    cout << "Search key 11: " << hashTable.search(11) << endl;
    cout << endl;
    hashTable.remove(11);
    cout << endl;
    hashTable.display();

    return 0;
}