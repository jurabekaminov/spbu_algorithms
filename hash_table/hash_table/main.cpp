#include <fstream>
#include <iostream>


// Реализация списка для хеш-таблицы (только необходимое)
class table_list {
    struct node {
        int data;
        node* next;
        node(int value): data(value), next(nullptr) {}
    };
    node* head;
    node* tail;
public:
    table_list(): head(nullptr), tail(nullptr) {}
    ~table_list() {
        node* tmp = nullptr;
        while (head) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
    }
    
    bool is_empty() {
        return head == nullptr;
    }
    
    void push_back(int value) {
        node* tmp_node = new node(value);
        if (is_empty()) {
            head = tmp_node;
            tail = tmp_node;
            return;
        }
        tail->next = tmp_node;
        tail = tmp_node;
    }
    
    node* search(int value) {
        node* tmp_node = head;
        while (tmp_node && tmp_node->data != value) {
            tmp_node = tmp_node->next;
        }
        return (tmp_node && tmp_node->data == value) ? tmp_node : nullptr;
    }
    
    void remove_first() {
        if (is_empty()) {
            return;
        }
        node* tmp = head;
        head = tmp->next;
        delete tmp;
    }
    
    void remove_last() {
        if (is_empty()) {
            return;
        }
        if (head == tail) {
            remove_first();
            return;
        }
        node* tmp = head;
        while (tmp->next != tail) {
            tmp = tmp->next;
        }
        tmp->next = nullptr;
        delete tail;
        tail = tmp;
    }
    
    void remove(int value) {
        if (is_empty()) {
            return;
        }
        if (head->data == value) {
            remove_first();
            return;
        }
        else if (tail->data == value) {
            remove_last();
            return;
        }
        node* slow = head;
        node* fast = head->next;
        while (fast && fast->data != value) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
    
};


// проверка числа на простоту
bool is_prime(int number) {
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}


// выбор размера таблицы - следующее простое число после n / 3
int select_m(int n) {
    int m = n / 3 + 1;
    int i = 0;
    while (!is_prime(i + m)) {
        ++i;
    }
    return i + m;
}


// хеш-таблица: хеширование с цепочками, метод деления
class hash_table {
    int m;
    table_list* table;
public:
    hash_table(int m);
    void insert(int value);
    void remove(int value);
    int hash_function(int x);
    bool find(int value);
};


// метод деления
int hash_table::hash_function(int x) {
    return x % m;
}


// конструктор
hash_table::hash_table(int m) {
    this->m = m;
    table = new table_list[m];
}


// вставка в таблицу
void hash_table::insert(int value) {
    table[hash_function(value)].push_back(value);
}


// удаление
void hash_table::remove(int value) {
    int index = hash_function(value);
    table[index].remove(value);
}


// поиск
bool hash_table::find(int value) {
    int index = hash_function(value);

    if (table[index].search(value)) {
        return true;
    }
    return false;
}


// Работа с файлами
void Program(int argc, const char * argv[]) {
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        exit(-2);
    }
    
    std::ofstream outFile(argv[2]);
    if (!outFile) {
        exit(-3);
    }

    int n;
    inFile >> n;
    
    int m = select_m(n);
    hash_table table(m);
    
    for(int i = 0; i < n; ++i) {
        char c;
        std::string s;
        inFile >> c >> s;
        if (c == '+') {
            table.insert(std::stoi(s));
        }
        else if (c == '-') {
            table.remove(std::stoi(s));
        }
        else if (c == '?') {
            if (table.find(std::stoi(s))) {
                outFile << "true" << '\n';
            }
            else {
                outFile << "false" << '\n';
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    if (argc<3) {
        return -1;
    }
    Program(argc, argv);
    return 0;
}

