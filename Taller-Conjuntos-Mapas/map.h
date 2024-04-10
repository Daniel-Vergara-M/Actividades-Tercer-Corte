#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename K, typename V>
struct Pair
{
    K key;
    V value;
    Pair *next;
    Pair() : key(K()), value(V()), next(nullptr){};
    Pair(K key, V value) : key(key), value(value), next(nullptr){};
};

template <typename K, typename V>
class Map
{
private:
    int mapSize;
    int count;
    Pair<K, V> *pairs;

public:
public:
    Map(int size) : mapSize(size), count(0), pairs(new Pair<K, V>()){};
    Map(int size, Pair<K, V> *pairs) : mapSize(size), count(0), pairs(pairs){};

    V get(K key)
    {
        Pair<K, V> *current = this->pairs;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current->value;
            }
            current = current->next;
        }
        cout << "Key not found.\n";
        return V();
    }

    void insert(K key, V value)
    {
        if (this->count == this->mapSize)
        {
            cout << "Map is full.\n";
            return;
        }
        Pair<K, V> *current = this->pairs;
        if (current->key == K())
        {
            current->key = key;
            current->value = value;
            this->count++;
            return;
        }
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new Pair<K, V>(key, value);
        this->count++;
    }

    void remove(K key)
    {
        Pair<K, V> *current = this->pairs;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                this->pairs = current->next;
                this->count--;
                return;
            }
            if (current->next->key == key)
            {
                this->pairs->next = current->next->next;
                this->count--;
                return;
            }
            current = current->next;
        }
        cout << "Key not found.\n";
    }

    bool contains(K key)
    {
        Pair<K, V> *current = this->pairs;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Pair<K, V>* find(K key)
    {
        Pair<K, V> *current = this->pairs;
        Pair<K, V> *previous = nullptr;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current;
            }
            previous = current;
            current = current->next;
        }
        Pair<K, V> *emptyPair = new Pair<K, V>(key, V());
        if (previous == nullptr)
        {
            this->pairs = emptyPair;
        }
        else
        {
            previous->next = emptyPair;
        }
        return emptyPair;
    }

    void print()
    {
        Pair<K, V> *current = this->pairs;
        while (current != nullptr)
        {
            cout << current->key << " : " << current->value << endl;
            current = current->next;
        }
    }

    vector<K> keys()
    {
        Pair<K, V> *current = this->pairs;
        vector<K> mapKeys;
        while (current != nullptr)
        {
            mapKeys.push_back(current->key);
            current = current->next;
        }
        return mapKeys;
    }

    vector<V> values()
    {
        Pair<K, V> *current = this->pairs;
        vector<V> mapValues;
        while (current != nullptr)
        {
            mapValues.push_back(current->value);
            current = current->next;
        }
        return mapValues;
    }

    vector<Pair<K, V>> items()
    {
        Pair<K, V> *current = this->pairs;
        vector<Pair<K, V>> mapItems;
        while (current != nullptr)
        {
            mapItems.push_back(Pair<K, V>(current->key, current->value));
            current = current->next;
        }
        return mapItems;
    }

    bool isEmpty() { return this->count == 0; }

    int size() { return this->count; }

    void clear()
    {
        this->count = 0;
        this->pairs = new Pair<K, V>();
    }
};

template <typename K, typename V>
Map<K, V> merge(Map<K, V> &map1, Map<K, V> &map2)
{
    Map<K, V> mergedMap(map1.size() + map2.size());
    vector<Pair<K, V>> items1 = map1.items();
    vector<Pair<K, V>> items2 = map2.items();

    for (Pair<K, V> &pair : items1)
    {
        mergedMap.insert(pair.key, pair.value);
    }

    for (Pair<K, V> &pair : items2)
    {
        mergedMap.insert(pair.key, pair.value);
    }

    return mergedMap;
}