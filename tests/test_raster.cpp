#include <doctest/doctest.h>

#include <spatial/raster/raster.hpp>

TEST_CASE("raster construction")
{
    constexpr auto  ncols  = 10;
    constexpr auto  nrows  = 15;
    constexpr auto  ncells = ncols * nrows;

    spatial::raster x{ 15, 10, { 10, -10, 5, -5 } };

    CHECK(x.ncols() == ncols);
    CHECK(x.nrows() == nrows);
    CHECK(x.ncells() == ncells);

    REQUIRE_EQ(x.at(0, 1), 0);
    REQUIRE_THROWS(x.at(10, 0));

    x[{ 3, 4 }] = 5.0;
    CHECK(x[{ 3, 4 }] == 5.0);

    for (auto row = 0; row < nrows; row++) {
        for (auto col = 0; col < ncols; col++) {
            x[{ col, row }] = col * row;
            CHECK(x[{ col, row }] == col * row);
        }
    }

    x.apply([](auto& cell) { cell += 1; });
    for (auto row = 0; row < nrows; row++) {
        for (auto col = 0; col < ncols; col++) {
            CHECK(x[{ col, row }] == (col * row) + 1);
        }
    }

    const auto  origin  = x.at(0, 0);
    const auto  alt     = x.at(3, 3);
    const auto& invalid = spatial::cell::invalid;

    REQUIRE_EQ(origin.right(), x.at(1, 0));
    REQUIRE_EQ(origin.top(), x.at(0, 1));
    REQUIRE_EQ(origin.top_right(), x.at(1, 1));

    REQUIRE_EQ(origin.top_left(), invalid);
    REQUIRE_EQ(origin.left(), invalid);
    REQUIRE_EQ(origin.bottom(), invalid);
    REQUIRE_EQ(origin.bottom_left(), invalid);
    REQUIRE_EQ(origin.bottom_right(), invalid);

    REQUIRE_EQ(alt.right(), x.at(4, 3));
    REQUIRE_EQ(alt.top(), x.at(3, 4));
    REQUIRE_EQ(alt.top_right(), x.at(4, 4));
    REQUIRE_EQ(alt.top_left(), x.at(2, 4));
    REQUIRE_EQ(alt.left(), x.at(2, 3));
    REQUIRE_EQ(alt.bottom(), x.at(3, 2));
    REQUIRE_EQ(alt.bottom_left(), x.at(2, 2));
    REQUIRE_EQ(alt.bottom_right(), x.at(4, 2));
}
