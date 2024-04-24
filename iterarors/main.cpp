#include <iostream>
#include <queue>
using namespace std;


class F
{
public:
  int operator()(const int x)
  {
    return x / 2;
  }
};

struct Node
{
  int data;
  Node* next;
  Node* prev;
};


class Cycled_List
{
  Node* first;
  Node* last;
  size_t size;
  friend class listIter;
};

class listIter
{
  queue<Node*> q;
  bool start = false;
  Node* first;

  listIter(Cycled_List &L): start(true), first(L.first)
  {
   q.push(L.first);
  }
  bool beg()
  {
    return start;
  }
  bool end()
  {
    return q.empty();
  }
  int& operator*()
  {
    return q.front()->data;
  }
  listIter& operator++();
  void for_each(Cycled_List L, F f);

};


listIter& listIter::operator++()
{
  if(start)
  {
    start = false;
  }
  Node *tmp = q.front();
  q.pop();
  if(tmp->next != first)
  {
    q.push(tmp->next);
  }
  return *this;
}

void listIter::for_each(Cycled_List L, F f)
{
  for(listIter iter(L); !iter.end(); ++iter)
  {
    f(*iter);
  }
}

int main()
{
  cout << "Hello, world";
  return 0;
}
