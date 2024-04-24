#include <iostream>
#include <cassert>

#include "Heap.h"

class TestHeap : public Heap<int> {
  void TestParent() {
    size_t res = Parent(3);
    size_t expected = 1;
    assert(res == expected);
    res = Parent(4);
    assert(res == expected);
  }

  void TestLeft() {
    size_t res = Left(3);
    size_t expected = 7;
    assert(res == expected);
  }

  void TestRight() {
    size_t res = Right(3);
    size_t expected = 8;
    assert(res == expected);
  }

  void TestShiftUpForFirstElement() {
    Heap<int>::heap = { 1, 2, 3 };
    ShiftUp(0);
    std::vector<int> expected = { 1, 2, 3 };
    assert(heap == expected);
  }

  void TestShiftUpForShiftingElement() {
    Heap::heap = { 1, 2, 3 };
    ShiftUp(1);
    std::vector<int> expected = { 2, 1, 3 };
    assert(heap == expected);
  }

  void TestShiftUpForShiftingElement2() {
    Heap::heap = { 1, 2, 1, 3, 4 };
    ShiftUp(4);
    std::vector<int> expected = { 4, 1, 1, 3, 2};
    assert(heap == expected);
  }

  void TestShiftUpForNonShiftingElement() {
    Heap::heap = {3, 2, 1, 3, 4 };
    ShiftUp(1);
    std::vector<int> expected = { 3, 2, 1, 3, 4 };
    assert(heap == expected);
  }

  void TestShiftDownForLeafElement() {
    Heap<int>::heap = { 1, 2, 3 };
    ShiftDown(1);
    std::vector<int> expected = { 1, 2, 3 };
    assert(heap == expected);
  }

  void TestShiftDownForShiftingElement() {
    Heap<int>::heap = { 1, 2, 3 };
    ShiftDown(0);
    std::vector<int> expected = { 3, 2, 1 };
    assert(heap == expected);
  }

  void TestShiftDownForShiftingElement2() {
    Heap<int>::heap = { 1, 2 };
    ShiftDown(0);
    std::vector<int> expected = { 2, 1 };
    assert(heap == expected);
  }

  void TestShiftDownForShiftingElement3() {
    Heap<int>::heap = { 1, 3, 2, 4, 5, 1, 0, 0, 0};
    ShiftDown(0);
    std::vector<int> expected = { 3, 5, 2, 4, 1, 1, 0, 0, 0 };
    assert(heap == expected);
  }
public:
  void TestAll() {
    TestParent();
    TestLeft();
    TestRight();
    TestShiftUpForFirstElement();
    TestShiftUpForShiftingElement();
    TestShiftUpForShiftingElement2();
    TestShiftUpForNonShiftingElement();
    TestShiftDownForLeafElement();
    TestShiftDownForShiftingElement();
    TestShiftDownForShiftingElement2();
    TestShiftDownForShiftingElement3();
  }
};

int main() {
  TestHeap test;
  test.TestAll();

  std::vector<int> arr = {4, 2, 1, 3};
  Heap<int> myHeap(arr);
  myHeap.add(5);
  while (!myHeap.empty()) {
    std::cout << myHeap.top() << " ";
    myHeap.pop();
  }

  return 0;
}
