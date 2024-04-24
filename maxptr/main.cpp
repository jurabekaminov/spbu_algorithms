#include <iostream>

using namespace std;

bool max_element (int * p, int * q, int * res)
{
  if ( p == q)
    return false;
    * res = * p;
    for (; p != q; ++p)
      if (*p > *res)
        *res = *p;
    return true;
}

int main()
{
  int a[5] {1, 2, 3, 6, 5};
  int max = 0;
  if (max_element(a, a + 5, &max))
    cout << "Maximum = " << max;
}
