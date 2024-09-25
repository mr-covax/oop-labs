#pragma once

class Six {
public:
    Six();
    Six(unsigned int decimal_value);
    Six(unsigned int size, unsigned int decimal_value);
    Six(const Six& src) noexcept;

    Six plus(const Six& value) const;
    Six minus(const Six& value) const;
    
    bool equals(const Six& value) const;
    bool less_than(const Six& value) const ;
    bool greater_than(const Six& value) const;

    virtual ~Six() noexcept;

private:
    unsigned int size;
    unsigned char *array;
    int compare(const Six& value) const;
};