#include <iostream>
using namespace std;
// хранить будем массив указателей на начало каждой строки и массив склееных строк
// такая схема эффективнее чем массив массивов
template <typename T>
class d2_array
{
  T **m;
  int rows;
  int size;
public:
  d2_array():m(NULL), rows(0), size(0){}
  d2_array(int rws, int* rows_lenghts);
  d2_array (const d2_array& a);
  ~d2_array();
  void set(int i, int j, int x);
  T get (int i, int j);
  bool operator==(const d2_array& a);
};

template <typename T>
d2_array<T>::d2_array(int rws, int* rows_lenghts)
{
  rows = rws;
  T ** m = new T* [rows];

  size = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    size += rows_lenghts[i];
  }
  m[0] = new int [size];

  for (size_t i = 1; i != rows; ++i)
  {
    m[i] = m[i - 1] + rows_lenghts[i - 1];
  }

  for (size_t i = 0; i < size; ++i)
  {
    m[0][i] = 0;
  }
}

template <typename T>
d2_array<T>::~d2_array()
{
  delete [] m[0];
  delete [] m;
}

template <typename T>
d2_array<T>::d2_array(const d2_array& A):rows(A.rows), size(A.size)
{
  T** m = new T* [rows];
  for (size_t i = 0; i < rows; ++i)
  {
    m[i] = A.m[i];
  }

  for (size_t i = 0; i < A.size; ++i)
  {
    m[0][i] = A.m[0][i];
  }
}


template <typename T>
void d2_array<T>::set(int i, int j, int x)
{
  if(i >= rows) ||
}



int main()
{
  int a = 4;
  int arr[4] = {2, 3, 5 , 1};
  d2_array<int> d(a, arr);

  return 0;
}
