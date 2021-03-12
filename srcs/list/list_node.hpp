#ifndef LIST_NODE_HPP
# define LIST_NODE_HPP

#include <cstddef>
#include <iostream>

namespace ft {
template <typename T>
class Node {
    private:
        T         _content;
        Node     *_previous;
        Node     *_next;
    
    public:
        Node(T content = T(), Node *previous = NULL, Node *next = NULL) : _content(content), _previous(previous), _next(next) {}
        Node(Node const &other) : _content(other._content), _previous(other._previous), _next(other._next) {}
        ~Node() {}

// Operator
        Node& operator=(Node const &other) {
            if (this != &other){
                _content = other._content;
                _previous = other._previous;
                _next = other._next;
            }
        }
        T& operator*() { return _content;}

// Getters
        T&        content() { return (_content); }
        Node *previous() { return (_previous); }
        Node *next() { return (_next); }

// Setters
        void setNext(Node<T> *other){
            _next = other;
        }
        void setPrevious(Node<T> *other){
            _previous = other;
        }
    
// Auto management
        void retirement(){
            if (_previous)
                _previous->_next = _next;
            if (_next)
                _next->_previous = _previous;
        }

        void addBefore(Node *newNode) {
            newNode->_previous = _previous;
            newNode->_next = this;
            if (_previous)
                _previous->_next = newNode;
            _previous = newNode;
        }

        void addAfter(Node *newNode) {
            newNode->_next = _next;
            newNode->_previous = this;
            if (_next)
                _next->_previous = newNode;
            _next = newNode;
        }
};
}

#endif