#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Item
{
  int weigth;
  int value;
};

bool Comp (const Item &left, const Item &right)
{
  return left.value > right.value;
}

int Max_discrete_knapsack_value(int capacity, vector <Item> items)
{
  sort(items.begin(), items.end(), Comp);

  int knapsack_value = 0;

  for (auto &item:items)
  {
    if (capacity > item.weigth)
    {
      knapsack_value += item.value;
      capacity -= item.weigth;
    }

  }
    return knapsack_value;

}

int main()
{
  int number_of_items, knapsack_capacity;
  cin >> number_of_items >> knapsack_capacity;
  vector <Item> items(number_of_items);

  for (int i = 0; i < number_of_items; ++i)
    cin >> items[i].weigth >> items[i].value;

  int result = Max_discrete_knapsack_value(knapsack_capacity, move(items));
  cout << result;
  return 0;
}
