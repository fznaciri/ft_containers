#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP
# include <iostream>
# include <memory>
# include "tools.hpp"
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"
# define COUNT 25

namespace ft
{
    template <class T, class Alloc = std::allocator<T>, class Compare = std::less<typename T::first_type> >
    class RedBlackTree
    {
        public:
            typedef typename T::first_type key_type; 
            typedef typename T::second_type mapped_type;
            typedef ft::pair<const key_type,mapped_type> value_type;
            typedef Compare comp;
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
            typedef typename allocator_type::template rebind<ft::node<value_type> >::other allocator_node;
            typedef typename ft::node<value_type>::node_pointer node_pointer;
            typedef ft::node<value_type> node_element;

            RedBlackTree(const comp& com = comp(),
              const allocator_type& alloc = allocator_type()) : _alloc(alloc), _allocNode(allocator_node()), _root(NULL), _size(0), _comp(com)
            {
                _endNode = _allocNode.allocate(1);
                _allocNode.construct(_endNode);
                _alloc.construct(&(_endNode->value), value_type());
                _endNode->parent = NULL;
            }
            ~RedBlackTree();

            ft::pair<bool, bool> insert(const value_type& v)
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
                    return ft::make_pair(true, true);
                }
                ft::pair<bool, bool> r =  add(new_node, _root);
                checkColor(new_node);
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
            ft::pair<bool, bool> add(node_pointer newnode, node_pointer parent)
            {
                if (parent->value.first == newnode->value.first)
                {
                    _alloc.destroy(&(newnode->value));
                    _allocNode.destroy(newnode);
                    _allocNode.deallocate(newnode, 1);
                    return ft::make_pair(false, false);
                }
                if (_comp(parent->value.first, newnode->value.first))
                {
                    if (!parent->right)
                    {
                        parent->right = newnode;
                        newnode->parent = parent;
                        newnode->isLeft = false;
                        _size++;
                        return ft::make_pair(true, true);
                    }
                    return add(newnode, parent->right);
                }
                if (!parent->left)
                {
                    parent->left = newnode;
                    newnode->parent = parent;
                    _size++;
                    return ft::make_pair(true, true);
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
                    if (newnode->parent->parent && (!newnode->parent->parent->right || (newnode->parent->parent->right && newnode->parent->parent->right->balck)))
                        return rotate(newnode);
                    newnode->parent->balck = true;
                    if (newnode->parent->parent != _root)
                        newnode->parent->parent->balck = false;
                    newnode->parent->parent->right->black = true;
                    return;
                }
                if (newnode->parent->parent && (!newnode->parent->parent->left || (newnode->parent->parent->left && newnode->parent->parent->left->balck)))
                    return rotate(newnode);
                newnode->parent->balck = true;
                if (newnode->parent->parent != _root)
                    newnode->parent->parent->balck = false;
                newnode->parent->parent->left->black = true;
            }

            void    rotate(node_pointer newnode)
            {
                if (newnode->isLeft)
                {
                    if (newnode->parent && newnode->parent->isLeft)
                    {
                        rightrotation(newnode->parent->parent);
                        newnode->parent->balck = true;
                        newnode->parent->right->black = false;
                        return;
                    }
                    else if (newnode->parent && !newnode->parent->isLeft)
                    {
                        rightleftrotation(newnode->parent->parent);
                        newnode->balck = true;
                        newnode->right = false;
                        newnode->left->black = false;
                        return;
                    }
                }
                else
                {
                    if (newnode->parent && !newnode->parent->isLeft)
                    {
                        leftrotation(newnode->parent->parent);
                        newnode->parent->balck = true;
                        newnode->parent->left->black = false;
                        return;
                    }
                    else if (newnode->parent && !newnode->parent->isLeft)
                    {
                        leftrightrotation(newnode->parent->parent);
                        newnode->balck = true;
                        newnode->right = false;
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
                    newnode->left->isleft = true;
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
                    if (newnode->isleft)
                    {
                        tmp->isleft = true;
                        tmp->parent->left = tmp;
                    }
                    else
                    {
                        tmp->isleft = false;
                        tmp->parent->right = tmp;
                    }
                }
                tmp->right = newnode;
                newnode->isleft = false;
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
                    newnode->right->isleft = false;
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
                    if (newnode->isleft)
                    {
                        tmp->isleft = true;
                        tmp->parent->left = tmp;
                    }
                    else
                    {
                        tmp->isleft = false;
                        tmp->parent->right = tmp;
                    }
                }
                tmp->left = newnode;
                newnode->isleft = true;
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


            allocator_type  _alloc;
            allocator_node  _allocNode;
            node_pointer    _root;
            node_pointer    _endNode;
            size_type       _size;
            comp            _comp;
    };
    
} // namespace ft


#endif