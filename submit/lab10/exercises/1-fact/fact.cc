#include "fact.hh"

unsigned fact(unsigned n) {
  unsigned x = 0;
  if(n == x){
    return 1;
  }
  else{
    return (n <= 1) ? n : n * fact(n - 1);
  }
}
