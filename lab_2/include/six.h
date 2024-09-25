#pragma once

// 24 base-six digits can hold up to and including 46_655
const unsigned char ALLOC_DIGITS = 6;
const unsigned int MAX_SIZE = 46655;

class Six {
    public:
        Six() = default;
        Six(unsigned int value);

        Six plus(const Six& value);
        Six minus(const Six& value);
        void copy(Six& dest);

        bool greater_than(const Six& rhs);
        bool less_than(const Six& rhs);
        bool equals(const Six& rhs);

    private:
        unsigned char* digits{ new unsigned char[ALLOC_DIGITS]{} };
        void print();
        int compare(const Six& rhs);
};