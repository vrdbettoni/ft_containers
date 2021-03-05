#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "vector_iterator.hpp"
# include "../utils.hpp"
# include <cmath>
# include <cstddef>
# include <limits>
# include <cstring>
# include <iostream>

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
            _capacity = std::ceil(n * 1.5f);
            _data = new value_type [_capacity];
            for (; _size < n; ++_size)
                _data[_size] = val;
        }
    
        template <class InputIterator>
        vector(InputIterator first, InputIterator last){
            _capacity = std::ceil(std::distance(first, last) * 1.5f);
            _data = new value_type [_capacity];
            for (; first != last; ++first)
                _data[_size++] = first;
        }

        // vector(const vector &other) :  _data(NULL), _size(0), _capacity(0){
        //     reserve(other._capacity);
        //     for (size_t count = 0; count < other._size; ++count)
        //         _data[count] = other._data[count];
        // }
        vector(vector const &other) : _size(other._size), _capacity(other._capacity){
             _data = new value_type [_capacity];
             std::memcpy(_data, other._data, _size * sizeof(value_type));
         }

        ~vector(){
            // while (--_size)
            //     _data[_size].T::~T();
            // delete[] _data;
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
            return &_data[n];
        }

        const_reference at(size_type n) const {
            return &_data[n];
        }

        reference front(){
            return &_data[0];
        }

        const_reference front() const {
            return &_data[0];
        }
        
        reference back(){
            return &_data[_size - 1];
        }

        const_reference back() const {
            return &_data[_size - 1];
        }

// Modifiers
        void assign(size_type n, const value_type& val){
            clear();
            while (_size < n)
                push_back(val);
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last, 
            typename enable_if< !std::numeric_limits<InputIterator>::is_integer , void >::type* = 0)
        {
            clear();
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
            _data[_size-- - 1].T::T();
        }

        iterator insert(iterator position, const value_type &val){
            insert(position, 1, val);
            return position;
        }

        void insert (iterator position, size_type n, const value_type &val){
            vector<value_type> tmp(position, this->end());
            reserve(_size + n);
            for(size_t count = n; count--; ++position)
                position.getActual() = val;
            for (size_t count = 0; count < tmp._size; ++count)
                _data[_size++] = tmp._data[count];
            delete[] tmp;
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last){
            vector<value_type> tmp(position, this->end());
            reserve(_size + std::distance(first, last));
            for(; first != last; ++first)
                position++.getActual() = first;
            for (size_t count = 0; count < tmp._size; ++count)
                _data[_size++] = tmp._data[count];
            delete[] tmp;
        }  

        iterator erase(iterator position){
            pointer tmp = position.getActual();
            // tmp->T::~T();
            std::cout << "Size: " << _size << " Distance: "<< std::distance(position, this->end()) << std::endl;
            std::memmove(tmp, (tmp + 1), std::distance(position, this->end()));
            // for (size_t count = std::distance(position, this->end()); count--; ++tmp)
                // tmp = tmp + 1;
            --_size;   
            return position;
        }

        void clear(){
            for (; _size; --_size)
                _data[_size - 1].T::~T();
        }

};
}
#endif