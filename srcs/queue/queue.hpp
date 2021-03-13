#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "../list/list.hpp"

namespace ft{
template<class T, class Container = ft::list<T> >
class queue
{
    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef Container container_type;
    
    protected:
        container_type c;
    
    public:
        explicit queue(const container_type &cntr = container_type()) : c(cntr) {}
        ~queue() {}

        bool                empty() const   { return c.empty(); }
        size_type           size() const    { return c.size(); }

        value_type&         front()         { return c.front(); }
        value_type&         back()          { return c.back(); }
        const value_type&   front() const   { return c.front(); }
        const value_type&   back() const    { return c.back(); }

        void push(const value_type &val)    { c.push_back(val); }
        void pop()                          { c.pop_front(); }

        friend bool operator== (const queue<T, Container>& rhs, const queue<T, container_type> lhs) { return rhs.c == lhs.c; }
        friend bool operator< (const queue<T, Container>& rhs, const queue<T, container_type> lhs) { return rhs.c < lhs.c; }
        friend bool operator!= (const queue<T, Container>& rhs, const queue<T, container_type> lhs) { return rhs.c != lhs.c; }
        friend bool operator<= (const queue<T, Container>& rhs, const queue<T, container_type> lhs) { return rhs.c <= lhs.c; }
        friend bool operator> (const queue<T, Container>& rhs, const queue<T, container_type> lhs) { return rhs.c > lhs.c; }
        friend bool operator>= (const queue<T, Container>& rhs, const queue<T, container_type> lhs) { return rhs.c >= lhs.c; }

};
}

#endif