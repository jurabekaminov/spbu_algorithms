#include <iostream>
using namespace std;

class Triple_Heap
{
  int* head;
  int size;
public:
  Triple_Heap();
  Triple_Heap(int x);
  Triple_Heap(const Triple_Heap& t);
  void add(int x);
  void out();
  void heapify(int i); // упорядочивание кучи
  int get_max();
};

void Triple_Heap::heapify(int i) // понадобится для извлечения максимума
{
  int left = 3 * i + 1 ,
      middle = 3 * i + 2,
      right = 3 * i + 3;

  if (left < size)
  {
    if (head[i] < head[left])
    {
      swap(head[i], head[left]);
      heapify(left);
    }
  }

  if (middle < size)
  {
    if (head[i] < head[middle])
    {
      swap(head[i], head[middle]);
      heapify(middle);
    }
  }

  if (right < size)
  {
    if (head[i] < head[right])
    {
      swap(head[i], head[right]);
      heapify(right);
    }
  }
}

Triple_Heap::Triple_Heap(const Triple_Heap& t)
{
  size = t.size;
  head = new int [size];
  for (int i = 0; i < size; ++i)
  {
    head[i] = t.head[i];
  }
}

int Triple_Heap::get_max()
{
  int res = head[0];
  head[0] = head[size - 1];
  size--;
  heapify(0);
  return res;
}


int main()
{
  cout << "Hello World!" << endl;
  return 0;
}
