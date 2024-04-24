#include <iostream>
using namespace std;

  struct ListNode
  {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {

          ListNode *ptr = head;
          while (ptr != NULL && ptr->next != NULL)
          {
              if (ptr->next->val == ptr->val)
              {
                  ptr->next = ptr->next->next;
              }
              else
              {
                  ptr = ptr->next;
              }
          }
          return head;


    }
};
