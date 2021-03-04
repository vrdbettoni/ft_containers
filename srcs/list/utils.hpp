#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft{
// Assign List
template <bool b, class T = void>
struct enable_if {};
template<class T>
struct enable_if<true, T>
{
	typedef T type;
};

// Iterator
template <bool flag, class is_true, class is_false>
struct choose;

template <class is_true, class is_false>
struct choose<true, is_true, is_false>
{
    typedef is_true type;
};

template <class is_true, class is_false>
struct choose<false, is_true, is_false>
{
    typedef is_false type;
};

//Swap
template <class T>
void swap(T& left, T& right){
    T tmp = left;
    left = right;
    right = tmp;
}
}
#endif