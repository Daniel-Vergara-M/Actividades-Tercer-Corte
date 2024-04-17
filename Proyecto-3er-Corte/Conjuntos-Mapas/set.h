#include <iostream>

using namespace std;

template <typename T>
struct Pair
{
    T first;
    T second;
    Pair() : first(T()), second(T()) {}
    Pair(T first, T second) : first(first), second(second) {}

    bool operator<(const Pair &other) const
    {
        if (first < other.first)
            return true;
        if (first > other.first)
            return false;
        return second < other.second;
    }

    bool operator>(const Pair &other) const
    {
        if (first > other.first)
            return true;
        if (first < other.first)
            return false;
        return second > other.second;
    }

    bool operator<=(const Pair &other) const
    {
        if (first < other.first)
            return true;
        if (first > other.first)
            return false;
        return second <= other.second;
    }

    bool operator>=(const Pair &other) const
    {
        if (first > other.first)
            return true;
        if (first < other.first)
            return false;
        return second >= other.second;
    }

    bool operator==(const Pair &other) const
    {
        return first == other.first && second == other.second;
    }
};

template <typename T>
class Set
{
private:
    int capacity;
    int size;
    T *data;

public:
    Set<T>() : capacity(1), size(0), data(new T[1]) {}
    Set<T>(int capacity) : capacity(capacity), size(0), data(new T[capacity]) {}
    Set<T>(const Set<T> &other) : capacity(other.capacity), size(other.size), data(new T[other.capacity])
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    ~Set<T>()
    {
        delete[] data;
    }

    void insert(const T &value)
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == value)
            {
                return;
            }
        }

        int pos = 0;

        while (pos < size && data[pos] < value)
        {
            pos++;
        }

        if (size == capacity)
        {
            T *temp = new T[2 * capacity];
            for (int i = 0; i < size; i++)
            {
                temp[i] = data[i];
            }
            delete[] data;
            capacity *= 2;
            data = temp;
        }

        for (int i = size; i > pos; i--)
        {
            data[i] = data[i - 1];
        }

        data[pos] = value;
        size++;
    }

    void erase(const T &value)
    {
        int index = -1;
        for (int i = 0; i < size; i++)
        {
            if (data[i] == value)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < size - 1; i++)
            {
                data[i] = data[i + 1];
            }
            size--;
        }
    }

    void clear()
    {
        size = 0;
    }

    bool empty() const
    {
        return size == 0;
    }

    bool contains(const T &value) const
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    int length() const
    {
        return size;
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    T *begin()
    {
        return data;
    }

    T *end()
    {
        return data + size;
    }

    Set<T> &operator=(const Set<T> &other)
    {
        if (this != &other)
        {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Set<T> operator+(const Set<T> &other) const
    {
        Set<T> result(capacity + other.capacity);
        for (int i = 0; i < size; i++)
        {
            result.insert(data[i]);
        }
        for (int i = 0; i < other.size; i++)
        {
            result.insert(other.data[i]);
        }
        return result;
    }

    Set<T> setUnion(const Set<T> &other) const
    {
        return *this + other;
    }

    Set<T> operator-(const Set<T> &other) const
    {
        Set<T> result(capacity);
        for (int i = 0; i < size; i++)
        {
            if (!other.contains(data[i]))
            {
                result.insert(data[i]);
            }
        }
        return result;
    }

    Set<T> difference(const Set<T> &other) const
    {
        return *this - other;
    }

    Set<T> operator*(const Set<T> &other) const
    {
        Set<T> result(capacity);
        for (int i = 0; i < size; i++)
        {
            if (other.contains(data[i]))
            {
                result.insert(data[i]);
            }
        }
        return result;
    }

    Set<T> intersection(const Set<T> &other) const
    {
        return *this * other;
    }

    Set<T> operator/(const Set<T> &other) const
    {
        Set<T> result(capacity);
        for (int i = 0; i < size; i++)
        {
            if (!other.contains(data[i]))
            {
                result.insert(data[i]);
            }
        }
        return result;
    }

    Set<T> symmetric_difference(const Set<T> &other) const
    {
        return (*this - other) + (other - *this);
    }

    Set<T> &operator+=(const Set<T> &other)
    {
        *this = *this + other;
        return *this;
    }

    Set<T> &operator-=(const Set<T> &other)
    {
        *this = *this - other;
        return *this;
    }

    Set<T> &operator*=(const Set<T> &other)
    {
        *this = *this * other;
        return *this;
    }

    Set<T> &operator/=(const Set<T> &other)
    {
        *this = *this / other;
        return *this;
    }

    bool operator==(const Set<T> &other) const
    {
        if (size != other.size)
        {
            return false;
        }
        for (int i = 0; i < size; i++)
        {
            bool found = false;
            for (int j = 0; j < other.size; j++)
            {
                if (data[i] == other.data[j])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                return false;
            }
        }
        return true;
    }

    Set<Pair<T>> sorted_pairs(const Set<T> &s2)
    {
        Set<Pair<T>> result;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < s2.size; j++)
            {
                if (data[i] == T() || s2.data[j] == T())
                {
                    continue;
                }
                result.insert(Pair(data[i], s2.data[j]));
            }
        }
        return result;
    }

    Set<Pair<T>> operator^(Set<T> &other) const
    {
        return sorted_pairs(other);
    }

    bool operator<(const Set<T> &other) const
    {
        return size < other.size;
    }

    bool operator>(const Set<T> &other) const
    {
        return size > other.size;
    }

    bool operator<=(const Set<T> &other) const
    {
        return size <= other.size;
    }

    bool operator>=(const Set<T> &other) const
    {
        return size >= other.size;
    }

    bool operator!=(const Set<T> &other) const
    {
        return !(*this == other);
    }
};