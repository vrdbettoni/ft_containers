#ifndef LIST_HPP
# define LIST_HPP

# include "list_node.hpp"
# include "list_iterator.hpp"
# include "utils.hpp"
# include <algorithm>
# include <limits>
# include <functional>

namespace ft {
template <typename T>
class list
{
    public:
        typedef ListIterator<T, false> iterator;
        typedef ListIterator<T, true> const_iterator;
        typedef ReverseListIterator<T, false> reverse_iterator;
        typedef ReverseListIterator<T, true> const_reverse_iterator;
        typedef Node<T>* node_pointer;
 
    private:
        Node<T> *_head;
        Node<T> *_tail;
        size_t  _size;

        void del(Node<T> *toDel){
            _size--;
            toDel->retirement(true);
        }
    
    public:
// Canonical Form
        list() : _head(new Node<T>), _tail(new Node<T>), _size(0){
            _head->addAfter(_tail);
        }
        list(list const &other){*this = other;}
        list& operator=(list const &other){
            if (this != &other){
                _head = other._head;
                _tail = other._tail;
                _size = other._size;
            }
            return (*this);
        }

        ~list(){
            for (node_pointer tmp = _head; _head; tmp = _head){
                _head = _head->next();
                delete tmp;
            }
        }

// Other constructor
        // template <class InputIterator>
        // list(InputIterator first, InputIterator last){

        // }

// Member function
// Iterators
        iterator begin() { return iterator(_head->next()); }
        iterator end() { return iterator(_tail); }
        const_iterator begin() const { return const_iterator(_head->next()); }
        const_iterator end() const { return const_iterator(_tail); }
        reverse_iterator rbegin() { return reverse_iterator(_tail->previous()); }
        reverse_iterator rend () { return reverse_iterator (_head); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_tail->previous()); }
        const_reverse_iterator rend () const { return const_reverse_iterator (_head); }
    
// Basic Insertion
        void push_back(const T &value){
            _size++;
            Node<T>* newOne = new Node<T>(value);
            _tail->addBefore(newOne);
        }
        void push_front(const T &value){
            _size++;
            Node<T>* newOne = new Node<T>(value);
            _head->addAfter(newOne);
        }

        void assign(size_t n, const T& val){
            clear();
            for (size_t i = 0; i < n; ++i)
                push_back(val);
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                typename enable_if< !std::numeric_limits<InputIterator>::is_integer , void >::type* = 0){
            clear();
            for (; first != last; ++first)
                push_back(*first);
        }

// Remove
        void pop_front(){
            if (_size > 0)
                del(_head->next());
        }
        void pop_back(){
            if (_size > 0)
                del(_tail->previous());
        }
    
        void clear(){
            iterator start(_head->next());
            iterator end(_tail);
            erase(start, end);
        }

        iterator erase(iterator position){
            iterator ret = position;
            ret++;
            del(position.getNode());
            return ret;
        }

        iterator erase(iterator first, iterator last){
            while (first != last)
                del(first.getNode());
            return last;
        }

        void unique(void) {
            this->unique(std::equal_to<T>());
        }

        template<class BinaryPredicate>
        void unique(BinaryPredicate binary_pred){
            node_pointer first = _head->next();
            node_pointer second;
            while (first != _tail){
                second = first->next();
                if ((binary_pred)(first->content(), second->content()))
                    del(second);
                else
                    first = first->next();
            }
        }

        void remove(const T& val){
            for (node_pointer tmp = _head; tmp->next() != _tail; tmp = tmp->next()){
                if (tmp->next()->content() == val){
                    del(tmp->next());
                    tmp = tmp->previous();
                }
            }
        }

        template<typename Predicate>
        void remove_if(Predicate pred){
            for (node_pointer tmp = _head; tmp->next() != _tail; tmp = tmp->next()){
                if ((*pred)(tmp->next()->content())){
                    del(tmp->next());
                    tmp = tmp->previous();
                }
            }
        }

// Management
        void splice(iterator position, list& x){
            splice(position, x, x.begin(), x.end());
        }
        void splice(iterator position, list& x, iterator i){
            iterator next(i);
            splice(position, x, i, ++next);
        }
        void splice(iterator position, list &x, iterator first, iterator last){
            if (first == last)
                return;
            iterator tmp(first.getNode()->previous());
            position.getNode()->previous()->setNext(first.getNode());
            first.getNode()->setPrevious(position.getNode()->previous());
            position.getNode()->setPrevious(last.getNode()->previous());
            position.getNode()->previous()->setNext(position.getNode());
            tmp.getNode()->setNext(last.getNode());
            last.getNode()->setPrevious(tmp.getNode());
            for (; first != position; ++first){
                ++_size;
                --x._size;
            }
        }

        void reverse (void){
            iterator pos = begin();
            for (size_t i = 0; i < _size - 1; ++i)
                splice(pos, *this, --end());            
        }

        void resize(size_t n, T val = T()){
            while (n > _size)
                    push_back(val);
            while (n < _size)
                pop_back();
        }

        void swap(list &x){
            ft::swap(_size, x._size);
            ft::swap(_head, x._head);
            ft::swap(_tail, x._tail);
        }

        void merge(list &x){
            merge(x, std::less<T>());
        }

        template <class Compare>
        void merge(list &x, Compare comp){
            if (this == &x)
                return;
            for (iterator it = begin(); it != end() && x._size; ++it){
                node_pointer tmp = x.begin().getNode();
                if ((comp)(tmp->content(), *it)){
                    tmp->retirement(false);
                    it.getNode()->addBefore(tmp);
                    ++_size;
                    --x._size;
                    --it;
                }
            }
            if (x._size)
                splice(end(), x);
        }

        void sort(){
            sort(std::less<T>());
        }

        template <class Compare>
        void sort(Compare comp){
            if (_size < 2)
                return;
            list<T> right_part;
            list<T> left_part;
            iterator it = begin();
            std::advance(it, _size / 2);
            right_part.splice(right_part.end(), *this, it, end());
            left_part.splice(left_part.end(), *this);
            // std::cout << "right: ";
            // for (iterator it = right_part.begin(); it != right_part.end(); ++it)
            //     std::cout << *it;
            // std::cout << "\nleft: ";
            // for (iterator it = left_part.begin(); it != left_part.end(); ++it)
            //     std::cout << *it;
            // std::cout << std::endl;;
            
            right_part.sort(comp);
            left_part.sort(comp);
            left_part.merge(right_part);
            merge(left_part, comp);
        }

// Informations
        size_t size(){ return _size; }
        bool empty(){ return (_size == 0);}
        T& front() { return(_head->next()->content()); }
        T& back() { return(_tail->previous()->content()); }
        const T& front() const { return(_head->next()->content()); }
        const T& back() const { return (_tail->previous()->content()); }
};
}

#endif