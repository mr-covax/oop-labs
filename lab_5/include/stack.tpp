#pragma once

#include <iterator>
#include <stdexcept>
#include <memory_resource>

template <typename T>
struct StackElement {
    T element;
    StackElement* next;
};

template <typename T>
class StackIter {
    public:
        using iterator_category = std::forward_iterator_tag;

        StackIter(StackElement<T>* current) : m_current(current) {}

        T& operator*() const {
            if (!m_current) {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return m_current->element;
        }

        T* operator->() const { 
            return &(operator*()); 
        }

        StackIter<T>& operator++() {
            if (m_current) {
                m_current = m_current->next;
            }
            return *this;
        }

        StackIter<T> operator++(int) {
            StackIter<T> temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const StackIter<T>& other) const { 
            return m_current == other.m_current; 
        
        }

        bool operator!=(const StackIter<T>& other) const { 
            return m_current != other.m_current;
        }

    private:
        StackElement<T>* m_current;
    };


template <typename T>
class Stack {
public:
    Stack(std::pmr::polymorphic_allocator<StackElement<T>> allocator)
        : m_size(0), m_top(nullptr), m_alloc(allocator) {}

    void push(const T& value) {
        StackElement<T>* new_element = m_alloc.allocate(1);
        m_alloc.construct(new_element, StackElement<T>{value, m_top});
        m_top = new_element;
        ++m_size;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Cannot pop from an empty stack");
        }

        StackElement<T>* old_top = m_top;

        m_top = m_top->next;
        --m_size;

        m_alloc.destroy(old_top);
        m_alloc.deallocate(old_top, 1);
    }

    T& top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return m_top->element;
    }

    bool empty() const {
        return m_size == 0;
    }

    std::size_t size() const {
        return m_size;
    }

    StackIter<T> begin() {
        return StackIter<T>(m_top);
    }

    StackIter<T> end() {
        return StackIter<T>(nullptr);
    }

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

private:
    std::size_t m_size;  // Number of elements in the stack
    StackElement<T>* m_top;  // Pointer to the top element
    std::pmr::polymorphic_allocator<StackElement<T>> m_alloc;  // Custom allocator
};