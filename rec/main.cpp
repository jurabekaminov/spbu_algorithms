#include <iostream>
using namespace std;

struct Point
{
  double x;
  double y;
};

int main()
{
  int n;
  double res = 0.0;
  Point x, y, prev, current, first;
  cin >> n;
  cin >> first.x >> first.y;
  prev = first;
  for (int i = 1 ; i < n; ++i)
  {
    cin >> current.x >> current.y;
    if (current.x >= prev.x)
      res += (prev.y + current.y)/2*abs((current.x - prev.x));
    else res -= (prev.y + current.y)/2*abs((current.x - prev.x));
    prev = current;
  }

  if ( first.x <= prev.x) res -= abs(prev.x-first.x)*(prev.y+first.y)/2;
  else res += abs(prev.x-first.x)*(prev.y+first.y)/2;

  cout << res;
  return 0;
}
