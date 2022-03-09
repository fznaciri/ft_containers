#ifndef REVERSE_ITERATOR
# define REVERSE_ITERATOR
# include <iostream>
# include "iterator_traits.hpp"

namespace ft 
{
    template <class Iterator> 
    class reverse_iterator
    {
        public:
            typedef Iterator iterator_type; 
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;

        reverse_iterator() {}	
        
        explicit reverse_iterator (iterator_type it):  _iter(it) { }	
        
        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it) : _iter(rev_it.base()) { }

        reverse_iterator& operator= (const reverse_iterator& rev_it)
        {
            _iter = rev_it.base();
            return *this;
        }
        // operator reverse_iterator< const iterator_type> ()
        // {
        //     return reverse_iterator< const iterator_type>(_iter);
        // }

        iterator_type base() const { return _iter; }
        
        reference operator*() const 
        {
            iterator_type tmp = _iter;
            --tmp;
            return *tmp;
        }


        reverse_iterator operator+ (difference_type n) const
        {
            return reverse_iterator(_iter - n);
        }

        reverse_iterator& operator++()
        {
            --_iter;
            return *this;
        }

        reverse_iterator  operator++(int)
        {
            reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reverse_iterator& operator+= (difference_type n)
        {
            _iter -= n;
            return *this;
        }

        reverse_iterator operator- (difference_type n) const { return reverse_iterator(_iter + n); }
        reverse_iterator operator--()
        {
            ++_iter;
            return *this;
        }

        reverse_iterator  operator--(int)
        {
            reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        reverse_iterator& operator-= (difference_type n)
        {
            _iter += n;
            return *this;
        }

        pointer operator->() const {
            return &(operator*());
        }

        reference operator[] (difference_type n) const { return _iter[-n-1]; }
        private:
            iterator_type _iter;
    };
    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() == rhs.base(); }
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() != rhs.base(); }
    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() > rhs.base(); }
    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() >= rhs.base(); }
    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() < rhs.base(); }
    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() <= rhs.base(); }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return rev_it + n; }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return rhs.base() - lhs.base(); }
}


#endif