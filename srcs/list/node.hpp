#ifndef NODE_HPP
# define NODE_HPP

#include <cstddef>

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
        virtual ~Node() {}

// Operator
        Node& operator=(Node const &other){
            if (*this != other){
                _content = other.content;
                _previous = other._previous;
                _next = other._next;
            }
        }

        T operator*() {return (*&_content); }

// Getters
        T     content() { return (_content); }
        Node *previous() { return (_content); }
        Node *next() { return (_next); }

// Auto management
        void retirement() {
            if (_previous)
                _previous->_next = _next;
            if (_next)
                _next->previous = _previous;
        }

        void addBefore(Node *newNode) {
            if (_previous)
                _previous->_next = newNode;
            newNode->_next = _previous;
            newNode->_next = this;
            _previous = newNode;
        }

        void addAfter(Node *newNode) {
            newNode->_next = _next;
            newNode->_previous = this;
            _next = newNode;
            if (newNode->_next)
                newNode->_next->_previous = _next;
        }
};
}

#endif