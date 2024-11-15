#include <gtest/gtest.h>
#include <memory_resource>
#include "stack.tpp"
#include "block_allocator.h"

// Test constructor and initial state
TEST(StackTest, ConstructorInitialState) {
    BlockAllocator mem = BlockAllocator(1024);
    std::pmr::polymorphic_allocator<int> alloc(&mem);
    Stack<int> stack(alloc);

    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.empty());
}

// Test push operation
TEST(StackTest, PushOperation) {
    BlockAllocator mem = BlockAllocator(1024);
    std::pmr::polymorphic_allocator<int> alloc(&mem);
    Stack<int> stack(alloc);

    stack.push(1);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.top(), 1);
}

// Test pop operation
TEST(StackTest, PopOperation) {
    BlockAllocator mem = BlockAllocator(1024);
    std::pmr::polymorphic_allocator<int> alloc(&mem);
    Stack<int> stack(alloc);

    stack.push(1);
    stack.push(2);

    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    EXPECT_EQ(stack.size(), 1);

    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test popping from an empty stack
TEST(StackTest, PopEmptyStack) {
    BlockAllocator mem = BlockAllocator(1024);
    std::pmr::polymorphic_allocator<int> alloc(&mem);
    Stack<int> stack(alloc);

    EXPECT_THROW(stack.pop(), std::runtime_error);
}

// Test push and top with multiple elements
TEST(StackTest, PushMultipleElements) {
    BlockAllocator mem = BlockAllocator(1024);
    std::pmr::polymorphic_allocator<int> alloc(&mem);
    Stack<int> stack(alloc);

    for (int i = 1; i <= 5; ++i) {
        stack.push(i);
        EXPECT_EQ(stack.top(), i);
        EXPECT_EQ(stack.size(), i);
    }
}

// Test size and empty after multiple operations
TEST(StackTest, SizeAndEmptyCheck) {
    BlockAllocator mem = BlockAllocator(1024);
    std::pmr::polymorphic_allocator<int> alloc(&mem);
    Stack<int> stack(alloc);

    stack.push(4);
    stack.push(4);

    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test stack behavior with complex types (only for `std::string`)
TEST(StackTestComplex, StringStack) {
    BlockAllocator mem = BlockAllocator(1024);
    std::pmr::polymorphic_allocator<std::string> alloc(&mem);
    Stack<std::string> stringStack(alloc);

    stringStack.push("Hello");
    stringStack.push("World");

    EXPECT_EQ(stringStack.size(), 2);
    EXPECT_EQ(stringStack.top(), "World");

    stringStack.pop();
    EXPECT_EQ(stringStack.top(), "Hello");

    stringStack.pop();
    EXPECT_TRUE(stringStack.empty());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}