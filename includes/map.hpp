#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include <memory>
# include "tools.hpp"
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"
# include "RedBlackTree.hpp"

namespace ft
{
    template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           >
    class map
    {
        public:
            typedef Key key_type; 
            typedef T mapped_type;
            typedef ft::pair<const key_type,mapped_type> value_type;
            typedef Compare key_compare;
            typedef class value_compare : std::binary_function<value_type,value_type,bool>
            {   
                friend class Map;
                protected:
                    Compare comp;
                public:
                    value_compare (Compare c) : comp(c) {}
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);+
                    }
            }    value_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef ft::bidirectional_iterator<value_type> iterator;
            typedef ft::bidirectional_iterator<const value_type> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const iterator> const_reverse_iterator;
            typedef ptrdiff_t difference_type;
            typedef size_t size_type;
            typedef ft::RedBlackTree<value_type, allocator_type, key_compare> tree;

            explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : _key_comp(comp), _alloc(alloc), _tree(tree()) {}
            template <class InputIterator>
            map (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : _key_comp(comp), _alloc(alloc), _tree(tree()) 
            {
                for (; first != last; first++)
                    _tree.insert(ft::make_pair(*first));
            }
            map (const map& x) : _key_comp(x.get), _alloc(x._alloc), _tree(tree())
            {
                iterator it = x.begin();
                for (; it != x.end(); it++)
                    _tree.insert(ft::make_pair(*it));
            }
            ~map() {}
            map& operator= (const map& x)
            {
                clear();
                _key_comp = x.
            }

            // Iterators
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            // Capacity
            bool empty() const;
            size_type size() const;
            size_type max_size() const;
            
            // Element access
            mapped_type& operator[] (const key_type& k);
            
            // Modifiers
            ft::pair<iterator,bool> insert (const value_type& val);	
            iterator insert (iterator position, const value_type& val);
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last);
            void erase (iterator position);
            size_type erase (const key_type& k);
            void erase (iterator first, iterator last);
            void swap (map& x);
            void clear();


            // Observers
            key_compare key_comp() const;
            value_compare value_comp() const;

            // Operations
            iterator find (const key_type& k);
            const_iterator find (const key_type& k) const;
            size_type count (const key_type& k) const;
            iterator lower_bound (const key_type& k);
            const_iterator lower_bound (const key_type& k) const;
            iterator upper_bound (const key_type& k);
            const_iterator upper_bound (const key_type& k) const;
            ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
            ft::pair<iterator,iterator>             equal_range (const key_type& k);

            // Allocator
            allocator_type get_allocator() const;
        
        
        private:
            key_compare _key_comp;
            allocator_type  _alloc;
            tree            _tree;
    };
}


#endif