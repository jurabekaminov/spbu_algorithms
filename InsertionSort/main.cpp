#include <iostream>
using namespace std;

void InsertionSort(int* a, int n)
{
  for (int i = 1 ; i < n ; ++i)
  {
    int tmp = a[i];
    int j = i - 1;
    for ( ; j >=0 && a[j] > tmp;)
    {
      a[j+1] = a[j];
      a[j] = tmp;

      j--;
    }
  }
}
int main()
{
  int a[5] = {4, 2, 1, 0, 12};
  InsertionSort(a, 4);
  for (int i = 0; i < 5; ++i)
    cout << a[i] << " ";
  return 0;
}
