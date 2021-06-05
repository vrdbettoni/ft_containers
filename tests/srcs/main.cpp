#ifdef NO_UNIT_TESTS

#include "../containers.hpp"

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <chrono>

int main(void)
{
    std::cout << "no_unit_tests" << std::endl;
    return 0;
}

#else

#define CATCH_CONFIG_MAIN

#include "../containers.hpp"
#include "catch.hpp"

#endif
