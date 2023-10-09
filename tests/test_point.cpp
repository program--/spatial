#include <doctest/doctest.h>

#include <memory>
#include <spatial/vector/point.hpp>

TEST_CASE("[st::point] construction")
{
    st::point a = { 1, 2 };
    CHECK_EQ(a.x(), 1);
    CHECK_EQ(a.y(), 2);
    st::point_ref b = a;
    CHECK_EQ(b.x(), 1);
    CHECK_EQ(b.y(), 2);

    b.x() = 3;
    REQUIRE_EQ(b.x(), 3);
    REQUIRE_EQ(a.x(), 3);

    st::const_point_ref c = b;
    CHECK_EQ(c.x(), 3);
    CHECK_EQ(c.y(), 2);

    REQUIRE_EQ(std::addressof(a.x()), std::addressof(b.x()));
    REQUIRE_EQ(std::addressof(b.x()), std::addressof(c.x()));
}
