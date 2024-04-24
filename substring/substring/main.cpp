#include <iostream>
#include <fstream>


// Решение алгоритмом Кнута-Морриса-Пратта
void build_p(char* substr, int size_of_substr, int* p) {
    p[0] = 0;
    int counter = 0;
    int i = 1;
    while (i < size_of_substr) {
        if (substr[i] == substr[counter]) {
            p[i++] = ++counter;
        }
        else {
            if (counter) {
                counter = p[counter - 1];
            }
            else {
                p[i++] = 0;
            }
        }
    }
}


void finder(char* str, int size_of_str, char* substr, int size_of_substr, int argc, const char * argv[]) {
    int* arr_of_indices = new int[size_of_str]; // массив индексов вхождений
    
    int num_of_occurrences = 0; // количество вхождений
    
    int* p = new int[size_of_substr];
    build_p(substr, size_of_substr, p);

    int i = 0;
    int j = 0;
    
    while (i < size_of_str) {
        if (substr[j] == str[i]) {
            j++;
            i++;
        }
        if (j == size_of_substr) {
            arr_of_indices[num_of_occurrences++] = i - j + 1;
            j = p[j - 1];
        }
        else if (i < size_of_str && substr[j] != str[i]) {

            if (j) {
                j = p[j - 1];
            }
            else {
                ++i;
            }
        }
    }
    
    
    std::ofstream outFile(argv[2]);
    if (!outFile) {
        exit(-3);
    }
    
    outFile << num_of_occurrences << '\n';
    for(int i = 0; i < num_of_occurrences - 1; ++i) {
        outFile << arr_of_indices[i] << ' ';
    }
    outFile << arr_of_indices[num_of_occurrences - 1];
    
    delete [] arr_of_indices;
    delete [] p;
}


// Работа с файлами
void Program(int argc, const char * argv[]) {
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        exit(-2);
    }

    int str_size = 1;
    int substr_size = 1;
    
    // динамические массивы, при переполнении удлиняем в 2 раза
    char* str = new char[str_size];
    char* substr = new char[substr_size];
    
    char c;
    int i = 0;
    while (true) {
        if (!inFile.get(c) || c == '\n') {
            break;
        }
        if(i == substr_size) {
            char* tmp_substr = substr;
            substr = new char[substr_size * 2];
            for (int j = 0; j < substr_size; ++j) {
                substr[j] = tmp_substr[j];
            }
            substr_size *= 2;
            delete [] tmp_substr;
        }
        substr[i++] = c;
    }
    
    char* tmp_substr = substr;
    substr = new char[i + 1];
    
    for(int j = 0; j < i; ++j) {
        substr[j] = tmp_substr[j];
    }
    substr[i] = '\0';
    delete [] tmp_substr;
    
    
    char d;
    int k = 0;
    while (true) {
        if (!inFile.get(d) || d == '\n') {
            break;
        }
        if(k == str_size) {
            char* tmp_str = str;
            str = new char[str_size * 2];
            for (int j = 0; j < str_size; ++j) {
                str[j] = tmp_str[j];
            }
            str_size *= 2;
            delete [] tmp_str;
        }
        str[k++] = d;
    }
    
    char* tmp_str = str;
    str = new char[k + 1];
    
    for(int j = 0; j < k; ++j) {
        str[j] = tmp_str[j];
    }
    str[k] = '\0';
    delete [] tmp_str;
    
    
    finder(str, k ,substr, i, argc, argv);
    
    delete [] str;
    delete [] substr;
}


int main(int argc, const char* argv[])
{
    Program(argc, argv);
    return 0;
}

