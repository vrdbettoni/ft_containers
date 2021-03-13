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
# include <memory>

namespace ft{
template <typename T, class Alloc = std::allocator<T> >
class vector
{
    public:
        typedef std::ptrdiff_t difference_type;
	    typedef size_t size_type;
        typedef Alloc allocator_type;
        typedef T value_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
	    typedef VectorIterator<value_type, false> iterator;
	    typedef VectorIterator<value_type, true> const_iterator;
	    typedef ReverseVectorIterator<value_type, false> reverse_iterator;
	    typedef ReverseVectorIterator<value_type, true> const_reverse_iterator;

    private:
        typedef vector<value_type, allocator_type> self_type;
    
    private:
        allocator_type  _alloc;
        pointer         _data;
        size_type       _size;
        size_type       _capacity;

    public:
        explicit vector(const allocator_type &alloc = allocator_type()) 
            : _data(NULL), _size(0), _capacity(0), _alloc(alloc) {}
        
        explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) 
            : _data(NULL), _size(0), _capacity(0), _alloc(alloc)
        {
           reserve(n);
           push_n_back(n, val);
        }
    
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), 
            typename enable_if< !std::numeric_limits<InputIterator>::is_integer , void >::type* = 0)
                : _size(0), _capacity(0), _data(0), _alloc(alloc) 
        {
            assign(first, last);
        }

        vector(vector const &other) : _data(NULL), _size(0), _capacity(0), _alloc(other._alloc)
        {
            assign(other.begin(), other.end());
        }

        vector& operator=(const vector &other){
            if (this != &other)
                assign(other.begin(), other.end());
            return (*this);
        }

        ~vector(){
            clear();
            _alloc.deallocate(_data, _capacity);
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

        size_type capacity() const {
            return _capacity;
        }

        bool empty() const {
            return _size == 0;
        }

        void resize(size_type n, value_type val = value_type()){
            if (n > _size)
                push_n_back(n - _size, val);
            else
                while (n < _size)
                    pop_back();
        }

        void reserve(size_type n){
            if (n > _capacity)
                realloc(n);
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
            push_n_back(1, val);
        }

        void pop_back(){
            if (_size > 0){
                _alloc.destroy(_data + _size - 1);
                --_size;
            }
        }

        iterator insert(iterator position, const value_type &val){
            difference_type p = position - begin();
            insert(position, 1, val);
            return begin() + p;
        }

        void insert (iterator position, size_type n, const value_type &val){
            vector<value_type> tmp(position, this->end());
            erase(position, end());
            reserve(_size + n + tmp._size);
            push_n_back(n, val);
            for (iterator it = tmp.begin(); it != tmp.end(); ++it)
                push_back(*it);
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, 
                    typename enable_if< !std::numeric_limits<InputIterator>::is_integer , void >::type* = 0){
            vector<value_type> tmp(position, this->end());
            erase(position, end());
            reserve(_size + std::distance(first, last) + tmp._size);
            for (; first != last; ++first)
                push_back(*first);
            for (iterator it = tmp.begin(); it != tmp.end(); ++it)
                push_back(*it);
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
                _alloc.destroy(_data + i);
            _size = 0;
        }

    private:
        void push_n_back(size_type n, const value_type &val = value_type()){
            reserve(_size + n);
            for (size_type i = 0; i < n; i++)
                _alloc.construct(_data + _size + i, val);
            _size += n;
        }

        void realloc(size_type new_size){
            size_type new_capacity = _capacity == 0 ? 1 : _capacity;
            while (new_capacity < new_size)
                new_capacity = std::ceil(new_capacity * 1.5f);
            value_type *new_array = _alloc.allocate(new_capacity);
            for (size_type i = 0; i < _size; i++){
                _alloc.construct(new_array + i, _data[i]);
                _alloc.destroy(_data + i);
            }
            _alloc.deallocate(_data, _capacity);
            _data = new_array;
            _capacity = new_capacity;
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
template<typename value_type, class Alloc>
bool operator!=(const vector<value_type, Alloc> &lhs, const vector<value_type, Alloc> &rhs){
    return !(lhs == rhs);        
}
template<typename value_type, class Alloc>
bool operator<(const vector<value_type, Alloc> &lhs, const vector<value_type, Alloc> &rhs){
    typename ft::vector<value_type>::const_iterator rit = rhs.begin();
    for (typename ft::vector<value_type>::const_iterator lit = lhs.begin(); rit != rhs.end() && lit != lhs.end(); ++lit, ++rit){
        if (*lit < *rit)
            return true;
        if (*lit > *rit)
            return false;
    }   
    return (lhs.size() >= rhs.size() ? false : true);
}
template<typename value_type, class Alloc>
bool operator>(const vector<value_type, Alloc> &lhs, const vector<value_type, Alloc> &rhs){
    return rhs < lhs;
}
template<typename value_type, class Alloc>
bool operator<=(const vector<value_type, Alloc> &lhs, const vector<value_type, Alloc> &rhs){
    return !(rhs < lhs);
}
template<typename value_type, class Alloc>
bool operator>=(const vector<value_type, Alloc> &lhs, const vector<value_type, Alloc> &rhs){
    return !(lhs < rhs);
}

template<typename value_type, class Alloc>
void swap(ft::vector<value_type, Alloc> &lhs, ft::vector<value_type, Alloc> &rhs){
	lhs.swap(rhs);
}

}
#endif