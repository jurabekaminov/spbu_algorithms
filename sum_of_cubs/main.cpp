//Написать программу находящую среднее арифметическое кубов последовательности чисел;
#include <iostream>
using namespace std;

double Avg_sum_of_cubes (double* a, int n)
{
  double res = 0;
  for (int i = 0; i < n; ++i)
    res += (a[i]*a[i]*a[i])/n;
  return res;
}

int main()
{
  int n;
  cin >> n;
  double a[n+1];
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  cout << Avg_sum_of_cubes(a, n);
  return 0;
}
