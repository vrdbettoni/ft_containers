#include "../containers.hpp"
#include "catch.hpp"
#include <map>
#include <set>
#include <list>

#include <iostream>

#ifdef VERIFY_UNIT_TESTS
# define LIB std
#else
# define LIB ft
#endif

TEST_CASE("multimap works correctly", "[multimap]")
{
    std::list<char> l;
    char rand_char;
    int rand_int;
    LIB::multimap<char, int> mmap;

    for (int i = 0; i < 100; ++i) {
        rand_char = rand() % 93 + 33;
        rand_int = rand();
        mmap.insert(std::make_pair(rand_char, rand_int));
        l.push_back(rand_char);
    }
    CHECK( mmap.size() == l.size() );

    l.sort();
    auto it = mmap.begin();
    auto sit = l.begin();
    for (; it != mmap.end() && sit != l.end(); ++it, ++sit)
        CHECK( it->first == *sit );

    l.unique();
    for (it = mmap.begin(); it != mmap.end(); ++it) {
        auto eq = mmap.equal_range(it->first);
        it = eq.first;
        mmap.erase(++eq.first, eq.second);
    }
    CHECK( mmap.size() == l.size() );

    sit = l.begin();
    it = mmap.begin();
    for (; it != mmap.end(); ++it, ++sit)
        CHECK( it->first == *sit );

    rand_char = rand() % 93 + 33;
    for (int i = 0; i < 120; ++i)
        mmap.insert(std::make_pair(rand_char, rand()));

    auto eq = mmap.equal_range(rand_char);
    auto old_size = mmap.size();
    auto eq_range_size = std::distance(eq.first, eq.second);

    CHECK( (unsigned)eq_range_size == mmap.count(rand_char) );
    auto ret = mmap.erase(rand_char);
    CHECK( ret == (unsigned)eq_range_size );
    CHECK( mmap.size() == old_size - eq_range_size );

    CHECK( mmap.find(127) == mmap.end() );
}

TEST_CASE("multiset works correctly", "[multiset]")
{
    std::list<char> l;
    char rand_char;
    LIB::multiset<char> mset;

    for (int i = 0; i < 100; ++i) {
        rand_char = rand() % 93 + 33;
        mset.insert(rand_char);
        l.push_back(rand_char);
    }
    CHECK( mset.size() == l.size() );

    l.sort();
    auto it = mset.begin();
    auto sit = l.begin();
    for (; it != mset.end() && sit != l.end(); ++it, ++sit)
        CHECK( *it == *sit );

    l.unique();
    for (it = mset.begin(); it != mset.end(); ++it) {
        auto eq = mset.equal_range(*it);
        it = eq.first;
        mset.erase(++eq.first, eq.second);
    }
    CHECK( mset.size() == l.size() );

    sit = l.begin();
    it = mset.begin();
    for (; it != mset.end(); ++it, ++sit)
        CHECK( *it == *sit );

    rand_char = rand() % 93 + 33;
    for (int i = 0; i < 120; ++i)
        mset.insert(rand_char);

    auto eq = mset.equal_range(rand_char);
    auto old_size = mset.size();
    auto eq_range_size = std::distance(eq.first, eq.second);

    CHECK( (unsigned)eq_range_size == mset.count(rand_char) );
    auto ret = mset.erase(rand_char);
    CHECK( ret == (unsigned)eq_range_size );
    CHECK( mset.size() == old_size - eq_range_size );

    CHECK( mset.find(127) == mset.end() );
}
