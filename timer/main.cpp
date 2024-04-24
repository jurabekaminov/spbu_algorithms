#include <iostream>

using namespace  std;
int main()
{
  int a[] {1, 2 , 3 , 4, 5};
  int shift = 2;
  for (int i = shift ; i <= 5; ++i)
  {
    a[i] = a[i + shift];
  }

  for (int i = 0; i < 5; i ++ )
    cout << a[i] << " ";

}
