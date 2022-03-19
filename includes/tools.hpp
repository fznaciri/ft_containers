#ifndef TOOLS_HPP
# define TOOLS_HPP
# include <type_traits>
# include <iostream>
namespace ft
{

    template<bool B, class T = void>
    struct enable_if {};
    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template<class T, class U=void()>
    struct is_integral { static const bool value = false; };

    template<class T>
    struct is_integral<bool, T> { static const bool value = true; };
    template<class T>
    struct is_integral<char, T> { static const bool value = true; };
    template<class T>
    struct is_integral<char16_t, T> { static const bool value = true; };
    template<class T>
    struct is_integral<char32_t, T> { static const bool value = true; };
    template<class T>
    struct is_integral<wchar_t, T> { static const bool value = true; };
    template<class T>
    struct is_integral<signed char, T> { static const bool value = true; };
    template<class T>
    struct is_integral<short int, T> { static const bool value = true; };
    template<class T>
    struct is_integral<int, T> { static const bool value = true; };
    template<class T>
    struct is_integral<long int, T> { static const bool value = true; };
    template<class T>
    struct is_integral<long long int, T> { static const bool value = true; };
    template<class T>
    struct is_integral<unsigned char, T> { static const bool value = true; };
    template<class T>
    struct is_integral<unsigned short int, T> { static const bool value = true; };
    template<class T>
    struct is_integral<unsigned int, T> { static const bool value = true; };
    template<class T>
    struct is_integral<unsigned long int, T> { static const bool value = true; };
    template<class T>
    struct is_integral<unsigned long long int, T> { static const bool value = true; };

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
        {
            while (first1!=last1)
            {
                if (first2==last2 || *first2<*first1) return false;
                else if (*first1<*first2) return true;
                ++first1; ++first2;
            }
            return (first2!=last2);
        }   	
    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
        while (first1!=last1)
            {
                if (first2==last2 || comp(*first2, *first1)) return false;
                else if (comp(*first1,*first2)) return true;
                ++first1; ++first2;
            }
            return (first2!=last2);
    }

    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1!=last1) {
            if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1; ++first2;
        }
        return true;
    }
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1!=last1)
        {
            if (!pred(*first1,*first2))
                return false;
            ++first1; ++first2;
        }
        return true;
    }

     template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;
        pair() : first(first_type()), second(second_type()) {}
        template<class U, class V>
        pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
        pair (const first_type& a, const second_type& b) : first(a), second(b) {}
        pair& operator= (const pair& pr)
        {
            this->first = pr.first;
            this->second = pr.second;
            return *this;
        }
    };
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }
    
    template <class T1, class T2>
    std::ostream & operator<< (std::ostream & o, pair<T1,T2> const & p)
    {
        o << p.first << " " << p.second;
        return o; 
    }
    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return (ft::pair<T1,T2>(x,y));
    }

    template <class T>
    struct node
    {
        typedef T value_type;
        typedef node node_element;
        typedef node* node_pointer;

        value_type value;
        node_pointer parent;
        node_pointer left;
        node_pointer right;
        bool black;
        bool isLeft;
        node() : value(value_type()), parent(NULL), left(NULL), right(NULL), black(false), isLeft(true) {}
        node(const value_type& v) : value(v), parent(NULL), left(NULL), right(NULL), black(false), isLeft(true) {}
        static node_pointer getSuccesser(node_pointer n)
        {
            node_pointer tmp;
            if (!n->right)
            {
                if (n == getMax(n))
                    return NULL;
                if (n->isLeft && n->parent)
                    return n->parent;
                else if (!n->isLeft && n->parent->parent)
                    return n->parent->parent;
            }
            tmp = n->right;
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }
        static node_pointer getPredecessor(node_pointer n)
        {
            node_pointer tmp = n;
            if (!n->left)
            {
                if (n == getMin(n))
                    return NULL;
                if (!n->isLeft && n->parent)
                    return n->parent;
                while (tmp->value < tmp->parent->value)
                    tmp = tmp->parent;
                // else if (n->isLeft && n->parent->parent)
                //     return n->parent->parent;
                return tmp->parent;
            }
            tmp = n->left;
            while (tmp->right)
                tmp = tmp->right;
            return tmp;
        }
        static node_pointer getMin(node_pointer n)
        {
            if (!n)
                return NULL;
            node_pointer tmp = getRoot(n);
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }
        static node_pointer getMax(node_pointer n)
        {
            if (!n)
                return NULL;
            node_pointer tmp = getRoot(n);
            while (tmp->right)
                tmp = tmp->right;
            return tmp;
        }
        static node_pointer getRoot(node_pointer n)
        {
            if (!n)
                return NULL;
            node_pointer tmp = n;
            while (tmp->parent)
                tmp = tmp->parent;
            return tmp;
        }
        static node_pointer getSebling(node_pointer n)
        {
            if (n->isLeft && n->parent && n->parent->right)
                return n->parent->right;
            else if (!n->isLeft && n->parent && n->parent->left)
                return n->parent->left;
            return NULL;
        }
    };
}

#endif