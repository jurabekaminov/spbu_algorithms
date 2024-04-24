#include <iostream>
using namespace std;

void Delete_chet (int* a, int &n)
{
  int num_of_chet {0};
  if (a[n - 1] % 2 == 0) n--;
  for (int i = 0; i < n - 1; ++i)
  {
    if (a[i] % 2 == 0)
    {
      for (int j = i;  j < n - 1; ++j)
        a[j] = a[j + 1];
      num_of_chet++;
    }
  }
  n -= num_of_chet;
}

int main()
{
  int n {5};
  int a[5] = {1,2,3,4,5};
  Delete_chet(a, n);
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";

  return 0;
}
