#ifndef TOOLS_HPP
# define TOOLS_HPP
# include <type_traits>

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
}

#endif