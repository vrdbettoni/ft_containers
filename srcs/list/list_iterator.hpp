#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

#include <iterator>
#include "list_node.hpp"
#include "utils.hpp"

namespace ft {
template <class T, bool is_const>
class ListIterator
{
    public:
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef typename choose<is_const, const T*, T*>::type pointer;
        typedef typename choose<is_const, const T&, T&>::type reference;
        typedef T value_type;
    
    private:
        typedef ListIterator<T, is_const> self_type;
        typedef typename choose<is_const, const Node<T>*, Node<T>*>::type node_pointer;
    
    protected:
        Node<T>* _node;

    public:
// Canonical Form
        ListIterator(Node<T>* node = NULL) : _node(node) {}
        ListIterator(const ListIterator<T, false> &other) : _node(other.getNode()) {}
        ListIterator& operator=(const self_type &other){
            if (this != &other)
                _node = other.getNode();
            return *this;
        }
        ~ListIterator() {}

//Operators
        reference operator*() { return _node->content();}
        pointer   operator->() { return &_node->content();}

        self_type& operator++(){
            _node = _node->next();
            return *this;
        }
        self_type operator++(int){
            self_type tmp(*this);
            _node = _node->next();
            return tmp;
        }
        self_type& operator--(){
            _node = _node->previous();
            return *this;
        }
        self_type operator--(int){
            self_type tmp(*this);
            _node = _node->previous();
            return tmp;
        }

        bool operator==(const self_type &lhs){
            return this->_node == lhs._node;
        }
        bool operator!=(const self_type &lhs){
            return !(*this == lhs);
        }

//Getters
        node_pointer getNode() const {
            return _node;
        }
};

template<class T, bool is_const>
class ReverseListIterator : public ListIterator<T, is_const>
{
    
    public:
        typedef ReverseListIterator<T, is_const> self_type;

    public:
        ReverseListIterator(Node<T>* node = NULL) {this->_node = node;}
        ReverseListIterator(const ReverseListIterator<T, false> &other) {this->_node = other.getNode();}
        ReverseListIterator& operator=(const self_type &other){
            if (this != &other)
                this->_node = other.getNode();
            return *this;        
        }
        ~ReverseListIterator() {}
    
        self_type& operator++(){
            this->_node = this->_node->previous();
            return *this;
        }
        self_type operator++(int){
            self_type tmp(*this);
            this->_node = this->_node->previous();
            return tmp;
        }
        self_type& operator--(){
            this->_node = this->_node->next();
            return *this;
        }
        self_type operator--(int){
            self_type tmp(*this);
            this->_node = this->_node->next();
            return tmp;
        }
};
}

#endif