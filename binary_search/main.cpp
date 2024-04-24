#include <iostream>
#include <fstream>
using namespace std;

int Binary_search (int* arr, int n , int element)
{
  int first = 0;
  int last = n;
  while (first < last)
  {
    int mid = (first + last) / 2;
    if (arr[mid] >= element)
      last = mid;
    else
      first = mid + 1;
  }
  return (first == n || arr[first] != element) ? -1: first;
}

int main()
{
  int arr[10] = {0, 2, 4 ,5, 7, 8, 10, 12, 14, 16};
  int res[5];

  res[0] = Binary_search(arr, 10, 0); // 0
  res[1] = Binary_search(arr, 10, 99); // -1
  res[2] = Binary_search(arr, 10, 8); // 5
  res[3] = Binary_search(arr, 10, 12); // 7
  res[4] = Binary_search(arr, 10, 1); // -1

  fstream test_file;
  test_file.open("C:\\Users\\Jurabek Aminov\\Desktop\\SPBSU C++ projects\\chance.txt");
  int x, tmp = 1;

  if (test_file)
  {
    while ((!test_file.eof()) && (tmp != 6))
    {
      test_file >> x;
      if (res[tmp - 1] == x)
      {
        cout << "Test " << tmp << " is correct!" << endl;
      }

      else
      {
           cout << "Test " << tmp << " is wrong!" << endl;
      }
      tmp++;
    }
  }

  test_file.close();
  return 0;
}
