#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

#include <iterator>
#include "list_node.hpp"

namespace ft {
// Base Iterator
template <typename T>
class ListIterator
{
    public:
        typedef ListIterator<T> iterator;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        Node<T> *_actual;

    public:
// Canonical Form
        ListIterator(Node<T>* actual = NULL) : _actual(actual) {}
        ListIterator(ListIterator const &other) {*this = other;}
        ~ListIterator() {}

        ListIterator& operator=(ListIterator const &other){
            if (this != &other)
                _actual = other._actual;;
            return (*this);
        }

// Incrementation and Decrementation
        iterator    operator++(int) {
            iterator tmp(*this);
            _actual = _actual->next();
            return tmp;
        }
        iterator&   operator++(){
            _actual = _actual->next();
            return *this;
        }
        iterator    operator--(int) {
            iterator tmp(*this);
            _actual = _actual->previous();
            return tmp;
        }
        iterator    operator--() {
            _actual = _actual->previous();
            return _actual;
        }

// Deference
        reference   operator*() { return _actual->content(); }
        pointer     operator->() { return &(_actual->content()); }

// Compare
        bool        operator==(const iterator &rhs) const {
            return (this->_actual == rhs._actual);
        }
        bool        operator!=(const iterator &rhs) const {
            return (this->_actual != rhs._actual);
        }

        Node<T>* getcNode() const { return (_actual); }
};

// Const Iterator
template<typename T>
class ConstListIterator : public ListIterator<T>
{

    public:
        typedef const T* const_pointer;
        typedef const T& const_reference;
        typedef Node<T>* node;
    
    public:
        ConstListIterator(node newNode = NULL) { this->_actual = newNode; }    
        ConstListIterator(const ListIterator<T>& it){ this->_actual = it.getcNode(); }
        ConstListIterator(ConstListIterator<T> &other){ *this = other; }
        ConstListIterator& operator=(ConstListIterator<T> const &other){
            if (this != &other)
                this->_actual = other._actual;
            return (*this);
        }
        ~ConstListIterator() {}
    
        const_reference operator*() const{
            return (this->_actual->ccontent());
        }
        const_pointer   operator->() const{
            return &(this->_actual->ccontent());
        }
};

//Reverse Iterator
template <typename T>
class ReverseListIterator : public ListIterator<T>
{
    typedef ReverseListIterator<T> reverse;

    public:
        ReverseListIterator(Node<T>* actual = NULL) { this->_actual = actual; }
        ReverseListIterator(ReverseListIterator const &other) {*this = other;}
        ~ReverseListIterator() {}

        reverse& operator=(ReverseListIterator const &other) {
            if (this != &other)
                this->_actual = other._actual;
            return (*this);
        }

        reverse    operator++(int) {
            reverse tmp(*this);
            this->_actual = this->_actual->previous();
            return tmp;
        }
        reverse&   operator++(){
            this->_actual = this->_actual->previous();
            return *this;
        }
        reverse    operator--(int) {
            reverse tmp(*this);
            this->_actual = this->_actual->next();
            return tmp;
        }
        reverse   operator--() {
            this->_actual = this->_actual->next();
            return this->_actual;
        }
};

template<typename T>
class ConstReverseListIterator : public ReverseListIterator<T>
{
    typedef ConstReverseListIterator<T> const_reverse;
    typedef const T* const_pointer;
    typedef const T& const_reference;

    public:
        ConstReverseListIterator(Node<T>* actual = NULL) { this->_actual = actual;}
        ConstReverseListIterator(const ListIterator<T>& it){ this->_actual = it.getcNode(); }        
        ConstReverseListIterator(ConstReverseListIterator const &other) {*this = other;}
        ~ConstReverseListIterator() {}

        const_reverse& operator=(ConstReverseListIterator const &other){
            if (this != &other)
                this->_actual = other._actual;;
            return (*this);
        }
        const_reference operator*() const{
            return (this->_actual->ccontent());
        }
        const_pointer   operator->() const{
            return &(this->_actual->ccontent());
        }
};
}
#endif