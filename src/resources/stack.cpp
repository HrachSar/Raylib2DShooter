//
// Created by hrach on 1/18/25.
//

#include "stack.h"
#include <stdexcept>

Stack::Stack() {
    m_top = -1;
}
void Stack::Push(int element) {
    // if (this->Size() == 512)
    //     throw std::out_of_range("Stack Overflow");

    m_stack[++m_top] = element;
}
int Stack::Pop() {
    int data = m_stack[m_top];
    m_stack[m_top] = 0;
    --m_top;

    return data;
}
int Stack::Size() const {
    return m_top + 1;
}
bool Stack::Empty() const {
    return Size() == 0;
}

int Stack::Top() const {
    if (!Empty())
        return m_stack[m_top];
    return -1;
}



