#include <iostream>
#include <typeinfo>

#include "stack.hh"

    
    void Stack::push(int x){
        stk[stkIndex++] = x;
    }
    
    int Stack::pop(){
        return stk[--stkIndex];
    }
    
    int Stack::size(){
        return stkIndex;
    }
