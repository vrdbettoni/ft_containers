#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include "../utils.hpp"
#include <iostream>
namespace ft {
template <class T, bool is_const>
class VectorIterator
{
    public:
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef typename choose<is_const, const T*, T*>::type pointer;
        typedef typename choose<is_const, const T&, T&>::type reference;
        typedef T value_type;
    
    private:
        typedef VectorIterator<T, is_const> self_type;

    protected:
        pointer _actual;

    public:
// Canonical Form
        VectorIterator(pointer actual = NULL) : _actual(actual) {}
        VectorIterator(const VectorIterator<T, false> &other) : _actual(other.getActual()) {}
        VectorIterator& operator=(const self_type &other){
            if (this != &other)
                _actual = other.getActual();
            return *this;
        }
        ~VectorIterator() {}

// Basics Operators
        reference operator*() { return *_actual;}
        pointer   operator->() { return _actual;}

        self_type& operator++(){
            ++_actual;
            return *this;
        }
        self_type operator++(int){
            self_type tmp(*this);
            ++_actual;
            return tmp;
        }
        self_type& operator--(){
            --_actual;
            return *this;
        }
        self_type operator--(int){
            self_type tmp(*this);
            --_actual;
            return tmp;
        }

        bool operator==(const self_type &lhs){
            return this->_actual == lhs._actual;
        }
        bool operator!=(const self_type &lhs){
            return !(*this == lhs);
        }
// Random Operators
        self_type operator+(difference_type n){
            self_type tmp(*this);
            return tmp += n;
        }

        self_type operator-(difference_type n){
            self_type tmp(*this);
            return tmp -= n;
        }

        self_type operator-=(difference_type n){
            return *this - n; 
        }

        self_type operator+=(difference_type n){
            return *this + n;
        }

//Getters
        pointer getActual() const {
            return _actual;
        }
};

template<class T, bool is_const>
class ReverseVectorIterator : public VectorIterator<T, is_const>
{
    
    public:
        typedef ReverseVectorIterator<T, is_const> self_type;
        typedef T* pointer;
        typedef std::ptrdiff_t difference_type;

    public:
        ReverseVectorIterator(pointer actual = NULL) {this->_actual = actual;}
        ReverseVectorIterator(const ReverseVectorIterator<T, false> &other) {this->_actual = other.getActual();}
        ReverseVectorIterator& operator=(const self_type &other){
            if (this != &other)
                this->_actual = other.getActual();
            return *this;        
        }
        ~ReverseVectorIterator() {}
    
        self_type& operator++(){
            this->_actual -=1;
            return *this;
        }
        self_type operator++(int){
            self_type tmp(*this);
            this->_actual -= 1;
            return tmp;
        }
        self_type& operator--(){
            this->_actual += 1;
            return *this;
        }
        self_type operator--(int){
            self_type tmp(*this);
            this->_actual += 1;
            return tmp;
        }

// Random Operators
        self_type operator+(difference_type n){
            self_type tmp(*this);
            return tmp -= n;
        }

        self_type operator-(difference_type n){
            self_type tmp(*this);
            return tmp += n;
        }

        self_type operator-=(difference_type n){
            return *this + n; 
        }

        self_type operator+=(difference_type n){
            return *this - n;
        }
};

template <typename pointer>
size_t  operator- (const pointer& lhs, const pointer& rhs) {return &lhs - &rhs;}
}

#endif