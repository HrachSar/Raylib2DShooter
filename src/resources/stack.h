//
// Created by hrach on 1/18/25.
//

#ifndef STACK_H
#define STACK_H



class Stack {
public:
    Stack();
    int Top() const;
    int Pop();
    int Size() const;
    void Push(int element);
    bool Empty() const;
private:
    int m_stack[512];
    int m_top;
};



#endif //STACK_H
