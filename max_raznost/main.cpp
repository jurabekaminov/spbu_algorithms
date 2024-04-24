// Need to find i,j; i >= j: A[i] - A[j] = max
#include <iostream>
#include <vector>
using namespace std;
pair<int, int> max_sub_int (const vector <int>& mass)
{
  if (mass.size() == 0) return {-1, -1};
  int i0 = 0, j0 = 0;
  int locmin = 0, max_sub = 0;
  for (int i = 0; i < mass.size(); ++i)
  {
    if (mass[i] - mass[locmin] > mass[i0] - mass[j0])
    {
      i0 = i;
      j0 = locmin;
    }
    if (mass[locmin] > mass[i])
      locmin = i;
  }
}

int main()
{
}
