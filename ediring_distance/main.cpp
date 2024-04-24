//Даны два слова на алфавите {A,C,G,T}. Найти минимальное количество операций добавления, удаления и замены буквы необходимые для приведения слова A к B.
//Найти выравнивание строки A относительно B

#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
using namespace std;

int get_editing_distance(const string &a, const string &b)
{

  size_t n = a.size();
  size_t m = b.size();
  int d[2][m + 1];

  for (size_t i = 0 ; i <= n; ++i)
    d[i & 1][0] = i;

  for (size_t j = 0;  j <= m ; ++j)
    d[0 & 1][j] = j;

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      int delete_distance = d[(i - 1) & 1][j] + 1;
      int insert_distance = d[i & 1][j - 1] + 1;
      int match_distance =  d[(i - 1 & 1)][j - 1] + (a[n - i] != b[m - j]);
      d[i & 1][j] = min (min (delete_distance, insert_distance), match_distance);
    }
  }

  return d[n & 1][m];
}

int main()
{
  string a, b;
  getline(cin, a);
  getline(cin, b);
  cout << get_editing_distance(a, b);
  return 0;
}
