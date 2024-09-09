#include <gtest/gtest.h>
#include "../include/divider.hpp"

TEST(base_case, basic_test_set) {
    ASSERT_TRUE(get_min_divs(5, 5) == 8);       // 4 h-cuts, 4 v-cuts
    ASSERT_TRUE(get_min_divs(100, 100) == 198); // 99 h-cuts, 99 v-cuts
}

TEST(no_bar, basic_test_set) {
    ASSERT_TRUE(get_min_divs(0, 0) == 0);       // No bar at all :(
}

TEST(single_square_bar, basic_test_set) {
    ASSERT_TRUE(get_min_divs(1, 1) == 0);       // A single square
}

TEST(side_equals_one, basic_test_set) {
    ASSERT_TRUE(get_min_divs(6, 1) == 5);       // Only horizontal cuts
    ASSERT_TRUE(get_min_divs(1, 6) == 5);       // Only vertical cuts
}

TEST(negative_sides, basic_test_set) {
    ASSERT_TRUE(get_min_divs(-1, 2) == 0);
    ASSERT_TRUE(get_min_divs(2, -1) == 0);
    ASSERT_TRUE(get_min_divs(-2, -1) == 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}