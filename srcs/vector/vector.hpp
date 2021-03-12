#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "vector_iterator.hpp"
# include "../utils.hpp"
# include <cmath>
# include <cstddef>
# include <limits>
# include <cstring>
# include <iostream>
# include <ostream>

namespace ft{
template <typename T>
class vector
{
    public:
        typedef std::ptrdiff_t difference_type;
	    typedef size_t size_type;
	    typedef T value_type;
	    typedef T* pointer;
	    typedef T const * const_pointer;
	    typedef T& reference;
	    typedef T const & const_reference;
	    typedef VectorIterator<value_type, false> iterator;
	    typedef VectorIterator<value_type, true> const_iterator;
	    typedef ReverseVectorIterator<value_type, false> reverse_iterator;
	    typedef ReverseVectorIterator<value_type, true> const_reverse_iterator;

    private:
        pointer     _data;
        size_type   _size;
        size_type   _capacity;

    public:
        explicit vector() : _data(NULL), _size(0), _capacity(0) {}
        
        explicit vector(size_type n, const value_type &val = value_type()) : _data(NULL), _size(0), _capacity(0){
           reserve(n);
            for (; _size < n; ++_size)
                _data[_size] = val;
        }
    
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
            typename enable_if< !std::numeric_limits<InputIterator>::is_integer , void >::type* = 0)
                : _size(0), _capacity(0), _data(0) {
            assign(first, last);
        }

        vector(vector const &other) : _data(NULL), _size(0), _capacity(0){
            assign(other.begin(), other.end());
         }

        ~vector(){
            clear();
            delete[] _data;
        }

// Iterators
        iterator begin() { return iterator(&(_data[0])); }
        iterator end() { return iterator(&(_data[_size])); }
        const_iterator begin() const { return const_iterator(&(_data[0])); }
        const_iterator end() const { return const_iterator(&(_data[_size])); }
        reverse_iterator rbegin() { return reverse_iterator(&(_data[_size])); }
        reverse_iterator rend () { return reverse_iterator (&(_data[0])); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(&(_data[_size])); }
        const_reverse_iterator rend () const { return const_reverse_iterator (&(_data[0])); }

// Capacity
        size_type size() const{
            return _size;
        }

	    size_type max_size() const {
		    return (min((size_type) std::numeric_limits<difference_type>::max(), (std::numeric_limits<size_t>::max() / sizeof(value_type))));
	    }

        size_type capacity() const{
            return _capacity;
        }

        bool empty() const{
            return _size == 0;
        }

        void resize(size_type n, value_type val = value_type()){
            for (; _size > n; --_size)
                _data[_size - 1].T::~T();
            while (_size < n)
                push_back(val);
        }

        void reserve(size_type n){
            n == 0 ? n++ : 0;
            if (n <= _capacity)
                return ;
            pointer newData = new value_type [n];
            for (size_t i = 0; i <  _size; ++i)
                newData[i] = _data[i];
            _capacity = n;
            delete[] _data;
            _data = newData;
        }

// Element Access
	    reference operator[](size_type index) {
		    return (_data[index]);
	    }

        reference at(size_type n){

            if (n >= _size)
                throw std::out_of_range("don't exist");
            return (_data[n]);
        }

        const_reference at(size_type n) const {
            if (n >= _size)
                throw std::out_of_range("don't exist");
            return (_data[n]);
        }

        reference front(){
            return _data[0];
        }

        const_reference front() const {
            return _data[0];
        }
        
        reference back(){
            return _data[_size - 1];
        }

        const_reference back() const {
            return _data[_size - 1];
        }

// Modifiers
        void assign(size_type n, const value_type& val){
            clear();
            reserve(n);
            while (_size < n)
                push_back(val);
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last, 
            typename enable_if< !std::numeric_limits<InputIterator>::is_integer , void >::type* = 0)
        {
            clear();
            reserve(last - first);
            for (; first != last; ++first)
                push_back(*first);
        }

        void push_back(const value_type &val){
            if (_size == _capacity)
                reserve(_capacity == 0 ? 1 : std::ceil(_capacity * 1.5f));
            _data[_size] = val;
            ++_size;
        }

        void pop_back(){
            _data[_size-- - 1].T::~T();
        }

        iterator insert(iterator position, const value_type &val){
            difference_type p = position - begin();
            insert(position, 1, val);
            return begin() + p;
        }

        void insert (iterator position, size_type n, const value_type &val){
            vector<value_type> tmp(position, this->end());
            difference_type p = position - begin();
            reserve(_size + n);
            iterator pos = begin() + p;
            for(size_t count = 0; count < n; ++count, ++pos){
                pos.getActual()->T::~T();
                *pos = val;
            }
            for (size_t count = 0; count < tmp._size; ++pos){
                pos.getActual()->T::~T();
                *pos =  tmp._data[count++];
            }
            _size += n;
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, 
                    typename enable_if< !std::numeric_limits<InputIterator>::is_integer , void >::type* = 0){
            vector<value_type> tmp(position, this->end());
            difference_type p = position - begin();
            reserve(_size + last - first);
            iterator pos = begin() + p;
            for(; first != last; ++first, ++pos){
                pos.getActual()->T::~T();
                *pos = *first;
                ++_size;
            }
            for (size_t count = 0; count < tmp._size; ++pos){
                pos.getActual()->T::~T();
                *pos =  tmp._data[count++];
            }
        }  

        iterator erase(iterator position){
            return erase(position, position + 1);
        }
 
        iterator erase(iterator first, iterator last){
            size_t count =  last - first;
            pointer tmp = first.getActual();
            for (; first != last; ++first)
                first.getActual()->T::~T();
            std::memmove(tmp, last.getActual(), (this->end() - last) * sizeof(T));
            _size -= count;
            return tmp;
        }

        void swap(vector& x){
            ft::swap(_capacity, x._capacity);
            ft::swap(_data, x._data);
            ft::swap(_size, x._size);
        }

        void clear(){
            for (size_t i = 0;  i < _size; ++i)
                _data[i].T::~T();
            _size = 0;
        }

};

// Operators Comp
template<typename value_type>
bool operator==(const vector<value_type> &lhs, const vector<value_type> &rhs){
    if (lhs.size() != rhs.size())
        return false;
    typename ft::vector<value_type>::const_iterator rit = rhs.begin();
    for (typename ft::vector<value_type>::const_iterator lit = lhs.begin(); lit != lhs.end(); ++lit){
        if (*lit != *rit)
            return false;
        ++rit;
    }
    return true;
}
template<typename value_type>
bool operator!=(const vector<value_type> &lhs, const vector<value_type> &rhs){
    return !(lhs == rhs);        
}
template<typename value_type>
bool operator<(const vector<value_type> &lhs, const vector<value_type> &rhs){
    typename ft::vector<value_type>::const_iterator rit = rhs.begin();
    for (typename ft::vector<value_type>::const_iterator lit = lhs.begin(); rit != rhs.end() && lit != lhs.end(); ++lit, ++rit){
        if (*lit < *rit)
            return true;
        if (*lit > *rit)
            return false;
    }   
    return (lhs.size() >= rhs.size() ? false : true);
}
template<typename value_type>
bool operator>(const vector<value_type> &lhs, const vector<value_type> &rhs){
    return rhs < lhs;
}
template<typename value_type>
bool operator<=(const vector<value_type> &lhs, const vector<value_type> &rhs){
    return !(rhs < lhs);
}
template<typename value_type>
bool operator>=(const vector<value_type> &lhs, const vector<value_type> &rhs){
    return !(lhs < rhs);
}

template<typename value_type>
void swap(ft::vector<value_type> &lhs, ft::vector<value_type> &rhs){
	lhs.swap(rhs);
}

}
#endif