#include "six.h"
#include <iostream>
#include <stdexcept>


void Six::print() {
    std::cout << "[";
    for (int i{0}; i < ALLOC_DIGITS; ++i) {
        std::cout << ' ' << (int)digits[i];
    }
    std::cout << " ]" << std::endl;
}

Six::Six(unsigned int value) {
    int i{0};

    if (value > MAX_SIZE) {
        throw std::out_of_range("Buffer too small to fit the value");
    }

    while (value) {
        digits[i] = value % 6;
        value /= 6;
        ++i;
    }
}

Six Six::plus(const Six& value) {
    Six result{};
    int digit_sum{0}, carry{0};

    for (int i{0}; i < ALLOC_DIGITS; ++i) {
        digit_sum = digits[i] + value.digits[i] + carry;
        result.digits[i] = digit_sum % 6;
        carry = digit_sum / 6;
    }
    if (carry) {
        throw std::overflow_error("Value is now too big to fit");
    }

    return result;
}

Six Six::minus(const Six& value) {
    Six result{};
    int borrow{0}, diff{0};

    for (int i{0}; i < ALLOC_DIGITS; ++i) {
        diff = digits[i] - value.digits[i] - borrow;
        
        if (diff < 0) {
            diff += 6;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.digits[i] = diff;
    }

    if (borrow)
        throw std::underflow_error("Resulting value cannot be negative");

    return result;
}

void Six::copy(Six& dest) {
    for (int i{0}; i < ALLOC_DIGITS; ++i) {
        dest.digits[i] = digits[i];
    }
}

bool Six::greater_than(const Six& rhs) {
    return compare(rhs) == 1;
}

bool Six::less_than(const Six& rhs) {
    return compare(rhs) == 0;
}

bool Six::equals(const Six& rhs) {
    return compare(rhs) == -1;
}

int Six::compare(const Six& rhs) {
    // This function combines all order checking operations into
    // one for cleaner implementations of the public interface.
    // 
    // Returns 1 if this value is larger than rhs
    //         0 if rhs is larger
    //        -1 if equal
    
    for (int i{ALLOC_DIGITS}; i >= 0; --i) {
        if (digits[i] != rhs.digits[i]) {
            return digits[i] > rhs.digits[i];
        }
    }
    return -1;
}