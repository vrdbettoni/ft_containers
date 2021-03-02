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
        const_iterator begin() const { return const_iterator(_head->next()); }
        const_iterator end() const { return const_iterator(_tail); }
        reverse_iterator rbegin() { return reverse_iterator(_tail->previous()); }
        reverse_iterator rend () { return reverse_iterator (_head); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_tail->previous()); }
        const_reverse_iterator rend () const { return const_reverse_iterator (_head); }
    
// Basic Insertion
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
            while (first && first != last)
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
            first.getNode()->previous()->setNext(last.getNode());
            position.getNode()->previous()->setNext(first.getNode());
            position.getNode()->setPrevious(last.getNode()->previous());
            position.getNode()->previous()->setNext(position.getNode());
            for (; first != position; ++first){
                ++_size;
                --x._size;
            }
        }

        void reverse (void)
        {
            if (!_size)
                return ;
            iterator pos = begin();
            for (size_t i = 0; i < _size - 1; ++i)
                splice(pos, *this, --end());
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