#ifndef SET_HPP
# define SET_HPP
# include <iostream>
# include <memory>
# include "tools.hpp"
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"
# include "RedBlackTreeSet.hpp"
# include "vector.hpp"


namespace ft
{
    template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class set
    {
        public:
            typedef T key_type;
            typedef T value_type; 
            typedef Compare key_compare; 
            typedef Compare value_compare; 
            typedef Alloc allocator_type; 
            typedef typename allocator_type::reference reference; 
            typedef typename allocator_type::const_reference const_reference; 
            typedef typename allocator_type::pointer pointer; 
            typedef typename allocator_type::const_pointer const_pointer; 
            typedef ft::bidirectional_iterator<value_type> iterator; 
            typedef ft::bidirectional_iterator<const value_type> const_iterator; 
            typedef ft::reverse_iterator<iterator> reverse_iterator; 
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef ptrdiff_t difference_type; 
            typedef size_t size_type;
            typedef ft::RedBlackTreeSet<value_type, allocator_type, Compare> tree;


            explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _tree(tree()) {}
            template <class InputIterator>
            set (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type())  : _alloc(alloc), _comp(comp), _tree(tree())
            {
                insert(first, last);
            }
            set (const set& x) : _alloc(x.get_allocator()), _comp(x.key_comp()), _tree(tree())
            {
                const_iterator it = x.begin();
                for (; it != x.end(); it++)
                    insert(*it);
            }
            ~set() {}
            set& operator= (const set& x)
            {
                clear();
                _comp = x.key_comp();
                _alloc = x.get_allocator();
                const_iterator it = x.begin();
                for (; it != x.end(); it++)
                    insert(*it);
                return *this;
            }
            
            // Iterators
            iterator begin() { return _tree.begin(); }
            const_iterator begin() const { return _tree.begin(); }
            iterator end() { return _tree.end(); }
            const_iterator end() const { return _tree.end(); }
            reverse_iterator rbegin() { return _tree.rbegin(); }
            const_reverse_iterator rbegin() const { return _tree.rbegin(); }
            reverse_iterator rend() { return _tree.rend(); }
            const_reverse_iterator rend() const { return _tree.rend(); }

            // Capacity
            bool empty() const { return _tree.empty(); }
            size_type size() const { return _tree.size(); }
            size_type max_size() const { return _tree.max_size(); }

            // Modifiers
            ft::pair<iterator,bool> insert (const value_type& val) { return _tree.insert(val); }
            iterator insert (iterator position, const value_type& val)
            {
                (void)position;
                return _tree.insert(val).first;
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                for (;first != last; first++)
                    _tree.insert(*first);
            }
            void erase (iterator position) { _tree.erase(*position); }
            size_type erase (const value_type& val) { return _tree.erase(val); }
            void erase (iterator first, iterator last)
            {
                ft::vector <key_type> key_to_remove;
				while (first != last)
				{
					key_to_remove.push_back(*first);
                    first++;
				}
				for (size_t i = 0; i < key_to_remove.size(); i++)
                    _tree.erase(key_to_remove[i]);
            }
            void swap (set& x)
            {
                std::swap(x._tree._endNode, _tree._endNode);
				std::swap(x._tree._root, _tree._root);
				std::swap(x._tree._allocNode, _tree._allocNode);
				std::swap(x._tree._alloc, _tree._alloc);
				std::swap(x._tree._size, _tree._size);
				
				std::swap(x._comp, _comp);
				std::swap(x._alloc, _alloc);
            }
            void clear() { _tree.clear(); }

            // Observers
            key_compare key_comp() const { return _comp; }
            value_compare value_comp() const { return _comp; }

            // Operations
            iterator find (const value_type& val) const { return _tree.find(val); }
            size_type count (const value_type& val) const { return _tree.contain(val); }
            iterator lower_bound (const value_type& val) const { return _tree.lower_bound(val); }
            iterator upper_bound (const value_type& val) const { return _tree.upper_bound(val); }
            ft::pair<iterator,iterator> equal_range (const value_type& val) const
            {
                return ft::make_pair(lower_bound(val), upper_bound(val));
            }

            // Allocator
            allocator_type get_allocator() const { return _alloc; }

            template <class T_, class Compare_, class Alloc_>
			friend bool operator== ( const set<T_,Compare_,Alloc_>& lhs, const set<T_,Compare_,Alloc_>& rhs ){
				if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
					return (true);
				return (false);
			}
			
			template <class T_, class Compare_, class Alloc_>
			friend bool operator!= ( const set<T_,Compare_,Alloc_>& lhs, const set<T_,Compare_,Alloc_>& rhs ){
				return !(lhs == rhs);
			}
			
			template <class T_, class Compare_, class Alloc_>
			friend bool operator<  ( const set<T_,Compare_,Alloc_>& lhs, const set<T_,Compare_,Alloc_>& rhs ){
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
			
			template <class T_, class Compare_, class Alloc_>
			friend bool operator<= ( const set<T_,Compare_,Alloc_>& lhs, const set<T_,Compare_,Alloc_>& rhs ){
				return !(ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

			}
			
			template <class T_, class Compare_, class Alloc_>
			friend bool operator>  ( const set<T_,Compare_,Alloc_>& lhs, const set<T_,Compare_,Alloc_>& rhs ){
				return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
			}
			
			template <class T_, class Compare_, class Alloc_>
			friend bool operator>= ( const set<T_,Compare_,Alloc_>& lhs, const set<T_,Compare_,Alloc_>& rhs ){
				return !(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}

        private:
            allocator_type _alloc;
            key_compare _comp;
            tree _tree;

    };
};



#endif