#include <gtest/gtest.h>
#include "../include/divider.h"

TEST(bar_div_test, base_case) {
    ASSERT_TRUE(get_min_divs(5, 5) == 8);       // 4 h-cuts, 4 v-cuts
    ASSERT_TRUE(get_min_divs(100, 100) == 198); // 99 h-cuts, 99 v-cuts
}

TEST(bar_div_test, no_bar) {
    ASSERT_TRUE(get_min_divs(0, 0) == 0);       // No bar at all :(
}

TEST(bar_div_test, single_square) {
    ASSERT_TRUE(get_min_divs(1, 1) == 0);       // A single square
}

TEST(bar_div_test, side_equals_one) {
    ASSERT_TRUE(get_min_divs(6, 1) == 5);       // Only horizontal cuts
    ASSERT_TRUE(get_min_divs(1, 6) == 5);       // Only vertical cuts
}

TEST(bar_div_test, negative_sides) {
    ASSERT_TRUE(get_min_divs(-1, 2) == 0);
    ASSERT_TRUE(get_min_divs(2, -1) == 0);
    ASSERT_TRUE(get_min_divs(-2, -1) == 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
