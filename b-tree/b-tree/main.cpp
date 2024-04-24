#include <fstream>


class Btree {
public:
    struct Node {
        int* key;
        Node** ptr;
        int size;

        Node(int t, bool leaf) {
            size = 0;
            key = new int[2 * t - 1];
            if (leaf) {
                ptr = nullptr;
            }
            else {
                ptr = new Node * [2 * t];
                for (int i = 0; i < 2 * t; ++i) {
                    ptr[i] = nullptr;
                }
            }
        }

        ~Node() {
            if (key) {
                delete[] key;
                key = nullptr;
            }
            if (ptr) {
                delete[] ptr;
                ptr = nullptr;
            }
        }

        void make_empty() {
            if (size > 0 && ptr) {
                for (int i = 0; i <= size; ++i) {
                    if (ptr[i]) {
                        ptr[i]->make_empty();
                        delete ptr[i];
                    }
                }
            }
        }

        void insert(int position, int newKey, Node* left = nullptr, Node* right = nullptr) {
            for (int i = size; i > position; --i) {
                key[i] = key[i - 1];
            }
            key[position] = newKey;
            if (ptr) {
                for (int i = size + 1; i > position + 1; --i) {
                    ptr[i] = ptr[i - 1];
                }
                ptr[position] = left;
                ptr[position + 1] = right;
            }
            ++size;
        }

        void add_to_left(int newKey, Node* left = nullptr) {
            if (ptr) {
                insert(0, newKey, left, ptr[0]);
            }
            else {
                insert(0, newKey, left);
            }
        }

        void add_to_right(int newKey, Node* right = nullptr) {
            key[size] = newKey;
            ++size;
            if (ptr) {
                ptr[size] = right;
            }
;       }

        int erase(int k, Node* replace = nullptr) {
            int r = key[k];
            for (int i = k; i < size - 1; ++i) {
                key[i] = key[i + 1];
            }
            if (ptr) {
                for (int i = k; i < size; ++i) {
                    ptr[i] = ptr[i + 1];
                }
                ptr[k] = replace;
            }
            --size;
            return r;
        }

        int pop_left() {
            if (ptr) {
                return erase(0, ptr[1]);
            }
            return erase(0);
        }

        int pop_right() {
            --size;
            return key[size];
        }
    };

private:
    int t;
    Node* root;
private:

    bool is_full(Node* x) {
        return x->size == 2 * t - 1;
    }

    void split(Node*& parent, int c) {
        Node* left;
        Node* right;
        if (parent) {
            left = parent->ptr[c];
        }
        else {
            parent = new Node(t, false);
            left = root;
            root = parent;
        }
        right = new Node(t, !left->ptr);
        parent->insert(c, left->key[t - 1], left, right);
        left->size = t - 1;
        right->size = t - 1;
        for (int i = 0; i < t - 1; ++i) {
            right->key[i] = left->key[t + i];
        }
        if (left->ptr) {
            for (int i = 0; i < t; ++i) {
                right->ptr[i] = left->ptr[t + i];
            }
        }
    }
    
    Node* grab_from_right(Node* parent, int c) {
        Node* left = parent->ptr[c];
        Node* right = parent->ptr[c + 1];
        if (right->ptr) {
            left->add_to_right(parent->key[c], right->ptr[0]);
        }
        else {
            left->add_to_right(parent->key[c]);
        }
        parent->key[c] = right->pop_left();
        return left;
    }

    Node* grab_from_rleft(Node* parent, int c) {
        Node* left = parent->ptr[c - 1];
        Node* right = parent->ptr[c];
        if (left->ptr) {
            right->add_to_left(parent->key[c - 1], left->ptr[left->size]);
        }
        else {
            right->add_to_left(parent->key[c - 1]);
        }
        parent->key[c - 1] = left->pop_right();
        return right;
    }

    Node* merge_right(Node*& parent, int c) {
        Node* left = parent->ptr[c];
        Node* right = parent->ptr[c + 1];
        if (right->ptr) {
            left->add_to_right(parent->erase(c, left), right->ptr[0]);
            for (int i = 0; i < t - 1; ++i) {
                left->add_to_right(right->key[i], right->ptr[i + 1]);
            }
        }
        else {
            left->add_to_right(parent->erase(c, left));
            for (int i = 0; i < t - 1; ++i) {
                left->add_to_right(right->key[i]);
            }
        }
        delete right;
        if (parent->size == 0) {
            delete root;
            root = left;
        }
        return left;
    }

    Node* merge_left(Node*& parent, int c) {
        return merge_right(parent, c - 1);
    }

    Node* balance(Node* cur, Node*& parent, int c) {
        if (cur->size > t - 1 || cur == root) return cur;
        if (c > 0) {
            if (c < parent->size) {
                if (parent->ptr[c + 1]->size > parent->ptr[c - 1]->size) {
                    return grab_from_right(parent, c);
                }
                else if (parent->ptr[c - 1]->size > t - 1) {
                    return grab_from_rleft(parent, c);
                }
                else {
                    return merge_left(parent, c);
                }
            }
            else if (parent->ptr[c - 1]->size > t - 1) {
                return grab_from_rleft(parent, c);
            }
            else {
                return merge_left(parent, c);
            }
        }
        else if (parent->ptr[c + 1]->size > t - 1) {
            return grab_from_right(parent, c);
        }
        else {
            return merge_right(parent, c);
        }
        return cur;
    }

public:
    Btree(int t) : t(t) {
        root = new Node(t, true);
    }

    ~Btree() {
        if(root) {
            root->make_empty();
            delete root;
            root = nullptr;
        }
    }
    
    Node* get_root() {
        return root;
    }

    bool search(int key) {
        Node* cur = root;
        if (root->size == 0) return false;
        while (cur) {
            for (int i = 0; i < cur->size; ++i) {
                if (key == cur->key[i]) {
                    return true;
                }
                if (key < cur->key[i]) {
                    if (cur->ptr) {
                        cur = cur->ptr[i];
                    }
                    else {
                        cur = nullptr;
                    }
                    break;
                }
                if (i == cur->size - 1) {
                    if (cur->ptr) {
                        cur = cur->ptr[i + 1];
                    }
                    else {
                        cur = nullptr;
                    }
                    break;
                }
            }
        }
        return false;
    }

    void insert(int key) {
        Node* parent = nullptr;
        int c = 0;
        Node* cur = root;
        while (true) {
            if (is_full(cur)) {
                split(parent, c);
                if (key < parent->key[c]) {
                    cur = parent->ptr[c];
                }
                else {
                    cur = parent->ptr[c + 1];
                }
            }
            if (!cur->ptr) break;
            for (int i = 0; ; ++i) {
                if (key < cur->key[i]) {
                    parent = cur;
                    c = i;
                    cur = cur->ptr[i];
                    break;
                }
                if (i == cur->size - 1) {
                    parent = cur;
                    c = i + 1;
                    cur = cur->ptr[i + 1];
                    break;
                }
            }
        }
        int k = 0;
        for (; k < cur->size; ++k) {
            if (key < cur->key[k]) break;
        }
        cur->insert(k, key);
    }

    void erase(int key, Node* cur = nullptr) {
        if (!cur) {
            cur = root;
        }
        Node* parent = nullptr;
        int c = 0;
        int k = -1;
        while (k == -1) {
            cur = balance(cur, parent, c);
            for (int i = 0; ; ++i) {
                if (key == cur->key[i]) {
                    k = i;
                    break;
                }
                if (key < cur->key[i]) {
                    parent = cur;
                    c = i;
                    if (cur->ptr) {
                        cur = cur->ptr[i];
                    }
                    else {
                        cur = nullptr;
                    }
                    break;
                }
                if (i + 1 == cur->size) {
                    parent = cur;
                    c = i + 1;
                    if (cur->ptr) {
                        cur = cur->ptr[i + 1];
                    }
                    else {
                        cur = nullptr;
                    }
                    break;
                }
            }
        }
        if (!cur->ptr) {
            cur->erase(k);
        }
        else if (cur->ptr[k]->size > t - 1) {
            cur->key[k] = erase_max(cur, k);
        }
        else if (cur->ptr[k + 1]->size > t - 1) {
            cur->key[k] = erase_min(cur, k + 1);
        }
        else {
            erase(key, merge_right(cur, k));
        }
    }

    int erase_min(Node* parent = nullptr, int c = 0) {
        Node* cur = root;
        if (parent) {
            cur = parent->ptr[c];
        }
        while (true) {
            cur = balance(cur, parent, c);
            if (!cur->ptr) break;
            parent = cur;
            c = 0;
            cur = parent->ptr[c];
        }
        return cur->pop_left();
    }

    int erase_max(Node* parent = nullptr, int c = 0) {
        Node* cur = root;
        if (parent) {
            cur = parent->ptr[c];
        }
        while (true) {
            cur = balance(cur, parent, c);
            if (!cur->ptr) break;
            parent = cur;
            c = parent->size;
            cur = parent->ptr[c];
        }
        return cur->pop_right();
    }

};


// Работа с файлами
void Program(int argc, char* argv[]) {
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        exit(2);
    }
    std::ofstream outFile(argv[2]);
    if (!outFile) {
       exit(3);
    }

    int t;
    inFile >> t;
    Btree tree(t);

    int N;
    inFile >> N;
    for (int i = 0; i < N; ++i) {
        char ch;
        int X;
        inFile >> ch;
        inFile >> X;
        if (ch == '+') {
            tree.insert(X);
            Btree::Node* root = tree.get_root();
            outFile << root->size;
            if (root->size > 0) {
                for (int i = 0; i < root->size; ++i) {
                    outFile << ' ' << root->key[i];
                }
            }
            outFile << "\n";
        }
        else if (ch == '-') {
            tree.erase(X);
            Btree::Node* root = tree.get_root();
            outFile << root->size;
            if (root->size > 0) {
                for (int i = 0; i < root->size; ++i) {
                    outFile << ' ' << root->key[i];
                }
            }
            outFile << "\n";
        }
        else if (ch == '?') {
            if (tree.search(X)) {
                outFile << "true\n";
            }
            else {
                outFile << "false\n";
            }
        }
    }

    inFile.close();
    outFile.close();
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }
    Program(argc, argv);
    return 0;
}
