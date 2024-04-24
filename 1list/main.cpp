#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node* next;
  Node(): data (0), next (NULL) {}
};

class List
{
  Node* head;
public:
  List() { head = NULL;}
  void InsertAfter (Node* node, int a);
  Node* Search (Node* head, int a);
  void DeleteNode (int a);
  void DeleteAt (Node* node);
  void print();
  void add (int a);
  void reverse ();

};

void List:: add(int a)
{
  Node* temp = new Node;
  temp->data = a;
  temp->next = head;
  head = temp;
}

void List::print()
{
  Node* temp = head;
  while (temp != NULL)
  {
   cout << temp->data << " ";
   temp = temp->next;
  }
}

void List::reverse()
{
  Node* current = head;
  Node *prev = NULL, *next = NULL;
  while (current != NULL)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
    head = prev;
}

int main()
{
  List l;
  l.add(30);
  l.add(20);
  l.add(10);

  cout << "Before reverse " << endl;
  l.print();

  l.reverse();
  cout << endl << " After reverse " << endl;
  l.print();

  return 0;
}
