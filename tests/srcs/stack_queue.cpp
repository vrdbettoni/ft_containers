#include "../containers.hpp"
#include "catch.hpp"
#include <list>
#include <vector>
#include <stack>
#include <queue>

#ifdef VERIFY_UNIT_TESTS
# define LIB std
#else
# define LIB ft
#endif

#define CONTAINER_LIST ( LIB::stack, LIB::queue )
#define TYPE_LIST ( int, char, std::string, std::vector<int>, std::vector<std::string>, std::list<std::string>, std::list<std::deque<int> > )
#define VALUE_TYPE typename TestType::value_type

/* COMMON TESTS */
TEMPLATE_PRODUCT_TEST_CASE("container adaptors work as expected", "[container_adaptors][stack][queue]", CONTAINER_LIST, TYPE_LIST)
{
    TestType cnt;

    SECTION("containers are created empty") {
        CHECK( cnt.empty() );
        CHECK( cnt.size() == 0 );
    }
    SECTION("push updates containers size") {
        for (int i = 0; i < 100; ++i) {
            cnt.push(VALUE_TYPE());
            if (i == 49) {
                CHECK( cnt.size() == 50 );
                CHECK_FALSE( cnt.empty() );
            }
        }
        CHECK( cnt.size() == 100 );
        CHECK_FALSE( cnt.empty() );

        SECTION("pop updates containers size") {
            for (int i = 0; i < 100; ++i) {
                cnt.pop();
                if (i == 49) {
                    CHECK( cnt.size() == 50 );
                    CHECK_FALSE( cnt.empty() );
                }
            }
            CHECK( cnt.size() == 0 );
            CHECK( cnt.empty() );
        }
    }
}

TEMPLATE_PRODUCT_TEST_CASE("relational operators work as expected", "[container_adaptors][stack][queue]", CONTAINER_LIST, int)
{
    TestType cnt1;
    TestType cnt2;

    SECTION("on empty containers") {
        cnt1.push(1);
        cnt1.pop();
        CHECK(( cnt1 == cnt2 ));
        CHECK(( cnt1 <= cnt2 ));
        CHECK(( cnt1 >= cnt2 ));
        CHECK_FALSE(( cnt1 != cnt2 ) );
        CHECK_FALSE(( cnt1 < cnt2 ));
        CHECK_FALSE(( cnt1 > cnt2 ));
    }
    SECTION("on empty & non-empty containers") {
        cnt2.push(1);
        cnt2.push(2);
        CHECK(( cnt1 != cnt2 ));
        CHECK(( cnt1 <= cnt2 ));
        CHECK(( cnt1 < cnt2 ));
        CHECK_FALSE(( cnt1 == cnt2 ));
        CHECK_FALSE(( cnt1 >= cnt2 ));
        CHECK_FALSE(( cnt1 > cnt2 ));
    }
    SECTION("on two non-empty containers") {
        cnt1.push(1);
        cnt2.push(1);
        cnt2.push(2);
        CHECK(( cnt1 != cnt2 ));
        CHECK(( cnt1 <= cnt2 ));
        CHECK(( cnt1 < cnt2 ));
        CHECK_FALSE(( cnt1 == cnt2 ));
        CHECK_FALSE(( cnt1 >= cnt2 ));
        CHECK_FALSE(( cnt1 > cnt2 ));
        cnt1.push(2);
        CHECK(( cnt1 == cnt2 ));
        CHECK(( cnt1 <= cnt2 ));
        CHECK(( cnt1 >= cnt2 ));
        CHECK_FALSE(( cnt1 != cnt2 ));
        CHECK_FALSE(( cnt1 < cnt2 ));
        CHECK_FALSE(( cnt1 > cnt2 ));
    }
}

/* STACK TESTS */
TEST_CASE("stack specific methods work as expected", "[container_adaptors][stack]")
{
    LIB::stack<int> my_cnt;
    std::stack<int> stl_cnt;

    SECTION("top method works like stl container") {
        for (int i = 0; i < 40; ++i) {
            my_cnt.push(i);
            stl_cnt.push(i);
        }
        for (int i = 39; i >= 0; --i) {
            CHECK( my_cnt.top() == stl_cnt.top() );
            CHECK( my_cnt.top() == i );
            my_cnt.pop();
            stl_cnt.pop();
        }
    }
}

/* QUEUE TESTS */
TEST_CASE("deque specific methods work as expected", "[container_adaptors][queue]")
{
    LIB::queue<int> my_cnt;
    std::queue<int> stl_cnt;

    SECTION("back method works like stl container") {
        for (int i = 0; i < 5; ++i) {
            my_cnt.push(i);
            stl_cnt.push(i);
            CHECK( my_cnt.back() == stl_cnt.back() );
        }
        my_cnt.back() = 3;
        stl_cnt.back() = 3;
        CHECK( my_cnt.back() == stl_cnt.back() );
        my_cnt.pop();
        stl_cnt.pop();
        CHECK( my_cnt.back() == stl_cnt.back() );
    }
    SECTION("front method works as expected") {
        for (int i = 0; i < 9; ++i) {
            my_cnt.push(i);
            stl_cnt.push(i);
            CHECK( my_cnt.front() == stl_cnt.front() );
        }
        my_cnt.front() = 3;
        stl_cnt.front() = 3;
        CHECK( my_cnt.front() == stl_cnt.front() );
        my_cnt.pop();
        stl_cnt.pop();
        CHECK( my_cnt.front() == stl_cnt.front() );
    }
}
