#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class Point>
string to_string(const Point& point)
{
    return "(" + to_string(point.x()) + ", " + to_string(point.y()) + ")";
}

template <typename K, typename V>
struct Pair
{
    K key;
    V value;
    Pair *next;
    Pair *prev;
    Pair() : key(K()), value(V()), next(nullptr), prev(nullptr) {}
    Pair(K key, V value) : key(key), value(value), next(nullptr), prev(nullptr) {}
    ~Pair() { delete next; }
    friend ostream &operator<<(ostream &os, const Pair<K, V> &pair)
    {
        return os << pair.key << " : " << pair.value;
    }

    string toString() { return to_string(key) + " : " + to_string(value); }
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
    Map() : mapSize(0), count(0), pairs(new Pair<K, V>()){};
    Map(int size) : mapSize(size), count(0), pairs(new Pair<K, V>()){};
    Map(int size, Pair<K, V> *pairs) : mapSize(size), count(0), pairs(pairs){};
    Map(const Map &other)
    {
        this->count = other.count;
        this->pairs = new Pair<K, V>();
        Pair<K, V> *current = other.pairs;
        while (current != nullptr)
        {
            this->insert(current->key, current->value);
            current = current->next;
        }
    }

    int size() { return this->count; }
    int dataSize() { return this->mapSize; }
    void setSize(int size) { this->mapSize = size; }

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
        cout << "\"Key not found.\n\"";
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
        while (current != nullptr)
        {
            if (current->key == key)
            {
                current->value = value;
                return;
            }
            if (current->next == nullptr)
            {
                break;
            }
            current = current->next;
        }
        current->next = new Pair<K, V>(key, value);
        this->count++;
    }

    void insertAtBeginning(K key, V value)
    {
        Pair<K, V> *newPair = new Pair<K, V>(key, value);
        newPair->next = this->pairs;
        if (this->pairs != nullptr)
        {
            this->pairs->prev = newPair;
        }
        this->pairs = newPair;
        this->count++;
    }

    void remove(K key)

    {
        Pair<K, V> *current = this->pairs;
        Pair<K, V> *previous = nullptr;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (previous == nullptr)
                {
                    this->pairs = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                current->next = nullptr;
                delete current;
                this->count--;
                return;
            }
            previous = current;
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

    Pair<K, V> *find(K key)
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

    string toString()
    {
        string mapString = "{\n ";
        vector<Pair<K, V>> items = this->items();
        for (int i = 0; i < static_cast<int>(items.size()); i++)
        {
            Pair<K, V> &pair = items[i];
            mapString += pair.toString();
            if (i != static_cast<int>(items.size()) - 1)
            {
                mapString += ",\n ";
            }
        }
        mapString += "\n}";
        return mapString;
    }

    void print()
    {
        cout << this->toString() << endl;
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

    void clear()
    {
        this->count = 0;
        this->pairs = new Pair<K, V>();
    }

    Map<K, V> intersection(Map<K, V> &map)
    {
        Map<K, V> intersectionMap(this->size() + map.size());
        vector<Pair<K, V>> items = this->items();
        for (Pair<K, V> &pair : items)
        {
            if (map.contains(pair.key))
            {
                intersectionMap.insert(pair.key, pair.value);
            }
        }
        return intersectionMap;
    }

    Map<K, V> diff(Map<K, V> &map)
    {
        Map<K, V> diffMap(this->size() + map.size());
        vector<Pair<K, V>> items = this->items();
        for (Pair<K, V> &pair : items)
        {
            if (!map.contains(pair.key))
            {
                diffMap.insert(pair.key, pair.value);
            }
        }
        return diffMap;
    }

    Map<K, V> merge(Map<K, V> &map)
    {
        Map<K, V> mergedMap(this->size() + map.size());
        vector<Pair<K, V>> items = this->items();
        for (Pair<K, V> &pair : items)
        {
            mergedMap.insert(pair.key, pair.value);
        }
        items = map.items();
        for (Pair<K, V> &pair : items)
        {
            mergedMap.insert(pair.key, pair.value);
        }
        return mergedMap;
    }

    Map<K, V> copy()
    {
        Map<K, V> copiedMap = Map<K, V>(this->size());
        vector<Pair<K, V>> items = this->items();
        for (Pair<K, V> &pair : items)
        {
            copiedMap.insert(pair.key, pair.value);
        }
        return copiedMap;
    }

    Map<K, V> reverse()
    {
        Map<K, V> reversedMap = Map<K, V>(this->size() - 1);
        vector<Pair<K, V>> items = this->items();
        for (Pair<K, V> &pair : items)
        {
            reversedMap.insertAtBeginning(pair.key, pair.value);
        }
        return reversedMap;
    }

    Map<V, K> invert()
    {
        int k = 0;
        Map<V, K> invertedMap(this->size());
        vector<Pair<K, V>> items = this->items();
        for (Pair<K, V> pair : items)
        {
            if (k == this->size() - 1)
            {
                invertedMap.insert(pair.value, pair.key);
                k++;
                continue;
            }
            else
            {
                invertedMap.insertAtBeginning(pair.value, pair.key);
            }
        }
        return invertedMap.copy();
    }

    Map<K, V> operator+(Map<K, V> &map)
    {
        return this->merge(map);
    }

    Map<K, V> operator-(Map<K, V> &map)
    {
        return this->diff(map);
    }

    Map<K, V> operator*(Map<K, V> &map)
    {
        return this->intersection(map);
    }

    Map<K, V> operator!()
    {
        return this->reverse();
    }

    Map<K, V> operator~()
    {
        return this->invert();
    }

    Map<K, V> &operator=(Map<K, V> &map)
    {
        this->clear();
        vector<Pair<K, V>> items = map.items();
        for (Pair<K, V> &pair : items)
        {
            this->insert(pair.key, pair.value);
        }
        return *this;
    }

    Map<K, V> &operator+=(Map<K, V> &map)
    {
        vector<Pair<K, V>> items = map.items();
        for (Pair<K, V> &pair : items)
        {
            this->insert(pair.key, pair.value);
        }
        return *this;
    }

    Map<K, V> &operator-=(Map<K, V> &map)
    {
        vector<Pair<K, V>> items = map.items();
        for (Pair<K, V> &pair : items)
        {
            this->remove(pair.key);
        }
        return *this;
    }

    Map<K, V> &operator*=(Map<K, V> &map)
    {
        Map<K, V> intersectionMap = this->intersection(map);
        this->clear();
        vector<Pair<K, V>> items = intersectionMap.items();
        for (Pair<K, V> &pair : items)
        {
            this->insert(pair.key, pair.value);
        }
        return *this;
    }

    V operator[](K key)
    {
        return this->get(key);
    }

    void operator[]= (Pair<K, V> pair)
    {
        this->insert(pair.key, pair.value);
    }
    
    bool operator==(Map<K, V> &map)
    {
        if (this->size() != map.size())
        {
            return false;
        }

        vector<Pair<K, V>> items = this->items();
        for (Pair<K, V> &pair : items)
        {
            if (!map.contains(pair.key) || map.get(pair.key) != pair.value)
            {
                return false;
            }
        }
        return true;
    }

    void operator delete[](void *p)
    {
        delete p;
    }

    bool empty() { return this->count == 0; }
};
