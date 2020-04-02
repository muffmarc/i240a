#include "ops.hh"

class Ops2 : public Ops {
public:

    int compCount = 0;
    
    int swapCount = 0;

    /** return < 0, == 0, > 0 if a < b, a == b, a > b */
    int
    compare(int a, int b) {
      compCount ++;
      return this->Ops::compare(a,b);
    }

    /** swap a[i] and a[j] */
    void
    swap(int a[], int i, int j)
    {
      swapCount ++;
      this->Ops::swap(a, i, j);
    }
};
