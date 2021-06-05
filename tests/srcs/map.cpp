#include "../containers.hpp"
#include "catch.hpp"
#include <map>
#include <array>
#include <list>
#include <string>

#ifdef VERIFY_UNIT_TESTS
# define LIB std
#else
# define LIB ft
#endif

/* CONSTRUCTION */
TEST_CASE("map constructors return the requested map", "[map][basics]")
{
    SECTION("declaration creates an empty map") {
        LIB::map<int, int> map;
        CHECK( map.empty() );
        CHECK( map.size() == 0 );
    }
    SECTION("range constructor creates a map filled with the elements of the passed range") {
        std::map<char, int> stl_map;
        for (int i = 0; i < 25; ++i)
            stl_map[rand() % 93 + 33] = rand();
        LIB::map<char, int> my_map (stl_map.begin(), stl_map.end());

        CHECK( stl_map.size() == my_map.size() );
        CHECK_FALSE( my_map.empty() );

        auto stl_it = stl_map.begin();
        auto my_it = my_map.begin();
        for (; stl_it != stl_map.end(); ++my_it, ++stl_it)
            CHECK( *my_it == *stl_it );
    }
    SECTION("copy constructor constructs an exact copy of a given map") {
        LIB::map<char, int> my_map1;
        for (int i = 0; i < 25; ++i)
            my_map1[rand() % 93 + 33] = rand();
        LIB::map<char, int> my_map2 (my_map1);

        CHECK_FALSE( my_map2.empty() );
        CHECK( my_map2.size() == my_map1.size() );

        auto it1 = my_map1.begin();
        auto it2 = my_map2.begin();
        for (; it1 != my_map1.end(); ++it1, ++it2)
            CHECK( *it1 == *it2 );
        my_map1.begin()->second = my_map2.begin()->second - 10;
        (--my_map1.end())->second = (--my_map2.end())->second - 1029;
        CHECK(( my_map1.begin()->second != my_map2.begin()->second ));
        CHECK(( (--my_map1.end())->second != (--my_map2.end())->second ));
    }
}

TEST_CASE("maps can be assigned using the = operator", "[map][operators]")
{
    LIB::map<char, int> my_map1;
    for (int i = 0; i < 10; ++i)
        my_map1[rand() % 93 + 33] = rand() % 10000;

    LIB::map<char, int> my_map2 = my_map1;
    CHECK( my_map2.size() == my_map1.size() );

    // assigned maps contain the same values
    auto it1 = my_map1.begin();
    auto it2 = my_map2.begin();
    for (; it1 != my_map1.end(); ++it1, ++it2)
        CHECK( *it1 == *it2 );

    // values are copied when maps are assigned
    my_map1.begin()->second -= 1;
    (--my_map1.end())->second += 1;
    CHECK(( my_map1.begin()->second != my_map2.begin()->second ));
    CHECK(( (--my_map1.end())->second != (--my_map2.end())->second ));
}

TEST_CASE("maps contain no duplicates", "[map][basics]")
{
    LIB::map<int, int> map;
    std::list<int> list;

    for (int i = 0; i < 10000; ++i) {
        int rand = std::rand() % 5000;
        list.push_back(rand);
        map.insert(std::make_pair(rand, i));
    }
    // there should be duplicates in the list
    CHECK_FALSE( map.size() == list.size() );
    // removing those duplicates & sorting the resulting list
    list.sort();
    list.unique();
    CHECK( map.size() == list.size() );
    CHECK( (unsigned long)std::distance(map.begin(), map.end()) == map.size() );
}

/* RELATIONAL OPERATORS */
TEST_CASE("maps can be compared using relational operators", "[map][operators]")
{
    std::array<std::pair<char, int>, 4> a = {{ {'b', 2}, {'z', 40}, {'p', 1}, {'a', 680} }};
    std::array<std::pair<char, int>, 4> b = {{ {'b', 1}, {'z', 10}, {'c', 1}, {'z', 680} }};
    LIB::map<char, int> mymap1 (a.begin(), a.end());
    LIB::map<char, int> mymap2 (a.begin(), a.begin() + 2);
    LIB::map<char, int> mymap3;
    LIB::map<char, int> mymap4 (b.begin(), b.end());

    // mymap1 vs mymap2
    CHECK_FALSE( mymap1 == mymap2 );
    CHECK( mymap1 != mymap2 );
    CHECK( mymap1 < mymap2 );
    CHECK( mymap1 <= mymap2 );
    CHECK_FALSE( mymap1 > mymap2 );
    CHECK_FALSE( mymap1 >= mymap2 );

    // mymap1 vs mymap1
    CHECK( mymap1 == mymap1 );
    CHECK_FALSE( mymap1 != mymap1 );
    CHECK_FALSE( mymap1 < mymap1 );
    CHECK( mymap1 <= mymap1 );
    CHECK_FALSE( mymap1 > mymap1 );
    CHECK( mymap1 >= mymap1 );

    // mymap1 vs mymap3
    CHECK_FALSE( mymap1 == mymap3 );
    CHECK( mymap1 != mymap3 );
    CHECK_FALSE( mymap1 < mymap3 );
    CHECK_FALSE( mymap1 <= mymap3 );
    CHECK( mymap1 > mymap3 );
    CHECK( mymap1 >= mymap3 );

    // mymap3 vs mymap3
    CHECK( mymap3 == mymap3 );
    CHECK_FALSE( mymap3 != mymap3 );
    CHECK_FALSE( mymap3 < mymap3 );
    CHECK( mymap3 <= mymap3 );
    CHECK_FALSE( mymap3 > mymap3 );
    CHECK( mymap3 >= mymap3 );

    // mymap1 vs mymap4
    CHECK_FALSE( mymap1 == mymap4 );
    CHECK( mymap1 != mymap4 );
    CHECK( mymap1 < mymap4 );
    CHECK( mymap1 <= mymap4 );
    CHECK_FALSE( mymap1 > mymap4 );
    CHECK_FALSE( mymap1 >= mymap4 );
}

/* ITERATORS */
TEST_CASE("maps can be iterated over", "[map][iterators]")
{
    SECTION("iterators can be created as expected") {
        LIB::map<char, int> my_map;

        LIB::map<char, int>::iterator it = my_map.begin();
        LIB::map<char, int>::const_iterator cit = it;
        LIB::map<char, int>::const_iterator cit2 = my_map.begin();
        CHECK(( cit == my_map.begin() ));
        CHECK(( cit2 == my_map.begin() ));

        LIB::map<char, int>::reverse_iterator rit = my_map.rbegin();
        LIB::map<char, int>::const_reverse_iterator rcit = rit;
        LIB::map<char, int>::const_reverse_iterator rcit2 = my_map.rbegin();
        CHECK(( rcit == my_map.rbegin() ));
        CHECK(( rcit2 == my_map.rbegin() ));
    }

    SECTION("iterators allow in-order access to the map elements") {
        int rand = 0;
        LIB::map<int, char> map;
        std::list<int> list;

        for (int i = 0; i < 100; ++i) {
            rand = std::rand() % 1000;
            list.push_back(rand);
            map.insert(std::make_pair(rand, std::rand()));
        }

        list.sort();
        list.unique();
        CHECK( std::distance(map.begin(), map.end()) == std::distance(list.begin(), list.end()) );

        auto it = map.begin();
        auto lit = list.begin();
        for (; it != map.end(); ++it, ++lit)
            CHECK( it->first == *lit );

        auto rit = map.rbegin();
        auto rlit = list.rbegin();
        for (; rit != map.rend(); ++rit, ++rlit)
            CHECK( rit->first == *rlit );

        it = --map.end();
        lit = --list.end();
        for (; true; it--, lit--) {
            CHECK( it->first == *lit );
            if (it == map.begin())
                break;
        }
        CHECK( it == map.begin());
        CHECK( lit == list.begin());
    }
}

/* MODIFIERS */
TEST_CASE("insert works as expected", "[map][modifiers]")
{
    LIB::map<char, int> my_map;
    LIB::map<char, int>::iterator it_ret;
    std::pair<LIB::map<char, int>::iterator, bool> ret;

    SECTION("single element insert add the pair to the map if its not present") {
        CHECK( my_map.empty() );

        ret = my_map.insert(std::make_pair('g', 32));
        CHECK( my_map.size() == 1);
        CHECK( ret.first->first == 'g' );
        CHECK( ret.first->second == 32 );
        CHECK( ret.second );

        ret = my_map.insert(std::make_pair('g', 32));
        CHECK( my_map.size() == 1);
        CHECK( ret.first->first == 'g' );
        CHECK( ret.first->second == 32 );
        CHECK_FALSE( ret.second );

        ret = my_map.insert(std::make_pair('f', 21));
        CHECK( my_map.size() == 2);
        CHECK( ret.first->first == 'f' );
        CHECK( ret.first->second == 21 );
        CHECK( ret.second );
    }
    SECTION("position hint insert adds the pair regardless of the validity of hint") {
        my_map['a'] = 'a';
        my_map['e'] = 'e';
        my_map['f'] = 'f';
        my_map['h'] = 'h';
        my_map['i'] = 'i';
        my_map['s'] = 's';
        my_map['u'] = 'u';
        CHECK( my_map.size() == 7 );

        auto ita = my_map.find('a');
        auto ite = my_map.find('e');
        auto itf = my_map.find('f');

        //valid hint and key not in map
        it_ret = my_map.insert(ita, std::make_pair('b', 'b'));
        CHECK( my_map.size() == 8 );
        CHECK( it_ret->first == 'b' );
        CHECK( it_ret->second == 'b' );
        //valid hint but key already in map
        it_ret = my_map.insert(ita, std::make_pair('b', 'c'));
        CHECK( my_map.size() == 8 );
        CHECK( it_ret->first == 'b' );
        CHECK( it_ret->second == 'b' );
        it_ret = my_map.insert(my_map.find('b'), std::make_pair('e', 'c'));
        CHECK( my_map.size() == 8 );
        CHECK( it_ret->first == 'e' );
        CHECK( it_ret->second == 'e' );
        //invalid hint but key in map
        it_ret = my_map.insert(ite, std::make_pair('u', 'c'));
        CHECK( my_map.size() == 8 );
        CHECK( it_ret->first == 'u' );
        CHECK( it_ret->second == 'u' );
        //invalid hint but key not in map
        it_ret = my_map.insert(itf, std::make_pair('c', 'c'));
        CHECK( my_map.size() == 9 );
        CHECK( it_ret->first == 'c' );
        CHECK( it_ret->second == 'c' );
        it_ret = my_map.insert(ita, std::make_pair('z', 'z'));
        CHECK( my_map.size() == 10 );
        CHECK( it_ret->first == 'z' );
        CHECK( it_ret->second == 'z' );

        //assert content is the sum of inserts
        std::array< std::pair<const char, int>, 10 > arr = {{{'a','a'},{'b','b'},{'c','c'},{'e','e'},{'f','f'},{'h','h'},{'i','i'},{'s','s'},{'u','u'},{'z','z'}}};
        auto mapit = my_map.begin();
        auto arrit = arr.begin();
        for (; mapit != my_map.end(); ++mapit, ++arrit)
            CHECK( *mapit == *arrit );
    }
    SECTION("range insert inserts a copy of the ranges elements") {
        std::vector<std::pair<char, int> > v;
        for (char i = 'a'; i < 'z'; ++i)
            v.push_back(std::make_pair(i, rand()));
        auto first = v.begin() + 5;
        my_map.insert(first, first + 10);
        CHECK(( my_map.size() == 10 ));
        for (auto it = my_map.begin(); it != my_map.end(); ++it, ++first) {
            CHECK( it->first == first->first );
            CHECK( it->second == first->second );
        }
    }
}

TEST_CASE("erase works as expected", "[map][modifiers]")
{
    std::list<std::pair<const char, int> > data = {{{'a',1}, {'z', 25}, {'b',2}, {'c', 3}, {'d', 4}, {'r', 1}, {'e', 5}}};
    LIB::map<char, int> my_map (data.begin(), data.end());
    data.sort();

    SECTION("erase at iterator removes correct element") {
        my_map.erase(my_map.begin());
        my_map.erase(++++my_map.begin());
        my_map.erase(--my_map.end());
        my_map.erase(++++++my_map.begin());
        data.erase(data.begin());
        data.erase(++++data.begin());
        data.erase(--data.end());
        data.erase(++++++data.begin());
        CHECK( my_map.size() == data.size() );
        auto it = my_map.begin();
        auto lit = data.begin();
        for (; it != my_map.end(); ++it, ++lit)
            CHECK( *it == *lit );
    }
    SECTION("erase removes correct element when given a key") {
        int sum = 0;
        int ret = 0;
        ret = my_map.erase('b');
        CHECK( ret == 1 );
        sum += ret;
        ret = my_map.erase('b');
        CHECK( ret == 0 );
        ret = my_map.erase('a');
        CHECK( ret == 1 );
        sum += ret;
        ret = my_map.erase('z');
        CHECK( ret == 1 );
        sum += ret;
        ret = my_map.erase('z');
        CHECK( ret == 0 );
        ret = my_map.erase('/');
        CHECK( ret == 0 );
        ret = my_map.erase('$');
        CHECK( ret == 0 );
        CHECK( my_map.size() == data.size() - sum );
    }
    SECTION("erase iterator range") {
        my_map.erase(my_map.end(), my_map.end());
        my_map.erase(++++my_map.begin(), --my_map.end());
        data.erase(++++data.begin(), --data.end());
        CHECK( my_map.size() == 3 );
        CHECK( my_map.size() == data.size() );
        auto it = my_map.begin();
        auto lit = data.begin();
        for (; it != my_map.end(); ++it, ++lit)
            CHECK( *it == *lit );
        my_map.erase(my_map.begin(), my_map.end());
        CHECK( my_map.size() == 0 );
    }
}

TEST_CASE("maps can be swapped", "[map][modifiers]")
{
    LIB::map<int, std::string> my_map1;
    LIB::map<int, std::string> my_map2;

    my_map1[14] = "fifteen";
    my_map1[19] = "dog";
    my_map1[132] = "78";
    my_map1[-22] = "34";
    my_map1[10] = "autobahn";
    my_map2.swap(my_map1);
    CHECK( my_map1.empty() );
    CHECK( my_map2.size() == 5 );
    CHECK( my_map2[14] == "fifteen" );
    CHECK( my_map2[19] == "dog" );
    CHECK( my_map2[132] == "78" );
    CHECK( my_map2[-22] == "34" );
    CHECK( my_map2[10] == "autobahn" );
    my_map2.erase(++my_map2.begin(), my_map2.end());
    my_map2.swap(my_map1);
    CHECK( my_map1.size() == 1 );
    CHECK( my_map2.empty() );
}

TEST_CASE("clear works as expected", "[map][modifiers]")
{
    LIB::map<int, int> my_map;
    my_map.clear();
    CHECK( my_map.empty() );
    my_map['a'] = 1;
    my_map['b'] = 2;
    my_map['z'] = 3;
    my_map['i'] = 4;
    CHECK( my_map.size() == 4 );
    my_map.clear();
    CHECK( my_map.empty() );
    my_map['b'] = 2;
    CHECK( my_map.size() == 1 );
    my_map.clear();
    CHECK( my_map.empty() );
    CHECK(( my_map.begin() == my_map.end() ));
}

/* OBSERVERS */
TEST_CASE("value_comp & key_comp work as expected", "[map][observers]")
{
    LIB::map<char, int> mymap;
    LIB::map<char, int>::key_compare kc = mymap.key_comp();
    LIB::map<char, int>::value_compare vc = mymap.value_comp();

    mymap['a'] = 20;
    mymap['d'] = 20;

    CHECK( kc(mymap.begin()->first, (++mymap.begin())->first) );
    CHECK_FALSE( kc((++mymap.begin())->first, mymap.begin()->first) );
    CHECK_FALSE( kc(mymap.begin()->first, mymap.begin()->first) );
    CHECK_FALSE( kc(mymap.begin()->first, (----mymap.end())->first) );
    CHECK_FALSE( kc((----mymap.end())->first, mymap.begin()->first) );

    CHECK( vc(*mymap.begin(), *++mymap.begin()) );
    CHECK_FALSE( vc(*++mymap.begin(), *mymap.begin()) );
    CHECK_FALSE( vc(*mymap.begin(), *mymap.begin()) );
    CHECK_FALSE( vc(*mymap.begin(), *(----mymap.end())) );
    CHECK_FALSE( vc(*(----mymap.end()), *mymap.begin()) );
}

/* OPERATIONS */
TEST_CASE("find works as expected", "[map][operations]")
{
    LIB::map<char, int> mymap;
    mymap['a'] = 20;
    mymap['d'] = 80;

    CHECK( mymap.find('a')->first == 'a' );
    CHECK( mymap.find('a')->second == 20 );
    CHECK( mymap.find('d')->first == 'd' );
    CHECK( mymap.find('d')->second == 80 );
    CHECK(( mymap.find('f') == mymap.end() ));
    mymap.erase('a');
    CHECK(( mymap.find('a') == mymap.end() ));
}

TEST_CASE("count works as expected", "[map][operations]")
{
    LIB::map<char, int> mymap;
    mymap['a'] = 20;
    mymap['d'] = 80;
    CHECK( mymap.count('a') == 1 );
    CHECK( mymap.count('d') == 1 );
    CHECK( mymap.count('c') == 0 );
    CHECK( mymap.count('p') == 0 );
    mymap.erase('a');
    CHECK( mymap.count('a') == 0 );
}

TEST_CASE("lower_bound & upper_bound work as expected", "[map][operations]")
{
    LIB::map<char, int> mymap;

    SECTION("reference example") {
        mymap['a'] = 20;
        mymap['b'] = 40;
        mymap['c'] = 60;
        mymap['d'] = 80;
        mymap['e'] = 100;
        LIB::map<char, int>::iterator itlow = mymap.lower_bound ('b');
        LIB::map<char, int>::iterator itup = mymap.upper_bound ('d');
        CHECK( itlow->first == 'b' );
        CHECK( itlow->second == 40 );
        CHECK( itup->first == 'e' );
        CHECK( itup->second == 100 );
        mymap.erase(itlow, itup);
        CHECK( mymap.size() == 2 );
        CHECK( mymap.begin()->first == 'a' );
        CHECK( mymap.begin()->second == 20 );
        CHECK( (--mymap.end())->first == 'e' );
        CHECK( (--mymap.end())->second == 100 );
        CHECK( (mymap.upper_bound('z') == mymap.end()) );
    }
    SECTION("") {
        mymap[1] = 10;
        mymap[2] = 20;
        mymap[4] = 40;
        mymap[5] = 50;
        CHECK(( mymap.lower_bound(2)->first == 2 ));
        CHECK(( mymap.lower_bound(6) == mymap.end() ));
        CHECK(( mymap.upper_bound(3) == mymap.lower_bound(3) ));
        CHECK(( mymap.upper_bound(2)->first == 4 ));
    }
    SECTION("const versions") {
        mymap['a'] = 20;
        mymap['b'] = 40;
        mymap['d'] = 80;
        mymap['e'] = 100;
        mymap['f'] = 60;
        const LIB::map<char, int> cmymap (mymap);
        CHECK(( cmymap.upper_bound('c') == cmymap.lower_bound('c') ));
        CHECK(( cmymap.upper_bound('a')->first == 'b' ));
        CHECK(( cmymap.upper_bound('b')->first == 'd' ));
        CHECK(( cmymap.upper_bound('z') == cmymap.end() ));
        CHECK(( cmymap.lower_bound('d')->first == 'd' ));
        CHECK(( cmymap.lower_bound('z') == cmymap.end() ));
    }
}

TEST_CASE("equal_range works as expected", "[map][operations]")
{
    LIB::map<char, int> mymap;
    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;
    const LIB::map<char, int> cmymap (mymap);

    std::pair<LIB::map<char, int>::iterator, LIB::map<char, int>::iterator> ret = mymap.equal_range('b');
    CHECK( ret.first->first == 'b' );
    CHECK( ret.second->first == 'c' );
    CHECK( ret.first->second == 20 );
    CHECK( ret.second->second == 30 );
    CHECK(( mymap.equal_range('c').first->first == 'c' ));
    CHECK(( mymap.equal_range('c').first->second == 30 ));
    CHECK(( mymap.equal_range('c').second == mymap.end() ));
    CHECK(( mymap.equal_range('u').first == mymap.end() ));
    CHECK(( mymap.equal_range('u').second == mymap.end() ));

    std::pair<LIB::map<char, int>::const_iterator, LIB::map<char, int>::const_iterator> cret = cmymap.equal_range('c');

    CHECK( cret.first->first == 'c' );
    CHECK( cret.first->second == 30 );
    CHECK( cret.second == cmymap.end() );
    CHECK(( cmymap.equal_range('a').first->first == 'a' ));
    CHECK(( cmymap.equal_range('a').first->second == 10 ));
    CHECK(( cmymap.equal_range('u').first == cmymap.end() ));
    CHECK(( cmymap.equal_range('u').second == cmymap.end() ));
}
