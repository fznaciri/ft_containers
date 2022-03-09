#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include <stdexcept>
# include "tools.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"


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
            typedef ft::random_access_iterator<value_type> iterator;
            typedef ft::random_access_iterator<const value_type> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator ;
            typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;
            typedef ptrdiff_t difference_type;
            typedef size_t size_type;

            explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _arr(NULL), _size(0), _capacity(0) {}
            explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _alloc(alloc), _arr(_alloc.allocate(n)), _size(n), _capacity(n) 
            {
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_arr + i, val);
            }
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : _alloc(alloc),
                    _arr(_alloc.allocate(abs(std::distance(first, last)))), _size(abs(std::distance(first, last))), _capacity(_size)
            {
                for (size_type i = 0; first != last; i++, first++)
                    _alloc.construct(_arr + i, *first);
            }
            vector (const vector& x)
            {
                _alloc = x.get_allocator();
                _size = x.size();
                _capacity = x.capacity();
                _arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(_arr + i, x[i]);
            }
            vector& operator= (const vector& x)
            {
                clear();
                _alloc.deallocate(_arr, _capacity);
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
                if (_arr)
                {
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(_arr + i);
                    _alloc.deallocate(_arr, _capacity);
                }
            }

            iterator begin() { return iterator(_arr); }
            const_iterator begin() const { return const_iterator(_arr); }
            iterator end() { return iterator(_arr + _size); }
            const_iterator end() const { return const_iterator(_arr + _size); }
            reverse_iterator rbegin() { return reverse_iterator(end()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
            reverse_iterator rend() { return reverse_iterator(begin()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

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
                for (size_type i = _size; i < n; i++)
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
                if (n < 0 || n >= _size)
                    throw std::out_of_range("vector");
                return _arr[n];
            }
            const_reference at (size_type n) const
            {
                if (n < 0 || n >= _size)
                    throw std::out_of_range("vector");
                return _arr[n];
            }
            reference front() { return _arr[0]; }
            const_reference front() const { return _arr[0]; }
            reference back() { return _arr[_size - 1]; }
            const_reference back() const { return _arr[_size - 1]; }

            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
                size_type tmp = std::distance(first, last);
                if (_capacity < tmp)
                {
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(_arr + i);
                    _alloc.deallocate(_arr, _capacity);
                    _capacity = _size = tmp;
                    _arr = _alloc.allocate(_capacity);
                }
                for (size_type i = 0; i < _size; i++, first++)
                    _alloc.construct(_arr + i, *first);
            }
            void assign (size_type n, const value_type& val)
            {
                reserve(n);
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_arr + i, val);
                if (n < _size)
                    for (size_type i = 0; i < _size; i++)
                         _alloc.destroy(_arr + i);
                _size = n;
            }
            void push_back (const value_type& val)
            {
                if (!_capacity)
                    reserve(1);
                else if (_size + 1 > _capacity)
                    reserve(_capacity * 2);
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
            iterator insert (iterator position, const value_type& val)
            {
                difference_type d = abs(std::distance(begin(), position)); 
                if (_size + 1 > _capacity)
                {
                    if (!_capacity)
                        reserve(1);
                    else
                        reserve(_capacity * 2);
                }
                if (_size)
                    for (size_type i = d + 1; i <= _size; i++)
                        std::swap(_arr[d], _arr[i]);
                _alloc.construct(_arr  + d, val);
                _size++;
                return iterator(_arr + d);
            }
            void insert (iterator position, size_type n, const value_type& val)
            {
                difference_type d = std::distance(begin(), position);
                if (_size + n > _capacity)
                {
                    if (_size + n > _capacity * 2)
                        reserve(_size + n);
                    else
                        reserve(_capacity * 2);
                }
                if (_size)
                    for (int i = _size - 1; i >= d; i--)
                        std::swap(_arr[i], _arr[i + n]);
                _size += n;
                for (size_type i = d; i < d + n; i++)
                    _alloc.construct(_arr + i, val);
            }	
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                difference_type d = std::distance(begin(), position);
                difference_type n = std::distance(first, last);
                if (_size + n > _capacity)
                {
                    if (_size + n > _capacity * 2)
                        reserve(_size + n);
                    else
                        reserve(_capacity * 2);
                }
                if (_size)
                    for (int i = _size - 1; i >= d; i--)
                        std::swap(_arr[i], _arr[i + n]);
                _size += n;
                for (int i = d; i < d + n; i++, ++first)
                    _alloc.construct(_arr + i, *first);
            }
            iterator erase (iterator position)
            {
                difference_type d = abs(std::distance(begin(), position));
                _size--;
                for (size_type i = d; i < _size; i++)
                    std::swap(_arr[i], _arr[i + 1]);
                _alloc.destroy((_arr - 1)  + d);
                return iterator(_arr + d);
            }
            iterator erase (iterator first, iterator last)
            {
                difference_type d = std::distance(begin(), first);
                difference_type n = std::distance(first, last);
                for (int i = d; i < d + n; i++)
                    _alloc.destroy(_arr + i);
                for (size_type i = d + n; i < _size; i++)
                    std::swap(_arr[i], _arr[i - n]);
                _size-=n;
                return iterator(_arr + d);
            }
            void clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_arr + i);
                _size = 0;
            }
            void swap (vector& x)
            {
                std::swap(_arr, x._arr);
                std::swap(_alloc, x._alloc);
                std::swap(_capacity, x._capacity);
                std::swap(_size, x._size);
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
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
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