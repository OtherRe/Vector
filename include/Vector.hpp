#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace aisdi
{

template <typename Type>
class Vector
{
public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type *;
  using reference = Type &;
  using const_pointer = const Type *;
  using const_reference = const Type &;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  Vector();
  Vector(std::initializer_list<Type> l);
  Vector(const Vector &other);
  Vector(Vector &&other);
  ~Vector()
  {
    if (_array)
      delete[] _array;
  }

  Vector &operator=(const Vector &other);
  Vector &operator=(Vector &&other);
  Type &operator[](const size_type index);

  bool isEmpty() const { return _size == 0; }
  size_type getSize() const { return _size; }
  size_type getCapacity() const { return _capacity; }

  void append(const Type &item);
  void prepend(const Type &item);
  void insert(const const_iterator &insertPosition, const Type &item);

  Type popFirst();
  Type popLast();

  void erase(const const_iterator &possition);
  void erase(const const_iterator &firstIncluded, const const_iterator &lastExcluded);

  // iterator begin()              {return _size > 0 ? iterator(&(_array[0])) : iterator();}
  // iterator end()                {return _size > 0 ? iterator(&_array[_size]) : iterator();}
  // const_iterator cbegin() const {return _size > 0 ? const_iterator(&_array[0]) : const_iterator();}
  // const_iterator cend() const   {return _size > 0 ? const_iterator(&_array[_size]) : const_iterator(); }
  iterator begin() { return iterator(&(_array[0]), 0, this); }
  iterator end() { return iterator(&_array[_size], _size, this); }
  const_iterator cbegin() const { return const_iterator(&_array[0], 0, this); }
  const_iterator cend() const { return const_iterator(&_array[_size], _size, this); }
  const_iterator begin() const { return cbegin(); }
  const_iterator end() const { return cend(); }

private:
  Type *_array;
  size_type _capacity;
  size_type _size;

  static const size_type _defaultCapacity = 8;

  void changeCapacityBy(float);
  void moveElementsRight(int from, int jump = 1);
  void moveElementsLeft(int from, int jump = 1);
};

template <typename Type>
class Vector<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;

  explicit ConstIterator() : _elem(nullptr) {}
  explicit ConstIterator(const_pointer elem, size_type pos, const Vector<Type> *v) : _elem(elem), _position(pos), vec(v) {}
  ConstIterator(const ConstIterator &other) : _elem(other._elem), _position(other._position), vec(other.vec) {}

  reference operator*() const
  {
    if (_position >= vec->getSize())
      throw std::out_of_range("Dereferencing end iterator");
    else if (_elem != nullptr)
      return *_elem;
    else
    {
      throw std::runtime_error("Referencin nullptr");
    }
  }

  ConstIterator &operator++()
  {
    if (++_position > vec->getSize())
      throw std::out_of_range("Incrementign end iterator");
    _elem++;
    return *this;
  }

  ConstIterator operator++(int)
  {

    if (++_position > vec->getSize())
      throw std::out_of_range("Incrementign end iterator");

    auto temp = ConstIterator(_elem, _position - 1, vec);

    _elem++;
    return temp;
  }

  ConstIterator &operator--()
  {
    if (_position == 0)
      throw std::out_of_range("Decrementing begin iterator");

    --_elem;
    --_position;
    return *this;
  }

  ConstIterator operator--(int)
  {
    if (_position == 0)
      throw std::out_of_range("Decrementing begin iterator");

    auto temp = ConstIterator(_elem, --_position, vec);
    _elem--;
    return temp;
  }

  ConstIterator operator+(difference_type d) const
  {
    if (_position + d > vec->getSize())
      throw std::out_of_range("Adding to iterator passed the end");

    return ConstIterator(_elem + d, _position + d, vec);
  }

  ConstIterator operator-(difference_type d) const
  {
    if (_position - d < 0)
      throw std::out_of_range("Substracting iterator pass zero");

    return ConstIterator(_elem - d, _position - d, vec);
  }

  bool operator==(const ConstIterator &other) const
  {
    return _elem == other._elem; ///POINTER OR VALUE EQUAILTY
  }

  bool operator!=(const ConstIterator &other) const
  {
    return !(*this == other);
  }

protected:
  size_type _position;
  const_pointer _elem;
  const Vector<Type> *vec;
};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;
  using size_type = typename Vector::size_type;

  explicit Iterator() : ConstIterator()
  {
  }

  Iterator(pointer elem, size_type pos, Vector<Type> *v) : ConstIterator(elem, pos, v) {}

  Iterator(const ConstIterator &other)
      : ConstIterator(other)
  {
  }

  Iterator &operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator &operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

} // namespace aisdi

#endif // AISDI_LINEAR_VECTOR_H
