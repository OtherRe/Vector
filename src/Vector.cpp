#include "../include/Vector.hpp"
#include <cassert>
#include <stdexcept>
#include <iostream>
namespace aisdi
{

template <typename T>
Vector<T>::Vector() : _array(new T[_defaultCapacity]), _capacity(_defaultCapacity), _size(0) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> il) : _size(0)
{
    size_t size = il.size();
    _array = new T[size];
    _capacity = size;

    for (auto &elem : il)
    {
        append(elem); //&& somehow(rvalue move)?
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other) : _array(new T[other._size]), _capacity(other._capacity), _size(0)
{
    for (const auto &elem : other)
        append(elem);
}
template <typename T>
Vector<T>::Vector(Vector<T> &&other) : _array(other._array), _capacity(other._capacity), _size(other._size)
{
    other._array = nullptr;
    other._capacity = 0;
    other._size = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (this == &other)
        return *this;

    _capacity = other.getCapacity();

    delete[] _array;
    _array = new T[_capacity];
    _size = 0;

    for (auto &elem : other)
        append(elem);

    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other)
{
    if (this == &other)
        return *this;

    delete[] _array;

    _array = other._array;
    _capacity = other._capacity;
    _size = other._size;

    other._array = nullptr;

    return *this;
}
template <typename T>
T &Vector<T>::operator[](const size_type index)
{
    if (_array == nullptr || index < 0 || index >= _size)
        throw std::out_of_range("Index out of range");

    return _array[index];
}

template <typename T>
void Vector<T>::append(const T &item)
{
    if (_size == _capacity)
        changeCapacityBy(2);

    _array[_size++] = item;
}

template <typename T>
void Vector<T>::prepend(const T &item)
{
    if (_size == _capacity)
        changeCapacityBy(2);

    moveElementsRight(0);

    _array[0] = item;
    ++_size;
}

template <typename T>
void Vector<T>::insert(const const_iterator &insertPosition, const T &item)
{
    size_type position;

    //cannot dereference end() iterator
    position = insertPosition == end() ? _size : &(*insertPosition) - &(*begin());

    if (_size == _capacity)
        changeCapacityBy(2);

    moveElementsRight(position);
    _array[position] = item;
    ++_size;
}

template <typename T>
T Vector<T>::popFirst()
{
    if (_size == 0)
        throw std::length_error("Popped empty vector");

    T temp = _array[0];
    moveElementsLeft(1);
    --_size;

    //to get constant/linear amortized time of popping elements
    //we reduce when the size is quarter of capacity instead of half
    if (_capacity > _defaultCapacity && _size < _capacity / 4)
        changeCapacityBy(1 / 2);

    return temp;
}

template <typename T>
T Vector<T>::popLast()
{
    if (_size == 0)
        throw std::length_error("Popped empty vector");

    if (_capacity > _defaultCapacity && _size < _capacity / 4)
        changeCapacityBy(1 / 2);

    return _array[--_size];
}
template <typename T>
void Vector<T>::erase(const const_iterator &possition)
{
    if (_size == 0)
        throw std::out_of_range("Erasing empty vector");

    size_type position = &(*possition) - &(*begin());
    moveElementsLeft(position + 1);
    --_size;

    if (_size < _capacity / 4 && _capacity > 8)
        changeCapacityBy(1 / 2);
}

template <typename T>
void Vector<T>::erase(const const_iterator &firstIncluded, const const_iterator &lastExcluded)
{

    if (firstIncluded == lastExcluded)
    {
        //?????
        return;
    }

    size_type position = &(*firstIncluded) - &(*begin());

    int nElements = lastExcluded == end() ? _size - position : &(*lastExcluded) - &(*firstIncluded);
    if (_size < nElements)
        throw std::out_of_range("Not enough elments");

    moveElementsLeft(position + nElements, nElements);

    _size -= nElements;
}

////////////////////////////////////////////////////////////////////
/////PRIVATE METHODS/////////
///////////////////////////////////////////////////////////////////

/**
 * @brief changes capacity of dynamically allocated array and copies
 *        elements from old array to new one and deallocates old one. 
 *        New capacity is (old_capacity) * share
 * 
 * @tparam T 
 * @param share factor we want to enlarge(share > 1) or decrease(share < 1)
 *              capacity
 */
template <typename T>
void Vector<T>::changeCapacityBy(float share)
{
    assert(share > 0);
    _capacity = static_cast<int>(_capacity * share); // new capacity
    T *newArray = new T[_capacity];
    for (size_type i = 0; i < _size; i++)
        newArray[i] = _array[i];

    delete[] _array;
    _array = newArray;
}

/**
 * @brief moves elements in the array to the right by 'jump' elements 
 *        using simple shift. Starts at position from and ends at the end
 *        moveElementsRight([1,2,3,4,5], from = 1) --> [1, 2, 2, 3, 4]
 *        moveElementsRight([1,2,3,4,5], from = 1, jump = 2) --> [1, 2, 3, 2, 3]
 * 
 * @tparam T 
 * @param from position in the array we want to start shifting
 * @param jump number of elements we want to move every element
 */
template <typename T>
void Vector<T>::moveElementsRight(int from, int jump)
{
    int to = _size - 1;

    assert(from >= 0);
    for (int i = to; i >= from; --i)
    {
        _array[i + jump] = _array[i];
    }
}

/**
 * @brief moves elements in the array to the left by 'jump' elements 
 *        using simple shift. Starts at position from and ends at the end
 *        moveElementsRight([1,2,3,4,5], from = 1) --> [2, 3, 4, 5, 5]
 *        moveElementsRight([1,2,3,4,5], from = 2, jump = 2) --> [3, 4, 5, 4, 5]
 * 
 * @tparam T 
 * @param from position in the array we want to start shifting
 * @param jump number of elements we want to move every element
 */
template <typename T>
void Vector<T>::moveElementsLeft(int from, int jump)
{
    int to = _size - 1;

    assert(from - jump >= 0);
    for (int i = from; i <= to; ++i)
        _array[i - jump] = _array[i];
}

} // namespace aisdi