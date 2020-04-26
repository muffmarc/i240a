#include <iostream>
#include <cstring>

#include "stack.cc"

struct DelimMap {
  int delim;
  int encoding;
};

DelimMap delimEncodings[] = {
    { '(', 1 },
    { ')', -1 },
    { '[', 2 },
    { ']', -2 },
    { '{', 3 },
    { '}', -3 },
    { '<', 4 },
    { '>', -4 }
};

bool chkDelim(char c) {
    for (int i=0; i < sizeof(delimEncodings); i++){
        if(delimEncodings[i].delim == c) {
            return true;
        }
    }
    return false;
}

int balance(int argc, const char* argv[]) {
    if (argc == 0){
        std::cout << "2" << std::endl;
        return 2;
    }
    Stack* stackptr = new Stack();
    Stack& stack = *stackptr;
    int count = 0;
    int i = 1;
    for (i; i < argc; i++) {
        if (argv[i][1] != 0) return i;
        if (!chkDelim(argv[i][0])) {
            std::cout << "Invalid Delimiter " << "'" << argv[i][0] << "'" << std::endl;
        }
        for (int j=0; j < sizeof(delimEncodings); j++){
            if (delimEncodings[j].delim != argv[i][0]) continue;
            if(delimEncodings[j].encoding > 0) {
                stack.push(delimEncodings[j].encoding);
                break;
            }
            else if (delimEncodings[j].encoding < 0) {
                int l = stack.pop();
                int r = delimEncodings[j].encoding;
                if(l + r == 0) count++;
                else { 
                    return i; 
                }
                break;
            }
        }
    }
    if(stack.size() != 0) return i - 1;
        
    return stack.size();
}

int main(int argc, const char* argv[]) {
    int result = balance(argc, argv);
    if (result == 0) return 0;
    else{
        std::cout << "unbalanced at argument " << result << std::endl;
        return 1;
    }
}
