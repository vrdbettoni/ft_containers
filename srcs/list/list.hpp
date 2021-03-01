#ifndef LIST_HPP
# define LIST_HPP

# include "list_node.hpp"
# include "list_iterator.hpp"
# include <algorithm>

namespace ft {
template <typename T>
class list
{
    public:
        typedef ListIterator<T> iterator;
        typedef ConstListIterator<T> const_iterator;
        typedef ReverseListIterator<T> reverse_iterator;
        typedef ConstReverseListIterator<T> const_reverse_iterator;
        typedef Node<T>* node_pointer;
 
    private:
        Node<T> *_head;
        Node<T> *_tail;
        size_t  _size;

        void del(Node<T> *toDel){
            _size--;
            toDel->retirement();
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
            // _head = _head->next();
            // for (; _head; _head = _head->next()){
            //     delete (_head->previous());
            //}
        }

// Other constructor

// Member function
// Iterators
        iterator begin() { return iterator(_head->next()); }
        iterator end() { return iterator(_tail); }
        const_iterator cbegin() const { return const_iterator(_head->next()); }
        const_iterator cend() const { return const_iterator(_tail); }
        reverse_iterator rbegin() { return reverse_iterator(_tail->previous()); }
        reverse_iterator rend () { return reverse_iterator (_head); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator(_tail); }
        const_reverse_iterator crend () const { return const_reverse_iterator (_head); }
    
// Add
        void push_back(T value){
            _size++;
            Node<T>* newOne = new Node<T>(value);
            _tail->addBefore(newOne);
        }
        void push_front(T value){
            _size++;
            Node<T>* newOne = new Node<T>(value);
            _head->addAfter(newOne);
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
    
        void erase(iterator position){
            del(position._actual);
        }

        void erase(iterator first, iterator last){
            while (first && first != last)
                del(first._actual);
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