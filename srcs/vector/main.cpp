#include "vector.hpp"
#include <vector>
#include <iostream>

using namespace ft;
int main()
{
    vector<int> v;

    v.reserve(10);
    std::cout << "first:" << std::endl;
    for(int i = 0; i < 10; i++)
        v.push_back(i);

    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    
    vector<int>paolo_le_con(v);

    std::cout << "\nSecond:" << std::endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    v.clear();
    std::cout << "Third:" << std::endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    v.assign(5, 1);
    v.push_back(1);
    v.resize(5);
    v.resize(10);

    std::cout << "Fourth:" << std::endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    
    std::cout << "\nTest Iterator:\n";
    vector<int>::iterator er = paolo_le_con.begin();
    er++;
    paolo_le_con.erase(er);
    for (vector<int>::iterator it = paolo_le_con.begin(); it != paolo_le_con.end(); ++it)
        std::cout << *it << " ";

}