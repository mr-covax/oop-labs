#include <gtest/gtest.h>
#include "block_allocator.h"

// Test constructor and initial state
TEST(BlockAllocatorTest, ConstructorInitialState) {
    EXPECT_NO_THROW({
        BlockAllocator tempAllocator(512);
    });
}

// Test alignment utility function
TEST(BlockAllocatorUtilsTest, AlignPtr) {
    uint8_t dummyBuffer[64];
    uint8_t* aligned = alignPtr(dummyBuffer, 16);
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(aligned) % 16, 0);

    aligned = alignPtr(dummyBuffer, 8);
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(aligned) % 8, 0);
}

// Test allocation with proper alignment
TEST(BlockAllocatorTest, AllocateWithAlignment) {
    BlockAllocator allocator = BlockAllocator(1024);

    void* ptr1 = allocator.allocate(16, 16);
    EXPECT_NE(ptr1, nullptr);

    void* ptr2 = allocator.allocate(32, 32);
    EXPECT_NE(ptr2, nullptr);

    EXPECT_NE(ptr1, ptr2);
}

// Test allocation failure when out of memory
TEST(BlockAllocatorTest, AllocateOutOfMemory) {
    BlockAllocator allocator = BlockAllocator(1024);

    // Allocate almost all available space
    allocator.allocate(1000, 1);

    // Next allocation should fail
    EXPECT_THROW({
        allocator.allocate(32, 1);
    }, std::bad_alloc);
}

// Test deallocation
TEST(BlockAllocatorTest, DeallocateMemory) {
    BlockAllocator allocator = BlockAllocator(1024);

    void* ptr = allocator.allocate(64, 8);
    EXPECT_NE(ptr, nullptr);

    allocator.deallocate(ptr, 64, 8);

    // Reallocate to check if memory is reused
    void* ptr2 = allocator.allocate(64, 8);
    EXPECT_EQ(ptr, ptr2);
}

// Test memory resource equality comparison
TEST(BlockAllocatorTest, IsEqual) {
    BlockAllocator allocator(512);
    BlockAllocator anotherAllocator(512);

    EXPECT_FALSE(allocator.is_equal(anotherAllocator));
}

// Test deallocation of non-existent block
TEST(BlockAllocatorTest, DeallocateNonExistentBlock) {
    BlockAllocator allocator = BlockAllocator(1024);

    void* invalidPtr = reinterpret_cast<void*>(0xdeadbeef);
    EXPECT_NO_THROW({
        allocator.deallocate(invalidPtr, 32, 8);
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}