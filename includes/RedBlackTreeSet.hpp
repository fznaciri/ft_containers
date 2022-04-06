#ifndef REDBLACKTREESET_HPP
# define REDBLACKTREESET_HPP
# include <iostream>
# include <memory>
# include "tools.hpp"
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"
# define COUNT 25

namespace ft {
    template <class T, class Alloc = std::allocator<T>, class Compare = std::less<T> >
    class RedBlackTreeSet
    {
        public:
            typedef T value_type;
            typedef Compare comp;
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
            typedef ft::node<value_type> node_element;
            typedef typename ft::node<value_type>::node_pointer node_pointer;
            typedef typename Alloc::template rebind<node_element>::other     allocator_node;
            
            allocator_type  _alloc;
            allocator_node  _allocNode;
            node_pointer    _root;
            node_pointer    _endNode;
            size_type       _size;
            comp            _comp;


            RedBlackTreeSet(const comp& com = comp(),
              const allocator_type& alloc = allocator_type()) : _alloc(alloc), _allocNode(allocator_node()), _root(NULL), _size(0), _comp(com)
            {
                _endNode = _allocNode.allocate(1);
                _allocNode.construct(_endNode);
                _alloc.construct(&(_endNode->value), value_type());
                _endNode->parent = NULL;
            }
            ~RedBlackTreeSet()
            {
                clear();
                _alloc.destroy(&_endNode->value);
                _allocNode.destroy(_endNode);
                _allocNode.deallocate(_endNode, 1);
            }

            ft::pair<iterator, bool> insert(const value_type& v)
            {
                node_pointer new_node = _allocNode.allocate(1);
                _allocNode.construct(new_node, node_element());
                _alloc.construct(&new_node->value, v);
                if (!_root)
                {
                    _root = new_node;
                    _root->black = true;
                    _endNode->parent = _endNode->left = _root;
                    _size++;
                    return ft::make_pair(iterator(_root, _endNode), true);
                }
                ft::pair<iterator, bool> r =  add(new_node, _root);
                 _endNode->parent = _endNode->left = _root;
                if (r.second)
                    checkColor(new_node);
                return r;
            }

            size_type    erase(value_type const& key)
            {
                node_pointer tmp = find(_root, key);
                if (tmp == _endNode)
                    return 0;
                tmp = swap_poisition(tmp);
                if (!tmp->black || _root == tmp)
                    removeBST(tmp);
                else
                {
                    fixDoubleBlack(tmp);
                    removeBST(tmp);
                }
                //balckNode(_root);
                _endNode->parent = _root;
                _endNode->left = _root;
                return 1;
            }

            void    clear()
            {
                while (_root)
                    erase(_root->value);
            }

            bool    empty() const { return _size == 0; }
            size_type    size() const { return _size; }
            size_type    max_size() const { return _allocNode.max_size(); }

            // Iterators
            iterator begin()
            {
                node_pointer n = node_element::getMin(_root);
                if (!n)
                    n = _endNode;
                return iterator(n, _endNode);
            }
            const_iterator begin() const
            {
                node_pointer n = node_element::getMin(_root);
                if (!n)
                    n = _endNode;
                return iterator(n, _endNode);
            }
            iterator end() { return iterator(_endNode, _endNode); }
            const_iterator end() const { return iterator(_endNode, _endNode); }
            reverse_iterator rbegin() { return reverse_iterator(iterator(_endNode, _endNode)); }
            const_reverse_iterator rbegin() const { return reverse_iterator(iterator(_endNode, _endNode)); }
            reverse_iterator rend()
            {
                return reverse_iterator(iterator(node_element::getMin(_root) ? node_element::getMin(_root) : _endNode , _endNode));
            }
            const_reverse_iterator rend() const 
            {
                return reverse_iterator(iterator(node_element::getMin(_root) ? node_element::getMin(_root) : _endNode , _endNode));
            }


            iterator lower_bound(value_type const& key) const { return iterator(find_lowerbound(key), _endNode); }
            iterator upper_bound(value_type const& key) const { return iterator(find_upperbound(key), _endNode); }

            iterator    find(value_type const& key) const {   return iterator(find(_root, key), _endNode); }
            size_type contain(value_type const& key) const
            {
                if (find(_root, key) == _endNode)
                    return 0;
                return 1;
            }

            void print2DUtil(node_pointer root, int space)
            {
                if (root == NULL)
                    return;
                space += COUNT;
                print2DUtil(root->right, space);
                std::cout<<std::endl;
                for (int i = COUNT; i < space; i++)
                    std::cout << " ";
                if (root->black)
                    std::cout << "\033[1;40m";
                else
                    std::cout << "\033[1;41m";
                std::cout << root->value;
                if (root->parent)
                    std::cout << " p(" << root->parent->value << ")";
                std::cout << "\033[0m" << std::endl;
                print2DUtil(root->left, space);
            }
            void print2D()
            {
                print2DUtil(_root, 0);
                std::cout << "======================================================================================" << std::endl;
            }
        private:
            ft::pair<iterator, bool> add(node_pointer newnode, node_pointer parent)
            {
                if (parent->value == newnode->value)
                {
                    _alloc.destroy(&(newnode->value));
                    _allocNode.destroy(newnode);
                    _allocNode.deallocate(newnode, 1);
                    return ft::make_pair(iterator(parent, _endNode), false);
                }
                if (_comp(parent->value, newnode->value))
                {
                    if (!parent->right)
                    {
                        parent->right = newnode;
                        newnode->parent = parent;
                        newnode->isLeft = false;
                        _size++;
                        return ft::make_pair(iterator(newnode, _endNode), true);
                    }
                    return add(newnode, parent->right);
                }
                if (!parent->left)
                {
                    parent->left = newnode;
                    newnode->parent = parent;
                    _size++;
                    return ft::make_pair(iterator(newnode, _endNode), true);
                }
                return add(newnode, parent->left);
            }

            void    checkColor(node_pointer newnode)
            {
                if (!newnode)
                    return;
                if (newnode->parent && !newnode->parent->black)
                    corectTree(newnode);
                checkColor(newnode->parent);
            }
            void corectTree(node_pointer newnode)
            {
                if (newnode->parent && newnode->parent->isLeft)
                {
                    if (newnode->parent->parent && (!newnode->parent->parent->right || (newnode->parent->parent->right && newnode->parent->parent->right->black)))
                        return rotate(newnode);
                    newnode->parent->black = true;
                    if (newnode->parent->parent != _root)
                        newnode->parent->parent->black = false;
                    newnode->parent->parent->right->black = true;
                    return;
                }
                if (newnode->parent->parent && (!newnode->parent->parent->left || (newnode->parent->parent->left && newnode->parent->parent->left->black)))
                    return rotate(newnode);
                newnode->parent->black = true;
                if (newnode->parent->parent != _root)
                    newnode->parent->parent->black = false;
                newnode->parent->parent->left->black = true;
            }

            void    rotate(node_pointer newnode)
            {
                if (newnode->isLeft)
                {
                    if (newnode->parent && newnode->parent->isLeft)
                    {
                        rightrotation(newnode->parent->parent);
                        newnode->parent->black = true;
                        newnode->parent->right->black = false;
                        return;
                    }
                    else if (newnode->parent && !newnode->parent->isLeft)
                    {
                        rightleftrotation(newnode->parent->parent);
                        newnode->black = true;
                        newnode->right->black = false;
                        newnode->left->black = false;
                        return;
                    }
                }
                else
                {
                    if (newnode->parent && !newnode->parent->isLeft)
                    {
                        leftrotation(newnode->parent->parent);
                        newnode->parent->black = true;
                        newnode->parent->left->black = false;
                        return;
                    }
                    else if (newnode->parent && !newnode->parent->isLeft)
                    {
                        leftrightrotation(newnode->parent->parent);
                        newnode->black = true;
                        newnode->right->black = false;
                        newnode->left->black = false;
                        return;
                    }
                }
            }

            void rightrotation(node_pointer newnode)
            {
                if (!newnode)
                    return;
                node_pointer tmp = newnode->left;
                newnode->left = tmp->right;
                if (newnode->left)
                {
                    newnode->left->parent = newnode;
                    newnode->left->isLeft = true;
                }
                if (!newnode->parent)
                {
                    _root = tmp;
                    _root->parent = NULL;
                    _root->black = true; 
                }
                else
                {
                    tmp->parent = newnode->parent;
                    if (newnode->isLeft)
                    {
                        tmp->isLeft = true;
                        tmp->parent->left = tmp;
                    }
                    else
                    {
                        tmp->isLeft = false;
                        tmp->parent->right = tmp;
                    }
                }
                tmp->right = newnode;
                newnode->isLeft = false;
                newnode->parent = tmp;
            }
            void leftrotation(node_pointer newnode)
            {
                if (!newnode)
                    return;
                node_pointer tmp = newnode->right;
                newnode->right = tmp->left;
                if (newnode->right)
                {
                    newnode->right->parent = newnode;
                    newnode->right->isLeft = false;
                }
                if (!newnode->parent)
                {
                    _root = tmp;
                    _root->parent = NULL;
                    _root->black = true; 
                }
                else
                {
                    tmp->parent = newnode->parent;
                    if (newnode->isLeft)
                    {
                        tmp->isLeft = true;
                        tmp->parent->left = tmp;
                    }
                    else
                    {
                        tmp->isLeft = false;
                        tmp->parent->right = tmp;
                    }
                }
                tmp->left = newnode;
                newnode->isLeft = true;
                newnode->parent = tmp; 
            }
            void leftrightrotation(node_pointer newnode)
            {
                leftrotation(newnode->left);
                rightrotation(newnode);
            }
            void rightleftrotation(node_pointer newnode)
            {
                rightrotation(newnode->right);
                leftrotation(newnode);
            }

            node_pointer    find(node_pointer root, value_type const& k) const
            {
                if (!root)
                    return _endNode;
                if (root->value == k)
                    return root;
                if (_comp(root->value, k))
                    return find(root->right, k);
                return find(root->left, k);
            }
            node_pointer    find_lowerbound(value_type const& k) const
            {
                node_pointer n = find(_root, k);
                if (n == _endNode)
                    return find_upperbound(k);
                return n;
            }
            
            node_pointer    find_upperbound(value_type const& k) const
            {
                node_pointer tmp = _root;
                while (tmp)
                {
                    if (tmp->value == k)
                        return node_element::getSuccesser(tmp);
                    if (_comp(tmp->value, k))
                    {
                        if (!tmp->right)
                            return getBigger(tmp, k);
                        tmp = tmp->right;
                    }
                    else
                    {
                        if (!tmp->left)
                            return getBigger(tmp, k);
                        tmp = tmp->left;
                    }
                }
                return tmp;
            }

            node_pointer    getBigger(node_pointer node, value_type k) const
            {
                node_pointer tmp = node;
                if (k < tmp->value)
                    return tmp;
                while (tmp)
                {
                    if (tmp->isLeft)
                        return tmp->parent;
                    if (_comp(tmp->value, k))
                        return tmp;
                    tmp = tmp->parent;
                }
                return _endNode;
            }

            void    fixDoubleBlack(node_pointer db)
        
            {
                node_pointer s;
                while (db)
                {
                    
                    s = node_element::getSebling(db);
                    if (!db->parent)
                        return ;
                    if ((!s || (s && s->black && (!s->right || (s->right && s->right->black))
                        && (!s->left || (s->left && s->left->black)))))
                    {
                        if (s)
                            s->black = false;
                        if (!db->parent->black)
                        {
                            db->parent->black = true;
                            return;
                        }
                        else  
                            return fixDoubleBlack(db->parent);
                    }
                    else if (s && !s->black)
                    {
                        std::swap(s->black, db->parent->black);
                        if (db->isLeft)
                            leftrotation(db->parent);
                        else
                            rightrotation(db->parent);
                        return fixDoubleBlack(db);
                    }
                    else if (!s || s->black)
                    {
                        if (db->isLeft && (((!s->left || (s->left && s->left->black)) && (s->right && !s->right->black)) || (s->right && !s->right->black)))
                        {
                            std::swap(s->black, db->black);
                            leftrotation(db->parent);
                            s->right->black = true;
                            return;
                        }
                        else if (!db->isLeft && (s->left && !s->left->black) && (!s->right || (s->right && s->right->black)))
                        {
                            std::swap(s->black, db->black);
                            rightrotation(db->parent);
                            return;
                        }
                        if (db->isLeft && (s->left && !s->left->black))
                        {
                            std::swap(s->black, s->left->black);
                            rightrotation(s);
                        }
                        else if (!db->isLeft && (s->right && !s->right->black))
                        {
                            std::swap(s->black, s->right->black);
                            leftrotation(s);
                        }
                    }
                }
            }
            void    removeBST(node_pointer n)
            {
                if (!n)
                    return ;
                if (!n->left && !n->right)
                {
                    if (n->isLeft && n != _root)
                        n->parent->left = NULL;
                    else if (!n->isLeft && n != _root)
                        n->parent->right = NULL;
                    if (n == _root)
                        _root = NULL;
                    _alloc.destroy(&(n->value));
                    _allocNode.destroy(n);
                    _allocNode.deallocate(n, 1);
                    _size--;
                    return ;
                }
            }
            node_pointer    swap_poisition(node_pointer n)
            {
                node_pointer tmp = NULL;
                if (!n)
                    return NULL;
                if (!n->left && !n->right)
                    return n;
                if (n->right)
                {
                    tmp = n->right;
                    while (tmp->left)
                        tmp = tmp->left;
                }
                else if (n->left)
                {
                    tmp = n->left;
                    while (tmp->right)
                        tmp = tmp->right;
                }
                value_type tmp1(n->value);
                _alloc.construct(&n->value, tmp->value);
                _alloc.construct(&tmp->value, tmp1);
                if (tmp->right || tmp->left)
                   return swap_poisition(tmp);
                return tmp;
            }     
    };
}

#endif