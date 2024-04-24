#include <iostream>

using namespace std;

int size(const char * c)
{
  int res = 0;
  for (; *c != '\0'; c++)
    res ++;
  return res;
}

int strstr(const char *text, const char *pattern)
{
  if (*pattern == '\0') return 0;
  int  pat_size = size(pattern);
  int text_size = size(text);
  for (auto i = 0; i <= text_size - pat_size; ++i)
  {
    int temp = 0;
    for (auto j = i; j < i + pat_size; ++j)
      if (text[j] == pattern[j - i])
        temp++;
    if (temp == pat_size) return i;
  }
  return -1;
}
int sum_of_squares (int x)
{
  int sum = 0;
  for (int i = 1; i <= x; ++i)
    sum += i*i;
  return sum;
}
int main()
{
  char a[] {"a"};
  char b[] {""};
  cout << strstr(a, b);

}
