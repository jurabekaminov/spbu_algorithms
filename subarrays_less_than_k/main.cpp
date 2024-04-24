#include <iostream>
#include <vector>
using namespace std;


int subarrs_less_than_k(vector <int> v, int k)
{

  int temp_sum = 0, res =0;

  int j = 0;
  for (int i = 0 ; i < v.size(); ++i)
  {
    temp_sum += v[i];
    while ((temp_sum > k) && (i > j))
    {
      temp_sum -= v[j];
      ++j;
    }
    if (temp_sum <= k)
    {

      res += (i - j + 1);
    }
  }
  return res;
}

int main()
{
  int n, k;
  cin >> n >> k;
  vector <int> vec(n);

  for (int i = 0; i < n; ++i)
    cin >> vec[i];

  int result = subarrs_less_than_k(move(vec), k);
  cout << result;

  return 0;
}
