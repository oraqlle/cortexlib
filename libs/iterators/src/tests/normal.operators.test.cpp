#include <catch2/catch.hpp>
#include <iterators/normal.hpp>
#include <vector>

struct Point
{
    int x;
    int y;
};

TEST_CASE("normal_iterator operators")
{
    std::vector<int> v{1, 2, 3, 4, 5};
    auto it { cortex::make_normal(v, v.begin()) };

    SECTION("operator*(dereference)")
    { REQUIRE(*it == 1); }

    std::vector<Point> points { { 1, 5 } };

    auto indirect_it { cortex::make_normal(points, points.begin()) };

    SECTION("operator-> [indirection]")
    { REQUIRE(indirect_it->x == 1); }

    SECTION("operator-> [indirection]")
    { REQUIRE(indirect_it->y == 5); }

    SECTION("operator[]")
    { REQUIRE(it[2] == 3); }

    SECTION("operator++")
    { REQUIRE(*++it == 2);}

    SECTION("operator++(int)")
    { 
        REQUIRE(*it++ == 1); 
        REQUIRE(*it == 2);
    }

    SECTION("operator--")
    { 
        it += 4;
        REQUIRE(*--it == 4); 
    }

    SECTION("operator--(int)")
    { 
        it += 4;
        REQUIRE(*it-- == 5);
        REQUIRE(*it == 4);
    }

    SECTION("operator+")
    { REQUIRE(*(it + 2) == 3); }

    SECTION("operator+=")
    { 
        it += 4;
        REQUIRE(*it == 5); 
    }

    SECTION("operator-")
    { 
        it += 4;
        REQUIRE(*(it - 1) == 4); 
    }

    SECTION("operator-=")
    { 
        it += 4;
        it -= 3;
        REQUIRE(*it == 2);
    }


    // std::vector<std::vector<int>> vv{
    //     {1, 2, 3},
    //     {4, 5, 6},
    //     {7, 8, 9}
    // };

    // std::vector<std::vector<int>> vvcheck{
    //     {1, 2, 3},
    //     {4, 5, 6},
    //     {7, 8, 9, 10}
    // };

    // auto itc = cortex::make_normal(vv, vv.begin());

    // SECTION("operator->")
    // {
    //     itc->push_back(10);
    //     REQUIRE(vv == vvcheck);
    // }


    it = cortex::make_normal(v, v.begin());
    SECTION("operator==")
    { REQUIRE(it == cortex::make_normal(v, v.begin())); }

    SECTION("operator<=>")
    { 
        REQUIRE((it <=> cortex::make_normal(v, v.begin())) == std::strong_ordering::equal); 
        REQUIRE(((it + 1) <=> cortex::make_normal(v, v.begin())) == std::strong_ordering::greater); 
        REQUIRE((it <=> cortex::make_normal(v, v.begin()) + 1) == std::strong_ordering::less); 
    }

    SECTION("operator!=")
    { REQUIRE(it != cortex::make_normal(v, v.begin()) + 1); }

    SECTION("operator<")
    { REQUIRE(it < cortex::make_normal(v, v.begin()) + 3); }

    SECTION("operator<=")
    { REQUIRE(it <= cortex::make_normal(v, v.begin())); }

    SECTION("operator>")
    { REQUIRE(it + 4 > cortex::make_normal(v, v.begin())); }

    SECTION("operator>=")
    { REQUIRE(it + 4 >= cortex::make_normal(v, v.begin())); }
}