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
        ssize_t _idx;

    public:
// Canonical Form
        VectorIterator(pointer actual = NULL, ssize_t idx = 0) : _actual(actual), _idx(idx) {}
        VectorIterator(const VectorIterator<T, false> &other) : _actual(other.getActual()), _idx(other.getIndex()) {}
        VectorIterator& operator=(const self_type &other) {
            if (this != &other) {
                _idx = other.getIndex();
                _actual = other.getActual();
            }
            return *this;
        }
        ~VectorIterator() {}

// Basics Operators
        reference operator*() { return *(_actual + _idx);}
        pointer   operator->() { return (_actual + _idx);}
        reference operator[](size_t n) { return *(_actual + _idx + n); }

        self_type& operator++(){
            ++_idx;
            return *this;
        }
        self_type operator++(int){
            self_type tmp(*this);
            ++_idx;
            return tmp;
        }
        self_type& operator--(){
            --_idx;
            return *this;
        }
        self_type operator--(int){
            self_type tmp(*this);
            --_idx;
            return tmp;
        }

        bool operator==(const self_type &lhs){
            return this->_idx == lhs._idx;
        }
        bool operator!=(const self_type &lhs){
            return !(*this == lhs);
        }
// Random Operators
        self_type operator+(difference_type n){
            self_type tmp(*this);
            tmp._idx += n;
            return tmp;
        }

        self_type operator-(difference_type n){
            self_type tmp(*this);
            tmp._idx -= n;
            return tmp;
        }

        self_type operator-=(difference_type n){
            _idx -= n;
            return *this;
        }

        self_type operator+=(difference_type n){
            _idx += n;
            return *this;
        }

        friend self_type operator+ (difference_type n, const self_type& rhs) {
            self_type tmp = rhs;
            tmp._idx += n;
            return tmp;
        }

        friend self_type operator- (difference_type n, const self_type& rhs) {
            self_type tmp = rhs;
            tmp._idx -= n;
            return tmp;
        }
        friend difference_type  operator- (const self_type& lhs, const self_type& rhs) {return lhs.getIndex() - rhs.getIndex();}

        friend bool operator== (const self_type& lhs, const self_type& rhs) { return rhs - lhs == 0; }
        friend bool operator< (const self_type& lhs, const self_type& rhs) { return rhs - lhs > 0; }
        friend bool operator!= (const self_type& lhs, const self_type& rhs) { return !(lhs == rhs); }
        friend bool operator> (const self_type& lhs, const self_type& rhs) { return rhs < lhs; }
        friend bool operator<= (const self_type& lhs, const self_type& rhs) { return !(rhs < lhs); }
        friend bool operator>= (const self_type& lhs, const self_type& rhs) { return !(lhs < rhs); }

//Getters
        ssize_t getIndex() const {
            return _idx;
        }
        pointer getActual() const {
            return _actual;
        }
};

template<class T, bool is_const>
class ReverseVectorIterator : public VectorIterator<T, is_const>
{

    public:
        typedef ReverseVectorIterator<T, is_const> self_type;
        typedef typename choose<is_const, const T*, T*>::type pointer;
        typedef typename choose<is_const, const T&, T&>::type reference;
        typedef std::ptrdiff_t difference_type;

    public:
        ReverseVectorIterator(pointer actual = NULL, ssize_t idx = 0) {
            this->_actual = actual;
            this->_idx = idx;
        }

        ReverseVectorIterator(const ReverseVectorIterator<T, false> &other) {
            this->_actual = other.getActual();
            this->_idx = other.getIndex();
        }

        ReverseVectorIterator& operator=(const self_type &other){
            if (this != &other) {
                this->_idx = other.getIndex();
                this->_actual = other.getActual();
            }
            return *this;
        }
        ~ReverseVectorIterator() {}

        reference operator[](size_t n) { return *(this->_actual + this->_idx - n); }

        self_type& operator++(){
            this->_idx -=1;
            return *this;
        }
        self_type operator++(int){
            self_type tmp(*this);
            this->_idx -= 1;
            return tmp;
        }
        self_type& operator--(){
            this->_idx += 1;
            return *this;
        }
        self_type operator--(int){
            self_type tmp(*this);
            this->_idx += 1;
            return tmp;
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
            this->_idx += n;
            return *this;
        }

        self_type operator+=(difference_type n){
            this->_idx -= n;
            return *this;
        }

        friend self_type operator+ (difference_type n, const self_type& rhs) {
            self_type tmp = rhs;
            tmp._idx -= n;
            return tmp;
        }

        friend self_type operator- (difference_type n, const self_type& rhs) {
            self_type tmp = rhs;
            tmp._idx += n;
            return tmp;
        }

        friend difference_type  operator- (const self_type& lhs, const self_type& rhs) {return rhs.getIndex() - lhs.getIndex();}

};
};
#endif