#include <stdexcept>
#include "six.h"

Six::Six() : size(1), array{ new unsigned char{0} } {}

Six::Six(unsigned int value) : Six(value, 8) {}

Six::Six(unsigned int value, unsigned int max_len) {
    size = max_len;
    array = new unsigned char[size]{};

    for (int i{0}; i < size && value; ++i) {
        array[i] = value % 6;
        value /= 6;
    }

    if (value)
        throw std::out_of_range("Buffer too small to fit the value");
}

Six::Six(const Six& src) noexcept {
    size = src.size;
    array = new unsigned char[size]{};
    
    for (int i{0}; i <= size; ++i) {
        array[i] = src.array[i];
    }
}

Six Six::plus(const Six& value) const {
    unsigned int max_size = std::max<int>(size, value.size);
    Six result{0, max_size};

    // Я бы лично развернул конструкцию ниже на три цикла:
    //   - первый от 0 до минимального из размеров контейнера (i);
    //   - второй от i до размера исходного контейнера;
    //   - третий от i до размера второго.
    // 
    // Таким образом, не пришлось бы делать постоянные проверки
    // на выход за границы внутри цикла, улучшая тем самым эффективность
    // ценой тройного дублирования кода внутри функции.

    int sum{0}, i{0};
    for (i; i < max_size; ++i) {
        sum += (i < size) ? array[i] : 0;
        sum += (i < value.size) ? value.array[i] : 0;
        result.array[i] = sum % 6;
        sum /= 6;
    }

    if (sum) { throw std::overflow_error("Buffer too small to fit the result"); }
    return result;
}

Six Six::minus(const Six& value) const {
    unsigned int max_size = std::max<int>(size, value.size);
    Six result{0, max_size};

    // Объяснение, почему я считаю, что конструкция ниже
    // неэффективна, смотри в Six::plus();

    int diff{0}, i{0};
    for (i; i < max_size; ++i) {
        diff += (i < size) ? array[i] : 0;
        diff -= (i < value.size) ? value.array[i] : 0;
        result.array[i] = (6 + diff) % 6;
        diff = -1 * (diff < 0);
    }

    if (diff) { throw std::underflow_error("Value must be non-negative"); }
    return result;
}

bool Six::equals(const Six& value) const {
    return compare(value) == -1;
}

bool Six::less_than(const Six& value) const {
    return compare(value) == 0;
}

bool Six::greater_than(const Six& value) const {
    return compare(value) == 1;
}

int Six::compare(const Six& value) const {
    // Эта функция объединяет несколько видов сравнения
    // и чем-то похоже на cmp(). 
    // Возращает:
    //     1, если this > value;
    //     0, ecли this < value;
    //    -1, если this == value;

    int a, b;
    int max_size = std::max<int>(size, value.size);

    for (int i{max_size}; i >= 0; --i) {
        a = (i < size) ? array[i] : 0;
        b = (i < value.size) ? value.array[i] : 0;
        if (a != b)
            return a > b;
    }
    return -1;
}

Six::~Six() noexcept {
    size = 0;
    delete []array;
    array = nullptr;
}