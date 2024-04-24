#include <iostream>
using namespace std;

void Merge (int* a, int a_len, int* b, int b_len, int* c)
{
  int i = 0, j = 0;
  while (i < a_len && j < b_len )
  {
    if (a[i] <= b[j])
    {
      c[i + j] = a[i];
      ++i;
    }
    else
    {
      c[i + j] = b[j];
      ++j;
    }
  }

  // остаток
  if (i == a_len)
  {
    for (; j < b_len; ++j)
      c[i + j] = b[j];
  }

  else
  {
    for (; i < a_len; ++i)
      c[i + j] = a[i];
  }

}

void MergeSort (int* a, int l, int r)
{
  int mid = (l + r) / 2;

}





















































//void Merge( const int* a, int aLen, const int* b, int bLen, int* c ) {
//int i = 0, j = 0;
//while(  i < aLen && j < bLen ) {
//if( a[i] <= b[j] ) {
//c[i + j] = a[i];
//++i;
//} else {
//c[i + j] = b[j];
//++j;
//}
//}
//// Обработаем остаток.
//if( i == aLen ) {
//for( ; j < bLen; ++j )
//c[i + j] = b[j];

//} else {
//for( ; i < aLen; ++i )
//c[i + j] = a[j];

//}
//}

//void MergeSort( int* a, int aLen ) {
//if( aLen <= 1 ) {
//return;
//}
//int firstLen = aLen / 2;
//int secondLen = aLen - firstLen;
//MergeSort( a, firstLen );
//MergeSort( a + firstLen, secondLen );
//int* c = new int[aLen];
//Merge( a, firstLen, a + firstLen, secondLen, c );
//memcpy( a, c, sizeof( int ) * aLen );
//delete[] c;
//}
//int main()
//{
//  int a[5] = {1, 3 ,0 -2 ,9};
//  MergeSort(a, 5);
//  for (int i = 0 ; i < 5; ++i)
//    cout << a[i] << " ";
//}
