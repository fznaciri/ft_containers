#include <iostream>
#include <vector>
#include "includes/vector.hpp"
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>
#include "includes/RedBlackTree.hpp"

# define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
# define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return(msecs_time);
}

int     main()
{
   ft::RedBlackTree<ft::pair<int, int> > tree;
   tree.insert(ft::make_pair(10, 0));
   tree.insert(ft::make_pair(20, 0));
   tree.insert(ft::make_pair(30, 0));
   tree.print2D();
   //tree.insert(ft::make_pair(10, 0));
   return 0;
}
