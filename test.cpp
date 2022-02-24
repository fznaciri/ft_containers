#include <iostream>
#include <vector>
#include "includes/vector.hpp"

int     main()
{
    ft::vector<int> ft_v;
    std::vector<int> v;

    for(int i = 0; i < 20; i++)
    {
        ft_v.push_back(i);
        v.push_back(i);

    }
    ft::vector<int> c_ft_v(ft_v.begin(), ft_v.end());
    std::cout << *ft_v.begin() << std::endl;
    ft::vector<int>::iterator itend = ft_v.end();
    itend--;
    std::cout << *itend << std::endl;

    std::cout << *c_ft_v.begin() << std::endl;

    // std::cout << "size : " << v.size() << std::endl;
    // std::cout << "capacity : " << v.capacity() << std::endl;
    // std::cout << "max size : " << v.max_size() << std::endl;
    // std::cout << "size : " << ft_v.size() << std::endl;
    // std::cout << "capacity : " << ft_v.capacity() << std::endl;
    // std::cout << "max size : " << ft_v.max_size() << std::endl;

    // v.assign(7, 33);
    // std::cout << "size : " << v.size() << std::endl;
    // std::cout << "capacity : " << v.capacity() << std::endl;
    // std::cout << "max size : " << v.max_size() << std::endl;
    // v.resize(30);
    // for(int i = 0; i < 30; i++)
    //     std::cout << "value[" << i << "]=" << v[i] << " and address is : " << &v[i] << std::endl;
    return 0;
}
