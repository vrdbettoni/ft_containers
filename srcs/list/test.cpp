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
    for (int i = 0; i < 10; ++i){
        test.push_back(0);
        if (i%2)
            test.push_back(0);
    }
    list<int> test1;
    for (int i = 1; i < 7 ; i++)
        test1.push_back(i);
    list<int>::iterator it = test.begin();
    list<int>::iterator end = test.end();
    list<int>::iterator a = test1.begin();
    list<int>::iterator b = test1.end();
    list<int>::iterator c = it;
    c++;
    a++;a++;
    std::cout << "First:" << std::endl;
    // test.splice(c, test1);
    for (; it != end; it++){
        std::cout << *it << " ";
    }
    a = test1.begin();
    b = test1.end();
    std::cout << "\nSecond: " << std::endl;
    for (; a != b; a++)
        std::cout << *a << " ";
    std::cout << "\nReverse: " << std::endl;
    test.reverse();
    int i = 0;
    for (it = test.begin(); it != end; it++){
        i++;
        if (i == 30){
            std::cout << std::endl;
            break;
        }
        std::cout <<*it << " ";
    }
    std::cout << std::endl;
    // test.unique();
    // std::cout << std::endl;
    // it = test.begin();
    // for (; it != end; it++){
    //     std::cout << *it << " ";
    // }
}