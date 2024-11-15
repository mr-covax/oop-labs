#pragma once

#include <list>
#include <memory_resource>

struct BlockEntry {
    void* position;
    std::size_t size;
};

class BlockAllocator : public std::pmr::memory_resource {
public:
    BlockAllocator(std::size_t bytes);
    ~BlockAllocator() override;

private:
    void* block;
    size_t allocated, total;
    std::list<BlockEntry> blockData;

    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

uint8_t* alignPtr(uint8_t* ptr, std::size_t alignment);