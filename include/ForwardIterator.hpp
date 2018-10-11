#ifndef FORWARD_ITERATOR_HPP
#define FORWARD_ITERATOR_HPP

#include <iterator>

template <typename T>
class ForwardIterator : public std::iterator<std::input_iterator_tag,
                                             T, T, T *, T &>
{
    T *itr;

  public:
    ForwardIterator() : itr(nullptr) {}
    explicit ForwardIterator(T *el) : itr(el) {}

    void swap(ForwardIterator& other);

    ForwardIterator &operator++();
    ForwardIterator operator++(int);
    template<typename OtherType>
    bool operator==(const ForwardIterator<OtherType>& rhs) const {return itr == rhs.itr;};

    template<typename OtherType>
    bool operator!=(const ForwardIterator<OtherType>& rhs) const {return itr != rhs.itr;};

    T& operator-> () const;
    T& operator*  () const;
};

#endif