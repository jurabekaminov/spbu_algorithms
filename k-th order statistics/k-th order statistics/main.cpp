//
//  main.cpp
//  k-th order statistics
//
//  Created by Jurabek Aminov on 27.03.2022.
//

#include <fstream>

// к-ая порядковая статистика
int kth_order_statistics (int* arr, int left, int right, int k)
{
    while (left < right)
    {
        int k_th = arr[k];
        int i = left, j = right;
        
        while (i <= j)
        {
            while (arr[i] < k_th) i++;
            while (arr[j] > k_th) j--;
            if (i <= j)
            {
                int temp = arr[i];
                arr[i++] = arr[j];
                arr[j--] = temp;
            }
        }
        
        if (j < k) {
            left = i;
        }
        
        if (k < i) {
            right = j;
        }
    }
 
    return arr[k];
}

// работа с данными и файлами
void Program (int argc, const char * argv[]) {
    
    // Работа с файлами
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        exit(2);
    }

    std::ofstream outFile(argv[2]);
    if (!outFile) {
        exit(3);
    }
    
    // инициализируем данные
    int n, k1, k2;
    int a, b, c, x1, x2;
    
    inFile >> n >> k1 >> k2;
    inFile >> a >> b >> c >> x1 >> x2;
    
    // создаем массив и заполняем рекуррентно
    int* arr = new int[n];
    arr[0] = x1;
    arr[1] = x2;
    
    // x[i] = a * x[i - 2] + b * x[i - 1] + c
    for (int i = 2; i < n; ++i) {
        arr[i] = a * arr[i - 2] + b * arr[i - 1] + c;
    }
    
    // выводим k_1, ..., k_2 - 1
    for (int i = k1 - 1; i < k2 - 1; ++i) {
        int x = kth_order_statistics(arr, 0, n - 1, i);
        outFile << x << " ";
    }
    
    // выводим k_2
    outFile << kth_order_statistics(arr, 0, n - 1, k2 - 1);
    
    delete [] arr;
    
    inFile.close();
    outFile.close();
}

int main(int argc, const char * argv[]) {
    
    if (argc < 3) {
        return 1;
    }
    
    Program(argc, argv);
    
    return 0;
}

