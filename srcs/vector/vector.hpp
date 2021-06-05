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
        pointer         _data;
        size_type       _size;
        size_type       _capacity;
        allocator_type  _alloc;

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
                : _data(0), _size(0), _capacity(0), _alloc(alloc)
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
        iterator begin() { return iterator(_data, 0); }
        iterator end() { return iterator(_data, _size); }
        const_iterator begin() const { return const_iterator(_data, 0); }
        const_iterator end() const { return const_iterator(_data, _size); }
        reverse_iterator rbegin() { return reverse_iterator(_data, _size - 1); }
        reverse_iterator rend () { return reverse_iterator (_data, -1); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_data, _size - 1); }
        const_reverse_iterator rend () const { return const_reverse_iterator (_data, -1); }

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
        const_reference operator[](size_type index) const {
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
            iterator next = position;
            ++next;
            return erase(position, next);
        }

        iterator erase(iterator first, iterator last){
            if (first == last)
                return first;
            vector tmp (last, end());
            size_type new_size = first - begin();
            while (_size > new_size)
                pop_back();
            for (iterator it = tmp.begin(); it != tmp.end(); ++it)
                push_back(*it);
            return iterator(_data, first.getIndex());
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

        friend bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
        {
            if (lhs._size != rhs._size)
                return false;
            for (size_type i = 0; i < lhs._size; ++i) {
                if (lhs[i] != rhs[i])
                    return false;
            }
            return true;
        }

        friend bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
        {
            for (size_type i = 0; i < lhs._size && i < rhs._size; ++i) {
                if (lhs[i] < rhs[i])
                    return true;
                if (lhs[i] > rhs[i])
                    return false;
            }
            if (lhs._size >= rhs._size)
                return false;
            return true;
        }

        friend bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs == rhs); }
        friend bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(rhs < lhs); }
        friend bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return rhs < lhs; }
        friend bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs < rhs); }

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

template<typename value_type, class Alloc>
void swap(ft::vector<value_type, Alloc> &lhs, ft::vector<value_type, Alloc> &rhs){
	lhs.swap(rhs);
}

}
#endif