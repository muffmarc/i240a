#ifndef STACK_HH_
#define STACK_HH_

class Stack {

int stk[16];
    
int stkIndex = 0;

public:
    
    void push(int x);
    
    int pop();
    
    int size();
    
};
#endif
