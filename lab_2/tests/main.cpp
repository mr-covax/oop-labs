#include <gtest/gtest.h>
#include <stdexcept>
#include "six.h"

TEST(initialization_test_suite, overflowing_numbers) {
    EXPECT_THROW(Six{MAX_SIZE + 1}, std::out_of_range);
}

TEST(equal_test_suite, equal_to_itself) {
    Six lhs{50};
    ASSERT_TRUE(lhs.equals(lhs));
}

TEST(equal_test_suite, different_equal_objects) {
    Six lhs{100};
    Six rhs{100};
    ASSERT_TRUE(lhs.equals(rhs));
    ASSERT_TRUE(rhs.equals(lhs));
}

TEST(equal_test_suite, no_args_is_zero) {
    Six lhs{};
    Six rhs{0};
    ASSERT_TRUE(lhs.equals(rhs));
    ASSERT_TRUE(rhs.equals(lhs));
}

TEST(equal_test_suite, no_equal) {
    Six lhs{100};
    Six rhs{200};
    
    ASSERT_FALSE(lhs.equals(rhs));
    ASSERT_FALSE(rhs.equals(lhs));
}

TEST(comparison_test_suite, larger) {
    Six small{100};
    Six large{200};
    
    ASSERT_TRUE(large.greater_than(small));
    ASSERT_FALSE(small.greater_than(large));
}

TEST(comparison_test_suite, smaller) {
    Six small{100};
    Six large{200};
    
    ASSERT_TRUE(small.less_than(large));
    ASSERT_FALSE(large.less_than(small));
}

TEST(comparison_test_suite, equal_is_not_larger) {
    Six value{100};
    ASSERT_FALSE(value.greater_than(value));
}

TEST(comparison_test_suite, equal_is_not_smaller) {
    Six value{100};
    ASSERT_FALSE(value.less_than(value));
}

TEST(addition_test_suite, normal_test) {
    Six left{10}, right{20}, answer{30};
    Six result = left.plus(right);
    ASSERT_TRUE(result.equals(answer));
}

TEST(addition_test_suite, throw_on_overflow) {
    Six left{MAX_SIZE}, right{MAX_SIZE};
    EXPECT_THROW(left.plus(right), std::overflow_error);
}

TEST(subtraction_test_suite, normal_test) {
    Six left{30}, right{20}, answer{10};
    Six result = left.minus(right);
    ASSERT_TRUE(result.equals(answer));
}

TEST(subtraction_test_suite, throw_on_underflow) {
    Six left{10}, right{20};
    EXPECT_THROW(left.minus(right), std::underflow_error);
}

TEST(copy_test_suite, regular_test) {
    Six value{10};
    Six copy;
    value.copy(copy);
    ASSERT_TRUE(copy.equals(value));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}