#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ForwardIterator.hpp"

// namespace
// {

template <typename T>
class Vector
{
    typedef ForwardIterator<T> iterator;
    typedef ForwardIterator<const T> const_iterator;

private:
    T* _array;
    int _size;
    int _capacity;
    int _defaultCapacity = 8;

public:
    explicit Vector(): 
        _array(new T[_defaultCapacity]), _capacity(_defaultCapacity), _size(0) {}
    
    explicit Vector(int);
    Vector(std::initializer_list<T>&&);
    Vector(const Vector& other);
    Vector(Vector&& other);
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    ~Vector() {delete _array;}

    T& at(size_t);

    T& back();
    T& front();

    size_t capacity();
    void clear();
    bool empty() const;

    iterator begin();
    iterator end();

    void erase(const_iterator position);
    void erase(const_iterator start, const_iterator end);

    void insert(const_iterator position, const T& val);

    T& operator[](size_t);
    T& operator[](size_t) const;

    size_t size() const;

    void pop_back();
    void push_back(const T&);

};

// }; // namespace

#endif