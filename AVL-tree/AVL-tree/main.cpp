#include<iostream>
#include <fstream>
#include <string>


// Узел АВЛ-дерева
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
};
   
   
int height(AVLNode *n) {
    return n == nullptr ? 0 : n->height;
}


// Создание узла
AVLNode* create_node(int key) {
    AVLNode* node = new AVLNode();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}


// Правый поворот
AVLNode* right_rotate(AVLNode* node) {
    AVLNode* l = node->left;
    AVLNode* lr = l->right;
   
    // поворот
    l->right = node;
    node->left = lr;
   
    // обновляем высоты
    node->height = std::max(height(node->left), height(node->right)) + 1;
    l->height = std::max(height(l->left), height(l->right)) + 1;
    
    return l;
}
   

// Левый поворот
AVLNode* left_rotate(AVLNode* node) {
    AVLNode* r = node->right;
    AVLNode* rl = r->left;
   
    // поворот
    r->left = node;
    node->right = rl;
    
    // обновляем высоты
    node->height = std::max(height(node->left), height(node->right)) + 1;
    r->height = std::max(height(r->left), height(r->right)) + 1;
   
    return r;
}
   

// Баланс узла
int get_balance(AVLNode *node) {
    return node == nullptr ? 0 : height(node->right) - height(node->left);
}


// Операция вставки
AVLNode* insert(AVLNode* node, int key) {
    
    if (node == nullptr)
        return(create_node(key));
   
    if (key < node->key){
        node->left = insert(node->left, key);
    }
    
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    
    else {
        return node;
    }
   
    node->height = 1 + std::max(height(node->left), height(node->right));
   
    // Проверка разбалансированности дерева
    int balance = get_balance(node);
   
    // 1 случай
    if (balance < -1 && key < node->left->key) {
        return right_rotate(node);
    }

    // 2 случай
    if (balance > 1 && key > node->right->key){
        return left_rotate(node);
    }
    
    // 3 случай
    if (balance < -1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
   
    // 4 случай
    if (balance > 1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    
    return node;
}

   
// Минимальный узел
AVLNode * min_node(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}


// Удаление узла
AVLNode* delete_node(AVLNode* root, int key) {
    if (root == nullptr) {
        return root;
    }
    
    if (key < root->key ) {
        root->left = delete_node(root->left, key);
    }
    
    else if (key > root->key) {
        root->right = delete_node(root->right, key);
    }
    
    else {
        // узел с одним потомком или без потомков
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode *temp = root->left ? root->left : root->right;
   
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        
        else {
            AVLNode* temp = min_node(root->right);
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key);
        }
    }
   
    if (root == nullptr) {
        return root;
    }
    
    // обновляем высоту
    root->height = 1 + std::max(height(root->left), height(root->right));
    
    // проверка дерева на разбалансированность
    int balance = get_balance(root);
  
    // 1 случай
    if (balance < -1 && get_balance(root->left) <= 0) {
        return right_rotate(root);
    }

    // 2 случай
    if (balance < -1 &&  get_balance(root->left) > 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // 3 случай
    if (balance > 1 &&  get_balance(root->right) >= 0) {
        return left_rotate(root);
    }
   
    // 4 случай
    if (balance > 1 && get_balance(root->right) < 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    
    return root;
}


// Проверка на наличие узла
std::string find_node (AVLNode* root, int value) {
    AVLNode* current = root;
    if (current == nullptr) {
        return "false";
    }
    if (current->key == value) {
        return "true";
    }
    
    if (current->key < value) {
        return find_node(current->right, value);
    }
    
    if (current->key > value) {
        return find_node(current->left, value);
    }
    
    return "false";
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
    
    AVLNode* tree = nullptr;
    
    for(int i = 0; i < n; ++i) {
        char c;
        std::string s;
        inFile >> c >> s;
        if (c == '+') {
            tree = insert(tree, stoi(s));
            outFile << get_balance(tree) << "\r\n";
        }
        else if (c == '-') {
            tree = delete_node(tree, stoi(s));
            outFile << get_balance(tree) << "\r\n";
        }
        else if (c == '?') {
            outFile << find_node(tree, stoi(s)) + "\r\n";
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
