#include <iostream>

using namespace std;

int BinarySearch2( double* arr, int count, double element )
{
int first = 0;
int last = count; // Элемент в last не учитывается.
while( first < last ) {
int mid = ( first + last ) / 2;
if( element <= arr[mid] )
last = mid;
else
first = mid + 1; // Здесь отличие от BinarySearch1.

}
// Все элементы слева от first строго больше искомого.
return ( first == count || arr[first] != element ) ? -1 : first;
}
int main()
{
  double  a[7];
  for (int i = 0 ;  i < 6; ++i)
    cin >> a[i];
  cout << BinarySearch2(a, 7, 4);
  return 0;
}
