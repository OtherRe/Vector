#include "Vector.hpp"
#include "myExepctions.hpp"
#include <cassert>
#include <exception>

template <typename T>
Vector<T>::Vector(std::initializer_list<T> &&il)
{
    const size_t size = il.size();
    static_assert(size > 0);
    if(size < _defaultCapacity)
        size = _defaultCapacity;
        
    _array = new T[size];
    _capacity = size;
    _size = size;

    for (auto &elem : il)
    {
        push_back(elem);//emplace_back?
    }
}

/**
 * @brief Deep copy construct a new Vector< T>:: Vector object
 * 
 * @tparam T 
 * @param other other vector of the same type
 */

template <typename T>
Vector<T>::Vector(const Vector<T> &other) : _array(new T[other.size()]), _capacity(other.capacity()), _size(other.size())
{
    static_assert(this != other);
    for (auto &elem : other)
        push_back(elem);
}
template <typename T>
Vector<T>::Vector(Vector<T> &&other) : _array(other._array), _capacity(other.capacity), _size(other.size)
{
    static_assert(this != other);
    delete[] other._array;
    other.capacity = 0;
    other.size = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    static_assert(this != other);

    delete[] _array;
    _array = new T[other.size()];

    _capacity = other.capacity();
    _size = other.size();
    for (auto &elem : other)
        push_back(elem);

    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other)
{
    static_assert(this != other);

    delete[] _array;
    _array = other._array;

    _capacity = other.capacity();
    _size = other.size();

    other._capacity = 0;
    other._size = 0;

    return *this;
}
template <typename T>
T& Vector<T>::at(size_t pos){
    if(pos < 0 || pos >= _size)
        throw std::out_of_range("Position out of bounds");
    
    return _array[pos];

}

// T &back();
// T &front();

// size_t capacity();
// void clear();
// bool empty() const;

// iterator begin();
// iterator end();

// void erase(const_iterator position);
// void erase(const_iterator start, const_iterator end);

// void insert(const_iterator position, const T &val);

// T &operator[](size_t);
// T &operator[](size_t) const;

// size_t size() const;

// void pop_back();
template <typename T>
void Vector<T>::push_back(const T &elem)
{
    throw NotImplementedExepction();
}