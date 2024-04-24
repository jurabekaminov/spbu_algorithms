//
//  main.cpp
//  inversions
//
//  Created by Jurabek Aminov on 19.03.2022.
//

#include <fstream>

// Найдем инверсии при помощи модифицированной сортировки слияниями без рекурсии
long long Inversions (int *arr, int n) {
    long long total = 0;
    int* tmp_arr = new int[n];
    int step = 1;
    while (step < n) {
        int index = 0;
        int left = 0, middle = left + step, right = left + step * 2;
        do {
            middle = std::min(middle, n);
            right = std::min(right, n);
            int start1 = left, start2 = middle;
           
            while (start1 < middle && start2 < right) {
                if (arr[start1] <= arr[start2]) {
                    tmp_arr[index++] = arr[start1++];
                }
                else {
                    tmp_arr[index++] = arr[start2++];
// находим количество инверсий
                    total += middle - start1;
                }
            }
          
            while (start1 < middle) {
                tmp_arr[index++] = arr[start1++];
            }
          
            while (start2 < right) {
                tmp_arr[index++] = arr[start2++];
            }
          
            left += step * 2;
            middle += step * 2;
            right += step * 2;
          
      } while (left < n);
        
        for (int i = 0; i < n; i++) {
            arr[i] = tmp_arr[i];
        }
        
        step *= 2;
    }
    delete[] tmp_arr;
    return total;
}

// Работа с файлами и основная логика программы
void Program (int argc, const char * argv[]) {
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        exit(2);
    }
    std::ofstream outFile(argv[2]);
    if (!outFile) {
        exit(3);
    }
    
    int n;
    inFile >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        inFile >> arr[i];
    }
    
    outFile << Inversions(arr, n);
    
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
