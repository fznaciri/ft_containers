#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include <stdexcept>
# include "tools.hpp"


namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class vector {
        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type*  const_pointer;
            // typedef iterator ft::random access iterator<value_type>;
            // typedef const_iterator const iterator;
            // typedef reverse_iterator ft::reverse_iterator<ft::random access iterator<value_type>>;
            // typedef const_reverse_iterator reverse_iterator;
            typedef difference_type ptrdiff_t;
            typedef size_t size_type;

            explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _arr(NULL), _size(0), _capacity(0) {}
            explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _alloc(alloc), _arr(_alloc.allocate(n)), _size(n), _capacity(n) 
            {
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_arr + i, val);
            }
            // template <class InputIterator>
            // vector (InputIterator first, InputIterator last,
            //         const allocator_type& alloc = allocator_type(), );	
            vector (const vector& x)
            {
                *this = x;
            }
            vector& operator= (const vector& x)
            {
                clear();
                _alloc.deallocate(_arr);
                _alloc = x.get_allocator();
                _size = x.size();
                _capacity = x.capacity();
                _arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(_arr + i, x[i]);
                return *this;
            }
            ~vector() 
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_arr + i);
                _alloc.deallocate(_arr, _capacity);
            }

            // iterator begin() { return iterator(_arr); }
            // const_iterator begin() const { return const_iterator(_arr); }
            // iterator end() { return iterator(_arr + _size); }
            // const_iterator end() const { return const_iterator(_arr + _size); }
            // reverse_iterator rbegin() { return reverse_iterator(end()); }
            // const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
            // reverse_iterator rend() { return reverse_iterator(begin()); }
            // const_reverse_iterator rend() const { return reverse_iterator(begin()); }

            size_type size() const { return _size; }
            size_type max_size() const { return _alloc.max_size(); }
            size_type capacity() const { return _capacity; }
            bool empty() const { return _size == 0; }
            void resize (size_type n, value_type val = value_type())
            {
                reserve(n);
                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++)
                        _alloc.destroy(_arr + i);
                    _size = n;
                    return ;
                }
                for (size_type i = _size - 1; i < n; i++)
                     _alloc.construct(_arr + i, val);
                _size = n;
            }
            void reserve (size_type n)
            {
                pointer tmp_arr;
                if (n > max_size())
                    throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
                if (n > _capacity)
                {
                    tmp_arr = _alloc.allocate(n);
                    for (size_type i = 0; i < _size; i++)
                    {
                        _alloc.construct(tmp_arr + i, _arr[i]);
                        _alloc.destroy(this->_arr + i);
                    }
                    _alloc.deallocate(_arr, _capacity);
                    _capacity = n;
                    _arr = tmp_arr;
                }
            }

            reference operator[] (size_type n) { return _arr[n]; }
            const_reference operator[] (size_type n) const { return _arr[n]; }
            reference at (size_type n)
            {
                if (n < 0 && n >= _size)
                    throw std::out_of_range("vector");
                return _arr[n];
            }
            const_reference at (size_type n) const
            {
                if (n < 0 && n >= _size)
                    throw std::out_of_range("vector");
                return _arr[n];
            }
            reference front() { return _arr[0]; }
            const_reference front() const { return _arr[0]; }
            reference back() { return _arr[_size - 1]; }
            const_reference back() const { return _arr[_size - 1]; }

            // template <class InputIterator>
            // void assign (InputIterator first, InputIterator last);	
            void assign (size_type n, const value_type& val)
            {
                reserve(n);
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_arr + i, val);
                if (n < _size)
                    for (; i < _size; i++)
                         _alloc.destroy(_arr + i);
                _size = n;
            }
            void push_back (const value_type& val)
            {
                reserve(_size + 1);
                _alloc.construct(_arr + _size, val);
                _size++;
            }
            void pop_back()
            {
                if (!_size)
                    return;
                _alloc.destroy(_arr + _size - 1);
                _size--;
            }
            // iterator insert (iterator position, const value_type& val);
            // void insert (iterator position, size_type n, const value_type& val);	
            // template <class InputIterator>
            // void insert (iterator position, InputIterator first, InputIterator last);
            // iterator erase (iterator position);
            // iterator erase (iterator first, iterator last); 
            void clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_arr + i);
                _size = 0;
            }
            void swap (vector& x)
            {
                std::swap(_arr, x._arr);
                std::swap(_alloc, x._alloc());
                std::swap(_capacity, x.capacity());
                std::swap(_size, x.size());
            }

            allocator_type get_allocator() const { return _alloc; }

        private:
            allocator_type   _alloc;
            pointer _arr;
            size_type   _size;
            size_type   _capacity;


    };
    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ((lhs < rhs) || (lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs <= lhs) ; }
    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

}
#endif