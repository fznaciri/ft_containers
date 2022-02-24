#ifndef RANDOM_ACCESS_ITERATOR
# define RANDOM_ACCESS_ITERATOR
# include <iostream>
# include "iterator_traits.hpp"

namespace ft 
{
    template<class T>
    class random_access_iterator : public ft::iterator<std::random_access_iterator_tag, T>
    {
        public:
            typedef typename    ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename    ft::iterator<std::random_access_iterator_tag, T>::value_type        value_type;
    		typedef typename    ft::iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef             T*                                                                  pointer;
    		typedef             T&			                                                               reference;


            random_access_iterator() : _ptr(NULL) {}
            random_access_iterator(pointer ptr) : _ptr(ptr) {}
            random_access_iterator(random_access_iterator const& x) : _ptr(x._ptr) {}
            ~random_access_iterator() {}
            random_access_iterator& operator= (random_access_iterator const& x)
            {
                _ptr = x.base();
                return *this;
            }
            operator random_access_iterator<const value_type>()
            {
                return random_access_iterator<const value_type>(base());
            }
            bool    operator== (random_access_iterator const& x) { return _ptr == x.base(); }
            bool    operator!= (random_access_iterator const& x) { return _ptr != x.base(); }
            reference operator* () { return *_ptr; }
            pointer operator-> () { return &(*this); }
            random_access_iterator operator++ () { return random_access_iterator(++_ptr); }
            random_access_iterator operator++ (int) 
            { 
                random_access_iterator tmp(*this);
                ++_ptr;
                return tmp;
            }
            random_access_iterator operator-- () { return random_access_iterator(--_ptr); }
            random_access_iterator operator-- (int) 
            { 
                random_access_iterator tmp(*this);
                --_ptr;
                return tmp;
            }
            random_access_iterator& operator+= (difference_type n) 
            {
                _ptr += n;
                return *this;
            }
            random_access_iterator& operator-= (difference_type n) 
            { 
                _ptr -= n;
                return *this;
            }
            difference_type operator- (random_access_iterator const& x) { return _ptr - x.base(); }
            random_access_iterator operator+ (difference_type n) const
            {
               random_access_iterator tmp = *this;
               tmp += n;
               return tmp;
            }
            random_access_iterator operator- (difference_type n) const
            {
               random_access_iterator tmp = *this;
               tmp -= n;
               return tmp;
            }
            reference operator[] (difference_type n) { return _ptr[n]; }
            pointer base() const { return _ptr; }
        private:
            pointer _ptr;
    };

    template<class T>
    bool    operator== (random_access_iterator<T> lhs, random_access_iterator<T> rhs) { return lhs == rhs; }
    template<class T>
    bool    operator!= (random_access_iterator<T> lhs, random_access_iterator<T> rhs) { return lhs != rhs; }
    template<class T>
    bool    operator< (random_access_iterator<T> lhs, random_access_iterator<T> rhs) { return lhs.base() < rhs.base(); }
    template<class T>
    bool    operator<= (random_access_iterator<T> lhs, random_access_iterator<T> rhs) { return lhs.base() <= rhs.base(); }
    template<class T>
    bool    operator> (random_access_iterator<T> lhs, random_access_iterator<T> rhs) { return lhs.base() > rhs.base(); }
    template<class T>
    bool    operator>= (random_access_iterator<T> lhs, random_access_iterator<T> rhs) { return lhs.base() >= rhs.base(); }
    template<class T>
    random_access_iterator<T>& operator+(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> const& a) { return a + n; }
}

#endif