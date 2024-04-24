  #include <iostream>
  using namespace std;

  template <typename T>
  void heapify(T arr[], int n, int i)
  {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
  }

  template <typename T>
  void heapSort(T arr[], int n)
  {

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);


    for (int i = n - 1; i >= 0; i--)
    {

        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
  }

  template <typename T>
  void printArray(T arr[], int n)
  {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
  }


