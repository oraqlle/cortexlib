#include <catch2/catch.hpp>
#include <iterators/column.hpp>
#include <iterators/row.hpp>
#include <vector>

TEST_CASE("Comparisons")
{
    std::vector<int> v { 0, 1, 2
                       , 3, 4, 5
                       , 6, 7, 8 };

    auto it = cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin(), 0ul, 0ul, 3ul, 3ul);

    SECTION("Equality")
    { REQUIRE(it == cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin(), 0ul, 0ul, 3ul, 3ul)); }
        
    SECTION("Inequality")
    { REQUIRE(it != cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin() + 8, 2ul, 2ul, 3ul, 3ul)); }

    SECTION("Less than")
    { REQUIRE(it < cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin() + 8, 2ul, 2ul, 3ul, 3ul)); }

    SECTION("Greater than")
    { REQUIRE(cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin() + 8, 2ul, 2ul, 3ul, 3ul) > it); }

    SECTION("Less than or equal")
    { REQUIRE(it <= cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin() + 8, 2ul, 2ul, 3ul, 3ul)); }

    SECTION("Greater than or equal")
    { REQUIRE(cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin() + 8, 2ul, 2ul, 3ul, 3ul) >= it); }

    SECTION("Spaceship")
    { 
        REQUIRE(it <=> cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin(), 2ul, 2ul, 3ul, 3ul) == std::strong_ordering::equal);
        REQUIRE(it <=> cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin() + 3, 2ul, 2ul, 3ul, 3ul) == std::strong_ordering::less);
        REQUIRE(cortex::two_dim_iterator<typename std::vector<int>::iterator>(v.begin()+ 6, 2ul, 2ul, 3ul, 3ul) <=> it == std::strong_ordering::greater);
    }
}