#include "node.hpp"
#include <iostream>

using namespace ft;
int main()
{
    Node<int> node(9);
    Node<int> ode(7);
    // int a = node.content();
    std::cout << node.content();
    node.addAfter(&ode);

    Node<int> test = *(node.next());    
    std::cout << test.content();
    std::cout << *test;
}