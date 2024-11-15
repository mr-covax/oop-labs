#include <cstdint>
#include <new>
#include "block_allocator.h"

uint8_t* alignPtr(uint8_t* ptr, std::size_t alignment) {
    auto numericPtr = reinterpret_cast<std::size_t>(ptr);
    auto result = (numericPtr + alignment - 1) & ~(alignment - 1);
    return reinterpret_cast<uint8_t*>(result);
}

BlockAllocator::BlockAllocator(std::size_t bytes) 
        : allocated{0}, total{bytes}, block{operator new(bytes)} {
    // We add a small stub entry to mark the end of the allocation table
    // to reduce complexity inside do_allocate method.
    auto addr = reinterpret_cast<std::size_t>(block) + total;
    blockData.emplace_back(reinterpret_cast<void*>(addr), 0);
}

BlockAllocator::~BlockAllocator() {
    operator delete(block);
}

void* BlockAllocator::do_allocate(std::size_t bytes, std::size_t alignment) {
    auto head = alignPtr(reinterpret_cast<uint8_t*>(block), alignment);

    for (auto it = blockData.begin(); it != blockData.end(); ++it) {
        auto ptr = alignPtr(reinterpret_cast<uint8_t*>(it->position), alignment);

        if (bytes < ptr - head) {
            allocated += bytes;
            auto allocatedPtr = reinterpret_cast<void*>(head);
            blockData.emplace(it, allocatedPtr, bytes);
            return allocatedPtr;
        }
        head = alignPtr(ptr + it->size, alignment);
    }

    throw std::bad_alloc();
}

void BlockAllocator::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    for (auto it = blockData.begin(); it != blockData.end(); ++it) {
        if (it->position == p && it->size == bytes) {
            blockData.erase(it);
            allocated -= bytes;
            break;
        }
    }
}

bool BlockAllocator::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    auto* castedOther = reinterpret_cast<const BlockAllocator*>(&other);
    return (this == castedOther);
}