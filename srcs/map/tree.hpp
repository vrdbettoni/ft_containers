#ifndef TREE_HPP
# define TREE_HPP

#include "../utils.hpp"

#include <cstddef>
#include <cmath>

#include <memory>
#include <functional>
#include <limits>

#include <iostream>
namespace ft {

											  /* NODE */
template <class T>
struct AvlNode
{
	T			data;
	AvlNode* 	parent;
	AvlNode* 	left;
	AvlNode* 	right;
	int			balance;

	AvlNode(const T& newData = T()) : data(newData), parent(NULL), left(NULL), right(NULL), balance(0) {}
};



											/* ITERATORS */

template <class T, bool is_const>
class AvlIterator
{
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef typename choose<is_const, const value_type*, value_type*>::type pointer;
        typedef typename choose<is_const, const value_type&, value_type&>::type reference;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        typedef AvlIterator<value_type, is_const> self_type;
        typedef typename choose<is_const, const AvlNode<value_type>*, AvlNode<value_type>*>::type node_pointer;

    public:
		AvlIterator(AvlNode<value_type>* node = NULL) : _node(node) {}
		AvlIterator(const AvlIterator<value_type, false>& other) : _node(other.get_node()) {}
		AvlIterator& operator=(const self_type& other) {
			if (this != &other)
				_node = other.get_node();
			return *this;
		}

		reference operator*() { return _node->data; }
		node_pointer operator->() { return &_node->data; }
		node_pointer get_node() const { return _node; }

		self_type& operator++() {
			node_pointer parent = _node->parent;
			if (_node->right) {
				for (_node = _node->right; _node->left; _node = _node->left);
			}
			else if (_node == parent->left)
				_node = parent;
			else
				for (_node = _node->parent; _node == _node->parent->right; _node = _node->parent);
			return *this;
		}

		self_type& operator--() {
			node_pointer parent = _node->parent;
			if (_node->left)
				for (_node = _node->left; _node->right; _node = _node->right);
			else if (_node == parent->right)
				_node = parent;
			else
				for (_node = _node->parent; _node == _node->parent->left; _node = _node->parent);
			return *this;
		}

		self_type& operator++(int) {
			self_type tmp = *this;
			return ++*this;
		}

		self_type& operator--(int) {
			self_type tmp = *this;
			return --*this;
		}

        friend bool operator== (const self_type& rhs, const self_type& lhs) { return rhs._node == lhs._node; }
        friend bool operator!= (const self_type& rhs, const self_type& lhs) { return rhs._node != lhs._node; }

	protected:
		node_pointer _node;

};

template <class T, bool is_const>
class ReverseAvlIterator : public AvlIterator<T, is_const>
{
    public:
        typedef T value_type;
        // typedef std::ptrdiff_t difference_type;
        // typedef typename choose<is_const, const value_type*, value_type*>::type pointer;
        // typedef typename choose<is_const, const value_type&, value_type&>::type reference;
        // typedef std::bidirectional_iterator_tag iterator_category;

    private:
        typedef ReverseAvlIterator<value_type, is_const> self_type;
        typedef typename choose<is_const, const AvlNode<value_type>*, AvlNode<value_type>*>::type node_pointer;

	public:
		ReverseAvlIterator(node_pointer node) : AvlIterator<T, is_const>(node) {}
        ReverseAvlIterator(const ReverseAvlIterator<T, false> &other) { this->_node = other.get_node(); }
		self_type& operator=(const self_type& other) {
			if (this != &other)
				this->_node = other.get_node();
			return *this;
		}

		self_type& operator++() { AvlIterator<T, is_const>::operator--(); }
		self_type& operator--() { AvlIterator<T, is_const>::operator++(); }
		// self_type& operator++(int) { AvlIterator<T, is_const>::operator--(int); }
		// self_type& operator--(int) { AvlIterator<T, is_const>::operator++(int); }
};


											  /* TREE */

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class AvlTree
{
    public:
        typedef T value_type;
        // typedef AvlIterator<T, false> iterator;
        // typedef AvlIterator<T, true> const_iterator;
        // typedef ReverseAvlIterator<T, false> reverse_iterator;
        // typedef ReverseAvlIterator<T, true> const_reverse_iterator;
        typedef Compare compare;
        typedef Alloc allocator_type;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

	private:
        typedef AvlNode<value_type> node;
        typedef node * node_pointer;
        typedef typename Alloc::template rebind<node>::other node_allocator;

	public:

/* Constructor */
        AvlTree (const compare& comp = compare(), const allocator_type& alloc = allocator_type())
            : _root(NULL), _begin(new_node()), _end(new_node()), _size(0), _alloc(alloc), _comp(comp)
        {
            _begin->parent = _end;
            _end->parent = _begin;
        }


/* Manipulation */
		void add_node(T data) {
			node_pointer newNode = new_node(data);
			unset_bounds();
			if (!_root) {
				_root = newNode;
				++_size;
			} else {
				recursive_add(_root, newNode);
				check_balance(newNode);
				std::cout << std::endl;
			}
			set_bounds();
		}

		void recursive_add(node_pointer parent, node_pointer newNode) {
			if (_comp(parent->data, newNode->data) > 0) {
				++parent->balance;
				if (!parent->right) {
					newNode->parent = parent;
					parent->right = newNode;
					++_size;
				} else {
					recursive_add(parent->right, newNode);
				}
			} else {
				--parent->balance;
				if (!parent->left) {
					newNode->parent = parent;
					parent->left = newNode;
					++_size;
				} else {
					recursive_add(parent->left, newNode);
				}
			}
		}

		void check_balance(node_pointer node) {
			std::cout << "node: " << node->data << " balance: " << node->balance << std::endl;
			if (node->balance > 1 || node->balance < -1)
				rebalance(node);
			else if (node != _root)
				check_balance(node->parent);
			else
				return;
		}

		void rebalance(node_pointer node) {// left --> > -1 right --> < 1
			if (node->balance < -1) {
				if (node->left->balance < 0)
					node = right_rotation(node);
				else
					node = left_right_rotation(node);
			} else {
				if (node->right->balance < 0)
					node = left_rotation(node);
				else
					node = right_left_rotation(node);
			}
			if (!node->parent)
				_root = node;
		}

		node_pointer right_left_rotation(node_pointer node) {
			std::cout << "right left rotation" << std::endl;
			node->right = right_rotation(node->right);
			return left_rotation(node);
		}

		node_pointer left_right_rotation(node_pointer node) {
			std::cout << "left right rotation" << std::endl;
			node->left = left_rotation(node->left);
			return right_rotation(node);
		}

		node_pointer left_rotation(node_pointer node) {
			std::cout << "left rotation" << std::endl;
			node_pointer tmp = node->right;
			node->right = tmp->left;
			tmp->left = node;
			return tmp;
		}

		node_pointer right_rotation(node_pointer node) {
			std::cout << "right rotation" << std::endl;
			node_pointer tmp = node->left;
			node->left = tmp->right;
			tmp->right = node;
			return tmp;
		}

	public: //protected
		node_pointer	_root;
		node_pointer	_begin;
		node_pointer	_end;
		size_type		_size;
		node_allocator	_alloc;
		compare			_comp;

		node_pointer new_node(const T& newData = T()) {
			node_pointer newNode = _alloc.allocate(1);
			_alloc.construct(newNode, newData);
			return newNode;
		}

		void delete_node(node_pointer toDelete) {
			_alloc.destroy(toDelete);
			_alloc.deallocate(toDelete, 1);
		}

		node_pointer get_min(node_pointer node) {
			while (node->left)
				node = node->left;
			return node;
		}

		node_pointer get_max(node_pointer node) {
			while (node->right)
				node = node->right;
			return node;
		}

		void set_bounds() {
			if (_size) {
				_begin->parent = get_min(_root);
				_end->parent = get_max(_root);
				_begin->parent->left = _begin;
				_end->parent->right = _end;
			} else {
				_begin->parent = _end;
				_end->parent = _begin;
			}
		}

		void unset_bounds() {
			if (_begin->parent && _begin->parent != _end)
				_begin->parent->left = NULL;
			if (_end->parent && _end->parent != _begin)
				_end->parent->right = NULL;
		}
};

};
#endif