#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP
# include "tools.hpp"

namespace ft
{
    template<class T>
    class bidirectional_iterator
    {
        
        public:
            typedef T value_type;
            typedef value_type& reference;
            typedef value_type* pointer;
            typedef ft::node<value_type> node_element;
            typedef node_element* node_pointer;

            bidirectional_iterator() : _ptr(NULL), _endNode(NULL) {}
            bidirectional_iterator(node_pointer ptr, node_pointer endNode) : _ptr(ptr), _endNode(endNode) {}
            bidirectional_iterator(bidirectional_iterator const& it) : _ptr(it._ptr), _endNode(it._endNode) {}
            bidirectional_iterator& operator= (bidirectional_iterator const& it)
            {
                _ptr = it._ptr;
                _endNode = it._endNode;
                return *this;
            }

            ~bidirectional_iterator() {}

            operator bidirectional_iterator<const value_type> ()
            {
                return bidirectional_iterator<const value_type>(_ptr, _endNode);
            }

            reference operator*() const
            {
                return _ptr->value;
            } 
            pointer operator->()
            {
                return &(operator*());
            }
            bidirectional_iterator operator++()
            {
            //    if (this->_ptr->parent && this->_ptr->parent == this->_ptr->left)
            //         this->_ptr = this->_ptr->right;
            //     else if (this->_ptr->parent && this->_ptr->isleft && (!this->_ptr->left && !this->_ptr->right))
            //         this->_ptr = this->_ptr->parent;
            //     else if (!this->_ptr->isleft && !this->_ptr->right)
            //         this->_ptr = ft::node::getParentPredecessor(this->_ptr);
            //     else
            //     {
            //         if (!ft::node::getSuccessor(this->_ptr))
            //             this->_ptr = this->_ptr->parent;
            //         else
            //             this->_ptr = ft::node::getSuccessor(this->_ptr);
            //     }
                _ptr = ft::node<value_type>::getSuccesser(_ptr);
                if (!_ptr)
                    this->_ptr = this->_endNode;
                return bidirectional_iterator(this->_ptr, this->_endNode);
            }
            bidirectional_iterator operator++(int)
            {
               bidirectional_iterator tmp = *this;
               ++(*this);
               return tmp;
            }
            bidirectional_iterator operator--()
            {
                if (_ptr == _endNode)
                    _ptr = ft::node<value_type>::getMax(_ptr->parent);
                else
                    _ptr = ft::node<value_type>::getPredecessor(_ptr);
                if (!_ptr)
                    this->_ptr = this->_endNode;
                return bidirectional_iterator(this->_ptr, this->_endNode);
            }
            bidirectional_iterator operator--(int)
            {
               bidirectional_iterator tmp = *this;
               --(*this);
               return tmp;
            }
            template <class U>
            friend bool operator== (const bidirectional_iterator<U>& lhs, const bidirectional_iterator<U>& rhs)
            {
                return lhs._ptr == rhs._ptr;
            }
            template <class U>
            friend bool operator!= (const bidirectional_iterator<U>& lhs, const bidirectional_iterator<U>& rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
        private:
            node_pointer _ptr;
            node_pointer _endNode;
    };
} // namespace ft


#endif