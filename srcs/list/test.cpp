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
    for (int i = 0; i < 8; ++i){
        test.push_back(rand()%20);
        // if (i%2)
            // test.push_back(0);
    }
    list<int> test1;
    for (int i = 0; i < 8 ; i++)
        test1.push_back(rand()%20);
    list<int>::iterator it = test.begin();
    list<int>::iterator end = test.end();
    list<int>::iterator a = test1.begin();
    list<int>::iterator b = test1.end();
    list<int>::iterator c = it;
    
    std::cout << "First:" << std::endl;
    // test.splice(test.end(), test1);
    for (; it != end; it++){
        std::cout << *it << " ";
    }
    a = test1.begin();
    b = test1.end();
    std::cout << "\nSecond: " << std::endl;
    for (; a != b; a++)
        std::cout << *a << " ";
    std::cout << "\nResult: " << std::endl;
    // test.reverse();
    int i = 0;
    // test.resize(0);
    // test.assign(10, 1);
    test.merge(test1);
    // for (int i = 0; i < 6; i++)
    //     test.push_front(i);
    test.sort();
    for (it = test.begin(); it != end; it++){
        std::cout <<*it << " ";
    }
    // for (int i = 0; i < 5 ; i++)
    //     test1.push_back(2);
    // test.swap(test1);
    // end = test.end();
    // for (it = test.begin(); it != end; it++){
    // std::cout << *it << " ";
    // }
    std::cout << std::endl;
    // test.unique();
    // std::cout << std::endl;
    // it = test.begin();
    // for (; it != end; it++){
    //     std::cout << *it << " ";
    // }
}