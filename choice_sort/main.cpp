#include <iostream>
using namespace std;

void SelectionSort(int* a, int n)
{
  for (int i = 0 ; i < n - 1; ++i)
  {
    int minIndex = i;
    for (int j = i + 1 ; j < n ; ++j)
      if ( a[j] < a[minIndex] )
      {
        minIndex = j;
      }
    if (minIndex != i)
    {
      swap (a[i], a[minIndex]);
    }
  }
}
int main()
{
  int a[5] = {0, 2, 1, 5, 3};
  SelectionSort(a, 5);
  for (int i = 0; i < 5; ++i)
    cout << a[i] << " ";
  return 0;
}
