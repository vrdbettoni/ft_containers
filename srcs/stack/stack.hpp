#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"

namespace ft{
template <class T, class Container = ft::vector<T> > 
class stack
{
    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef Container container_type  ;
 
    protected:
        container_type c;
 
    public:
        explicit stack(const container_type &cntr = container_type()) : c(cntr) {}
 
        bool              empty() const     { return c.empty(); }
        size_type         size()  const     { return c.size(); }

        value_type&       top()             { return c.back(); }
        const value_type& top() const       { return c.back(); }
    
        void push(const value_type& x)      { c.push_back(x); }
        void pop()                          { c.pop_back(); }

        friend bool operator== (const stack<T, Container>& rhs, const stack<T, container_type> lhs) { return rhs.c == lhs.c; }
        friend bool operator< (const stack<T, Container>& rhs, const stack<T, container_type> lhs) { return rhs.c < lhs.c; }
        friend bool operator!= (const stack<T, Container>& rhs, const stack<T, container_type> lhs) { return rhs.c != lhs.c; }
        friend bool operator<= (const stack<T, Container>& rhs, const stack<T, container_type> lhs) { return rhs.c <= lhs.c; }
        friend bool operator> (const stack<T, Container>& rhs, const stack<T, container_type> lhs) { return rhs.c > lhs.c; }
        friend bool operator>= (const stack<T, Container>& rhs, const stack<T, container_type> lhs) { return rhs.c >= lhs.c; }

};
}
#endif