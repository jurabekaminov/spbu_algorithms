#include <iostream>
using namespace std;

int main()
{
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  int length_of_LIS_till[n];
  length_of_LIS_till[0] = 1;

  for (int i = 1; i < n; ++i)
  {
      if (a[i - 1] < a[i])
        length_of_LIS_till[i] = length_of_LIS_till[i - 1] + 1;
      else
        length_of_LIS_till[i] = 1;
  }

  int max_length = length_of_LIS_till[0];
  int pos_max_length = 0;

  for (int i = 1; i < n; ++i)
  {
    if (length_of_LIS_till[i] > max_length)
    {
      max_length = length_of_LIS_till[i];
      pos_max_length = i;
    }
  }

  for (int i = pos_max_length + 1 - max_length; i < pos_max_length + 1; ++i)
    cout << a[i] << " ";
  return 0;
}
