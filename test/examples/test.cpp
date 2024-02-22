#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

int add_ints(int a, int b)
{
    return(a + b);
}

TEST_CASE("add_ints")
{
    REQUIRE(add_ints(5, 10) == 15);
}