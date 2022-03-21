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
//    tree.print2D();
   tree.insert(ft::make_pair(20, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(30, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(40, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(50, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(0, 5));
//    tree.print2D();
   tree.insert(ft::make_pair(60, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(70, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(80, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(90, 0));
//    tree.print2D();
   tree.insert(ft::make_pair(100, 0));
   tree.print2D();

    ft::RedBlackTree<ft::pair<int, int> >::iterator it = tree.begin();
    ft::RedBlackTree<ft::pair<int, int> >::iterator itend = tree.end();
    
    for (; it != itend; it++)
        std::cout << it->first << " " << it->second << std::endl;
   //  ft::RedBlackTree<ft::pair<int, int> >::iterator ifind = tree.find(80);
   //  ft::RedBlackTree<ft::pair<int, int> >::iterator ifind1 = tree.find(88);
   //  std::cout << ifind->first << " " << ifind->second << std::endl;
   //  std::cout << ifind1->first << " " << ifind1->second << std::endl;
   //  std::cout << tree.contain(80) << std::endl;
   //  std::cout << tree.contain(88) << std::endl;
    // std::cout << "========================================================" << std::endl;
    // ft::RedBlackTree<ft::pair<int, int> >::iterator it1 = tree.begin();
    // itend--;
    // std::cout << itend->first << " " << itend->second << std::endl;
    // itend--;
    // std::cout << itend->first << " " << itend->second << std::endl;
    // itend--;
    // std::cout << itend->first << " " << itend->second << std::endl;
    // itend--;
    // std::cout << itend->first << " " << itend->second << std::endl;
    // itend--;
    // std::cout << itend->first << " " << itend->second << std::endl;
    // itend--;
    // std::cout << itend->first << " " << itend->second << std::endl;
    // itend--;
    // std::cout << itend->first << " " << itend->second << std::endl;
    // for (; itend != it1; itend--)
    //     std::cout << itend->first << " " << itend->second << std::endl;
    std::cout << "===========================================================" << std::endl << "55" << std::endl;
    ft::RedBlackTree<ft::pair<int, int> >::iterator up = tree.upper_bound(55);
    ft::RedBlackTree<ft::pair<int, int> >::iterator lo = tree.lower_bound(55);
    std::cout << "upper bound  " << up->first << " " << up->second << std::endl;
    std::cout << "lower bound  " << lo->first << " " << lo->second << std::endl;
    std::cout << "===========================================================" << std::endl << "80" << std::endl;
    up = tree.upper_bound(80);
    lo = tree.lower_bound(80);
    std::cout << "upper bound  " << up->first << " " << up->second << std::endl;
    std::cout << "lower bound  " << lo->first << " " << lo->second << std::endl;
    std::cout << "===========================================================" << std::endl << "90" << std::endl;
    up = tree.upper_bound(90);
    lo = tree.lower_bound(90);
    std::cout << "upper bound  " << up->first << " " << up->second << std::endl;
    std::cout << "lower bound  " << lo->first << " " << lo->second << std::endl;
    std::cout << "===========================================================" << std::endl << "88" << std::endl;
    up = tree.upper_bound(88);
    lo = tree.lower_bound(88);
    std::cout << "upper bound  " << up->first << " " << up->second << std::endl;
    std::cout << "lower bound  " << lo->first << " " << lo->second << std::endl;
    std::cout << "===========================================================" << std::endl << "40" << std::endl;
    up = tree.upper_bound(40);
    lo = tree.lower_bound(40);
    std::cout << "upper bound  " << up->first << " " << up->second << std::endl;
    std::cout << "lower bound  " << lo->first << " " << lo->second << std::endl;

    std::cout << "is empty : " << tree.empty() << std::endl;
    std::cout << "is size : " << tree.size() << std::endl;
    std::cout << "is max_size : " << tree.max_size() << std::endl;
    //tree.insert(ft::make_pair(10, 0));
   return 0;
}
