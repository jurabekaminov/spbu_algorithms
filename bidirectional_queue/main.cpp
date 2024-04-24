#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node* prev = NULL;
  Node* next = NULL;
};

class bidirectional_queue
{
  Node* head;
  Node* tail;
  size_t size;
public:
  bidirectional_queue();
  ~bidirectional_queue();
  bidirectional_queue(const bidirectional_queue& q);
  const bidirectional_queue & operator = (const bidirectional_queue & q);
  void push_back(int x);
  void push_front(int x);
  void pop_back();
  void pop_front();
  int get_back();
  int get_front();
  int capacity();
  bool empty();

};

int main()
{
  cout << "Hello World!" << endl;
  return 0;
}
