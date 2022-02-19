#ifndef STACK_HPP
#define STACK_HPP
#include "includes/vector.hpp"

namespace ft {

    template <class T, class Container = ft::vector<T> >
    class stack {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;

            explicit stack (const container_type& ctnr = container_type()): _c(ctnr) {}
            bool empty() const { return _c.empty(); }
            size_type size() const { return _c.size(); }
            value_type& top() { return _c.back(); }
            const value_type& top() const { return _c.back(); } 
            void push (const value_type& val) { push_back(val); }
            void pop() { _c.pop_back(); }
            // template <class T, class Container>
            // friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            // {}
        protected:
            container_type _c;

    };
    // template <class T, class Container>
    // bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    // template <class T, class Container>
    // bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    // template <class T, class Container>
    // bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);	
    // template <class T, class Container>
    // bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    // template <class T, class Container>
    // bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);	
    // template <class T, class Container>
    // bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
}

#endif

