#include <iostream>
#include <vector>
#include "includes/vector.hpp"
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>
#include "includes/map.hpp"
#include <map>

# define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
# define TIME_FAC 20 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return(msecs_time);
}

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

int     main()
{
    ft::map<int, int> ft_m;

    for (int i = 0; i < 20; i++)
        ft_m.insert(ft::make_pair(i, i));
    ft_m.print2D();
    ft::map<int, int>::iterator it = ft_m.begin();
    for (; it != ft_m.end(); ++it)
        std::cout << it->first << std::endl;
    return 0;
}