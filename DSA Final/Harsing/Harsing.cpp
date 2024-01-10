#include <iostream>
#include <vector>
#include <list>
#include <functional>

using namespace std;

const int TABLE_SIZE = 10;

typedef pair<int, int> KeyValue;

size_t hashFunction(int key) {
    hash<int> hasher;
    return hasher(key) % TABLE_SIZE;
}

void insert_linear_probing(vector<list<KeyValue>>& table, int key, int value) {
    size_t index = hashFunction(key);
    size_t original_index = index;

    while (!table[index].empty() && table[index].front().first != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) {
            cout << "Hash table is full. Unable to insert key: " << key << endl;
            return;
        }
    }

    table[index].push_back(make_pair(key, value));
}

int get_linear_probing(const vector<list<KeyValue>>& table, int key) {
    size_t index = hashFunction(key);
    size_t original_index = index;

    while (!table[index].empty()) {
        if (table[index].front().first == key) {
            return table[index].front().second;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) {
            break;
        }
    }

    return -1;
}

void insert_quadratic_probing(vector<list<KeyValue>>& table, int key, int value) {
    size_t index = hashFunction(key);
    size_t original_index = index;
    size_t i = 1;

    while (!table[index].empty() && table[index].front().first != key) {
        index = (original_index + i * i) % TABLE_SIZE;
        i++;
        if (index == original_index) {
            cout << "Hash table is full. Unable to insert key: " << key << endl;
            return;
        }
    }

    table[index].push_back(make_pair(key, value));
}

int get_quadratic_probing(const vector<list<KeyValue>>& table, int key) {
    size_t index = hashFunction(key);
    size_t original_index = index;
    size_t i = 1;

    while (!table[index].empty()) {
        if (table[index].front().first == key) {
            return table[index].front().second;
        }
        index = (original_index + i * i) % TABLE_SIZE;
        i++;
        if (index == original_index) {
            break;
        }
    }

    return -1;
}

void insert_double_hashing(vector<list<KeyValue>>& table, int key, int value) {
    size_t index = hashFunction(key);
    size_t original_index = index;
    size_t step = 7 - (key % 7);

    while (!table[index].empty() && table[index].front().first != key) {
        index = (index + step) % TABLE_SIZE;
        if (index == original_index) {
            cout << "Hash table is full. Unable to insert key: " << key << endl;
            return;
        }
    }

    table[index].push_back(make_pair(key, value));
}

int get_double_hashing(const vector<list<KeyValue>>& table, int key) {
    size_t index = hashFunction(key);
    size_t original_index = index;
    size_t step = 7 - (key % 7);

    while (!table[index].empty()) {
        if (table[index].front().first == key) {
            return table[index].front().second;
        }
        index = (index + step) % TABLE_SIZE;
        if (index == original_index) {
            break;
        }
    }

    return -1;
}

int main() {
    vector<list<KeyValue>> linearProbingTable(TABLE_SIZE);
    vector<list<KeyValue>> quadraticProbingTable(TABLE_SIZE);
    vector<list<KeyValue>> doubleHashingTable(TABLE_SIZE);

    insert_linear_probing(linearProbingTable, 42, 100);
    insert_linear_probing(linearProbingTable, 7, 200);
    insert_linear_probing(linearProbingTable, 25, 300);

    cout << "Linear Probing: " << endl;
    cout << "Value for key 42: " << get_linear_probing(linearProbingTable, 42) << endl;
    cout << "Value for key 7: " << get_linear_probing(linearProbingTable, 7) << endl;
    cout << "Value for key 25: " << get_linear_probing(linearProbingTable, 25) << endl;

    insert_quadratic_probing(quadraticProbingTable, 42, 100);
    insert_quadratic_probing(quadraticProbingTable, 7, 200);
    insert_quadratic_probing(quadraticProbingTable, 25, 300);

    cout << "Quadratic Probing: " << endl;
    cout << "Value for key 42: " << get_quadratic_probing(quadraticProbingTable, 42) << endl;
    cout << "Value for key 7: " << get_quadratic_probing(quadraticProbingTable, 7) << endl;
    cout << "Value for key 25: " << get_quadratic_probing(quadraticProbingTable, 25) << endl;

    insert_double_hashing(doubleHashingTable, 42, 100);
    insert_double_hashing(doubleHashingTable, 7, 200);
    insert_double_hashing(doubleHashingTable, 25, 300);

    cout << "Double Hashing: " << endl;
    cout << "Value for key 42: " << get_double_hashing(doubleHashingTable, 42) << endl;
    cout << "Value for key 7: " << get_double_hashing(doubleHashingTable, 7) << endl;
    cout << "Value for key 25: " << get_double_hashing(doubleHashingTable, 25) << endl;

    return 0;
}