#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include <memory>
# include "tools.hpp"
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"
# include "RedBlackTree.hpp"
# include "vector.hpp"

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
                        return comp(x.first, y.first);
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
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
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
                insert(first, last);
            }
            map (const map& x) : _key_comp(x.key_comp()), _alloc(x._alloc), _tree(tree())
            {
                const_iterator it = x.begin();
                for (; it != x.end(); it++)
                    insert(*it);
            }
            ~map() {}
            map& operator= (const map& x)
            {
                clear();
                _key_comp = x.key_comp();
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
            
            // Element access
            mapped_type& operator[] (const key_type& k) 
            {
                iterator tmp = find(k);
                if (tmp == end())
                    tmp = insert(begin(), ft::make_pair(k, T()));
                return tmp->second;
            }
            
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
                    _tree.insert(ft::make_pair(first->first, first->second));
            }
            void erase (iterator position) { _tree.erase(position->first); }
            size_type erase (const key_type& k) { return _tree.erase(k); }
            void erase (iterator first, iterator last)
            {
                ft::vector <key_type> key_to_remove;
				while (first != last)
				{
					key_to_remove.push_back(first->first);
                    first++;
				}
				for (size_t i = 0; i < key_to_remove.size(); i++)
                    _tree.erase(key_to_remove[i]);
            }
            void swap (map& x)
            {
                std::swap(x._tree._endNode, _tree._endNode);
				std::swap(x._tree._root, _tree._root);
				std::swap(x._tree._allocNode, _tree._allocNode);
				std::swap(x._tree._alloc, _tree._alloc);
				std::swap(x._tree._size, _tree._size);
				
				std::swap(x._key_comp, _key_comp);
				std::swap(x._alloc, _alloc);

            }
            void clear() { _tree.clear(); }


            // Observers
            key_compare key_comp() const { return _key_comp; }
            value_compare value_comp() const { return value_compare(_key_comp); }

            // Operations
            iterator find (const key_type& k) { return _tree.find(k); }
            const_iterator find (const key_type& k) const { return _tree.find(k); }
            size_type count (const key_type& k) const { return _tree.contain(k); }
            iterator lower_bound (const key_type& k) { return _tree.lower_bound(k); }
            const_iterator lower_bound (const key_type& k) const { return _tree.lower_bound(k); }
            iterator upper_bound (const key_type& k) { return _tree.upper_bound(k); }
            const_iterator upper_bound (const key_type& k) const { return _tree.upper_bound(k); }
            ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            } 
            ft::pair<iterator,iterator>             equal_range (const key_type& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); } 

            // Allocator
            allocator_type get_allocator() const { return _alloc; }

            void    print2D()
            {
                _tree.print2D();
            }

            template <class Key_, class T_, class Compare_, class Alloc_>
			friend bool operator== ( const map<Key_,T_,Compare_,Alloc_>& lhs, const map<Key_,T_,Compare_,Alloc_>& rhs ){
				if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
					return (true);
				return (false);
			}
			
			template <class Key_, class T_, class Compare_, class Alloc_>
			friend bool operator!= ( const map<Key_,T_,Compare_,Alloc_>& lhs, const map<Key_,T_,Compare_,Alloc_>& rhs ){
				return !(lhs == rhs);
			}
			
			template <class Key_, class T_, class Compare_, class Alloc_>
			friend bool operator<  ( const map<Key_,T_,Compare_,Alloc_>& lhs, const map<Key_,T_,Compare_,Alloc_>& rhs ){
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
			
			template <class Key_, class T_, class Compare_, class Alloc_>
			friend bool operator<= ( const map<Key_,T_,Compare_,Alloc_>& lhs, const map<Key_,T_,Compare_,Alloc_>& rhs ){
				return !(ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

			}
			
			template <class Key_, class T_, class Compare_, class Alloc_>
			friend bool operator>  ( const map<Key_,T_,Compare_,Alloc_>& lhs, const map<Key_,T_,Compare_,Alloc_>& rhs ){
				return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
			}
			
			template <class Key_, class T_, class Compare_, class Alloc_>
			friend bool operator>= ( const map<Key_,T_,Compare_,Alloc_>& lhs, const map<Key_,T_,Compare_,Alloc_>& rhs ){
				return !(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
        
        private:
            key_compare _key_comp;
            allocator_type  _alloc;
            tree            _tree;
    };
    template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
		x.swap(y);
	}
}


#endif