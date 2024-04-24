#include <iostream>
using namespace std;

int Akkerman (int n, int m)
{
  if (n == 0)
    return m + 1;
  if (m == 0)
    return Akkerman(n - 1, 1);
  if ((m > 0) && (n > 0))
    return Akkerman(n - 1, Akkerman(n , m - 1));
  return 0;
}

int main()
{
  int n, m;
  cin >> n >> m;
  cout << Akkerman(n, m);
  return 0;
}
