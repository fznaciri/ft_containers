#include <iostream>
#include <vector>
#include "includes/vector.hpp"

int     main()
{
    std::vector<int> v(5, 5);
    ft::vector<int> ft_v(5, 5);

    // for(int i = 0; i < 20; i++)
    //     v.push_back(i);
    // for(int i = 0; i < 20; i++)
    //     std::cout << "value[" << i << "]=" << v[i] << "and address is : " << &v[i] << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "max size : " << v.max_size() << std::endl;
    std::cout << "size : " << ft_v.size() << std::endl;
    std::cout << "capacity : " << ft_v.capacity() << std::endl;
    std::cout << "max size : " << ft_v.max_size() << std::endl;

    v.assign(7, 33);
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "max size : " << v.max_size() << std::endl;
    // v.resize(30);
    // for(int i = 0; i < 30; i++)
    //     std::cout << "value[" << i << "]=" << v[i] << " and address is : " << &v[i] << std::endl;
    return 0;
}
