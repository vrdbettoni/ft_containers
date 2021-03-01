#include "list_node.hpp"
#include "list_iterator.hpp"
#include "list.hpp"
#include <iostream>
#include <list>
#include <string.h>

using namespace ft;

bool pair_digit (const int& value) { return (value %2 == 0); }
bool same (int first, int second)
{ return ( int(first)==int(second) ); }

int main()
{
    list<int> test;
    test.push_back(4);
    test.push_back(1);
    test.push_back(2);
    test.push_back(4);
    test.push_back(4);
    test.push_back(3);
    test.push_back(4);
    test.push_back(5);
    test.push_back(4);

    list<int>::iterator it = test.begin();
    list<int>::iterator end = test.end();
    // list<int>::const_iterator cit = test.cbegin();
    // list<int>::const_iterator cend = test.cend();
    // list<int>::reverse_iterator rit = test.rbegin();
    // list<int>::reverse_iterator rend = test.rend();
    // list<int>::const_reverse_iterator crit = test.crbegin();
    // list<int>::const_reverse_iterator crend = test.crend();
    list<int>::iterator a;
    for (; it != end; it++){
        if (*it == 5)
            a = it;
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    test.unique();
    // test.pop_front();
    // test.pop_back();
    it = test.begin();

    test.erase(a);
    for (; it != end; it++){
        std::cout << *it << " ";
    }
    // std::cout << std::endl;
    // for (; cit != cend; cit++){
    //     std::cout << *cit << " ";
    // }
    // std::cout << std::endl;
    // for (; rit != rend; rit++){
    //     std::cout << *rit << " ";
    // }
    // std::cout << std::endl;
    // for (; crit != crend; crit++){
    //     std::cout << *crit << " ";
    // }
}