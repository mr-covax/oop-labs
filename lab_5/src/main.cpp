#include <iostream>
#include <cassert>
#include <memory_resource>
#include "block_allocator.h"
#include "stack.tpp"

enum StopLightColors {
    Red,
    Green,
    Blue
};

struct SampleStruct {
    std::size_t largeVariable;
    std::string someString;
    StopLightColors color;
};

int main() {
    // This is a memory_resource that will be used for all stacks today.
    BlockAllocator blockAlloc(4096);

    // Testing the stack and the memory resource on a simple data type.
    std::pmr::polymorphic_allocator<int> allocator{&blockAlloc};
    Stack<int> sampleStack(allocator);

    for (std::size_t i{}; i < 50; ++i) {
        sampleStack.push(i);
    }
    for (auto entry : sampleStack) {
        std::cout << "Element: " << entry << std::endl; 
    }
    while (!sampleStack.empty()) {
        sampleStack.pop();
    }

    std::cout << "All elements popped from the stack!" << std::endl;

    // Now testing on a multi-field structure...
    std::pmr::polymorphic_allocator<SampleStruct> structAlloc{&blockAlloc};
    Stack<SampleStruct> structStack(structAlloc);

    SampleStruct e1(1234567890, "Hello, world", Red);
    SampleStruct e2(69, "Hello, Artyom Yadrow!", Green);
    structStack.push(e1);
    structStack.push(e2);

    for (auto entry : structStack) {
        std::cout << '\n'
            << "Value: " << entry.largeVariable << '\n'
            << "String: " << entry.someString << '\n'
            << "Color: " << entry.color << std::endl; 
    }

    return 0;
}