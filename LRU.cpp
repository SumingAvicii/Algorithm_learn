#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
        L = new Node(-1, -1), R = new Node(-1, -1);
        L->right = R;
        R->left = L;
    }

    ~LRUCache() {
        cap = 0;
        cout << "析构函数退出" << endl;
        delete L, R;
    }
    int get(int key) {
        if (hash.count(key) == 0) return -1;
        auto p = hash[key];
        //将节点放到表头
        remove(p);
        insert(p);
        return p->val;
    }

    void put(int key, int value) {
        if (hash.count(key)) {
            auto p = hash[key];
            p->val = value;
            remove(p);
            insert(p);
        } else {
            if (hash.size() == cap) {
                auto p = R->left;
                remove(p);
                hash.erase(p->key);
                delete p;
            }

            auto p = new Node(key, value);
            hash[key] = p;
            insert(p);
        }
    }
private:
    struct Node
    {
        int key, val;
        Node *left, *right;
        Node(int _key, int _val) : key(_key), val(_val), left(NULL), right(NULL) {}
    }*L, *R;  //双链表的最左最右节点不存储值
    
    int cap;
    unordered_map<int, Node*> hash;

    void remove(Node *p) {
        p->right->left = p->left;
        p->left->right = p->right;
    }
    void insert(Node *p) {
        p->right = L->right;
        p->left = L;
        L->right->left = p;
        L->right = p;
    }
};


int main() {
    LRUCache LRU = LRUCache(2);
    LRU.put(1, 2);
    cout << LRU.get(1) << endl;
    LRU.put(2, 3);
    LRU.put(3, 4);
    cout << LRU.get(1) << endl;
    cout << LRU.get(2) << endl;
    getchar();
    return 0;
}
