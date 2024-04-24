#include <iostream>
using namespace std;

int BinaryPower(int a, int n)
{
  if (n == 0) return 1;
  if (n % 2 == 0)
  {
    int sqrt_res = BinaryPower(a, n / 2);
    return sqrt_res * sqrt_res;
  }
  else
  {
    return BinaryPower(a, n - 1) * a;
  }
}

int main()
{
  int a, n;
  cin >> a >> n;
  cout << BinaryPower(a, n);
  return 0;
}
