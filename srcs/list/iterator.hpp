#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>

template <typename T>
class ListIterator 
    : public std::iterator<std::bidirectional_iterator_tag, T>
{
    typedef ListIterator<T> iterator;
    pointer pos_;

    public:
        ListIterator() : pos_(NULL) {}
        ListIterator(T *v) : pos_(v) {}
        ~ListIterator() {}

        iterator    operator++(int) {
            return pos_++;
        }
        iterator&   operator++(){
            ++pos_; return *this;
        }
        reference   operator*() const {
            return *pos_;
        }
        pointer     operator->() const {
            return pos_;
        }std::list
        iterator    operator+(difference_type v) const {
            return pos_ + v;
        }
        bool        operator==(const iterator &rhs) const {
            return pos_ == rhs.pos_;
        }
        bool        operator!=(const iterator &rhs) const {
            return pos_ != rhs.pos_;
        }

};

#endif