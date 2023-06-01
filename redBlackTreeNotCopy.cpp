/*
Note: This code does not copies values while deleting
*/
#include<iostream>
#include "plf_nanotimer.h"
using namespace std;

#define INFO_MSG(msg) printf("[%d][%s] %s\n", __LINE__, __func__, msg);
// #define INFO_MSG(msg);
#define print1(a) std::cout << "[" << __LINE__ << "]"  << #a": " << a \
    << std::endl;
#define print2(a, b) std::cout << "[" << __LINE__ << "]" << #a": " << a \
    << ", "#b": " << b << std::endl;
#define print3(a, b, c) std::cout << "[" << __LINE__ << "]"  << #a": " << a \
    << ", "#b": " << b << ", "#c": " << c << std::endl;
#define print4(a, b, c, d) std::cout << "[" << __LINE__ << "]"  << #a": " << a \
    << ", "#b": " << b << ", "#c": " << c << ", "#d": " << d << std::endl;
#define print5(a, b, c, d, e) std::cout << "[" << __LINE__ << "]"  \
    << #a": " << a << ", "#b": " << b << ", "#c": " << c << ", "#d": " << d \
    << ", "#e": " << e << std::endl;

#define yellow "\x1b[33m"
#define black "\x1b[30m"
#define red "\x1b[31m"
#define green "\x1b[32m"
#define warning ""
#define error ""
#define nocolor "\x1b[0m"

// #define yellow ""
// #define black ""
// #define red ""
// #define green ""
// #define warning ""
// #define error ""
// #define nocolor ""

plf::nanotimer timer1;

typedef struct node{
    int key, val, l, r, lc, rc;
    bool isRed;
    node* left, *right, *parent;
}Node;

#define POOLSIZE 1024
Node* pool = (Node*)malloc(POOLSIZE*sizeof(Node));
Node* freeList = NULL;

void initializePool(){
    freeList = pool;
    for(int i = 0; i < POOLSIZE-1; i++){
        Node** tmp = (Node**)(&pool[i]);
        *tmp = &pool[i+1];
    }
    Node** tmp = (Node**)(&pool[POOLSIZE-1]);
    *tmp = NULL;
}

Node* allocMem(){
    if(freeList == NULL)
        return (Node*)malloc(1*sizeof(Node));
    Node* node = freeList;
    freeList = *(Node**)freeList;
    return node;
}

void freeMem(Node* node){
    Node** tmp = (Node**)node;
    *tmp = freeList;
    freeList = node;
    return;
}

Node* getNewNode(int key,const int& val, bool isRed){
    Node* node = allocMem();
    node->key = key;
    node->val = val;
    node->l = 0;
    node->r = 0;
    node->lc = 0;
    node->rc = 0;
    node->isRed = isRed;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

class RedBlackTree{
    Node* root;
    int numNodes;
public:
    RedBlackTree(){
        root = NULL;
        numNodes = 0;
    }

    Node* _getNewNode(int key, int val, bool isRed){
        numNodes++;
        return getNewNode(key, val, isRed);
    }

    void freeNode(Node* node){
        numNodes--;
        freeMem(node);
    }

    void decrement(Node* node, int val){
        // INFO_MSG("START");
		Node* tmp=node;
		while(tmp->parent != NULL){
			if(tmp->parent->left == tmp){
                tmp->parent->l--;
                tmp->parent->lc -= val;
            }
			if(tmp->parent->right == tmp){
                tmp->parent->r--;
                tmp->parent->rc -= val;
            }
			tmp = tmp->parent;
		}
	}

    void decrementCount(Node* node, int val){
        INFO_MSG("START");
        Node* tmp = node;
        while(tmp->parent != NULL){
            if(tmp->parent->left == tmp)
                tmp->parent->lc -= val;
            if(tmp->parent->right == tmp)
                tmp->parent->rc -= val;
            tmp = tmp->parent;
        }
    }

    void setParentsChild(Node* suc, Node* tmp){
        INFO_MSG("START");
        if(suc->parent){
            if(suc->parent->left == tmp)
                suc->parent->left = suc;
            else if(suc->parent->right == tmp)
                suc->parent->right = suc;
        }
        else this->root = suc;
    }

    void leftRotate(Node* root){
        INFO_MSG("START");
        Node* p = root->parent;
        root->parent = root->right;
        root->right = root->parent->left;
        if(root->right)root->right->parent = root;
        root->r = root->parent->l;
        root->rc = root->parent->lc;
        root->parent->left = root;
        root->parent->l = 1+root->l+root->r;
        root->parent->lc = root->val+root->lc+root->rc;
        root->parent->parent = p;
        if(root == this->root)this->root = root->parent;
        else{
            if(p->left == root)p->left = root->parent;
            if(p->right == root)p->right = root->parent;
        }
    }

    void rightRotate(Node* root){
        INFO_MSG("START");
        Node* p = root->parent;
        root->parent = root->left;
        root->left = root->parent->right;
        if(root->left)root->left->parent = root;
        root->l = root->parent->r;
        root->lc = root->parent->rc;
        root->parent->right = root;
        root->parent->r = 1+root->l+root->r;
        root->parent->rc = root->val+root->lc+root->rc;
        root->parent->parent = p;
        if(root == this->root)this->root = root->parent;
        else{
            if(p->left == root)p->left = root->parent;
            if(p->right == root)p->right = root->parent;
        }
    }

    void fix(Node* root){
        // INFO_MSG("START");
        Node* p = root->parent;
        Node* g = p->parent;
        Node* u;
        if(g->left == p)u = g->right;
        if(g->right == p)u = g->left;
        if(u != NULL && u->isRed){
            u->isRed = false;
            p->isRed = false;
            g->isRed = true;
            if(g == this->root)g->isRed = false;
            else if(g->parent->isRed)fix(g);
        }
        else if(root == p->left && p == g->right){
            rightRotate(p);
            fix(p);
        }
        else if(root == p->right && p == g->left){
            leftRotate(p);
            fix(p);
        }
        else if(root == p->left && p == g->left){
            rightRotate(g);
            g->isRed = true;
            p->isRed = false;
        }
        else if(root == p->right && p == g->right){
            leftRotate(g);
            g->isRed = true;
            p->isRed = false;
        }
    }

    void _insert(Node* root, int key, int val){
        // INFO_MSG("START");
        // print3(root, key, val);
        if(root == NULL)this->root = _getNewNode(key, val, false);
        while(root != NULL){
            if(key == root->key){
                decrement(root, val);
                break;
            }
            else if(key < root->key){
                root->l += 1;
                root->lc += val;
                if(root->left == NULL){
                    root->left = _getNewNode(key, val, true);
                    root->left->parent = root;
                    if(!root->isRed)break;
                    fix(root->left);
                    break;
                }
                else root = root->left;
            }
            else if(key > root->key){
                root->r += 1;
                root->rc += val;
                if(root->right == NULL){
                    root->right = _getNewNode(key, val, true);
                    root->right->parent = root;
                    if(!root->isRed)break;
                    fix(root->right);
                    break;
                }
                else root = root->right;
            }
        }
    }

    void insert(int key, int val){
        // INFO_MSG("START");
        _insert(root, key, val);
    }

    Node* findMin(Node* root){
        // INFO_MSG("START");
        if(root->left == NULL)return root;
        return findMin(root->left);
    }

    void del(Node* root, Node* p){
        // INFO_MSG("START");
        decrement(root, root->val);
        if(root == p->left)p->left = NULL;
        else p->right = NULL;
        freeNode(root);
    }

    void forgetFix(Node* root, int key){
        // INFO_MSG("START");
        // print2(root, key);
        // cout << "In forgetFix\n";
        if(root == this->root){
            // cout << "In forgetFix case 1\n";
            return;//case 1 in tushar roy's video(terminating)
        }
        Node* p = root->parent;
        Node* s;// s for sibling
        if(root == p->left)s = p->right;
        else s = p->left;
        Node* sl = s->left, * sr = s->right;
        // cout << "Hi there\n";
        // case 4 in tushar roy's video(terminating)
        if(p->isRed && !s->isRed && (!sl || !sl->isRed) && (!sr || !sr->isRed)){
            // cout << "In forgetFix case 4\n";
            p->isRed = false;
            s->isRed = true;
            if(key == root->key && !root->left && !root->right)del(root, p);
            return;
        }
        // case 6 in tushar roy's video(terminating)
        if(root == p->left && !s->isRed && sr && sr->isRed){
            // cout << "In forgetFix case 6\n";
            leftRotate(p);
            s->isRed = p->isRed;
            p->isRed = false;
            sr->isRed = false;
            if(key == root->key && !root->left && !root->right)del(root, p);
            return;
        }
        else if(root == p->right && !s->isRed && sl && sl->isRed){
            // cout << "In forgetFix case 6\n";
            rightRotate(p);
            s->isRed = p->isRed;
            p->isRed = false;
            sl->isRed = false;
            if(key == root->key && !root->left && !root->right)del(root, p);
            return;
        }
        // case 3 in tushar roy's video
        if(!p->isRed && !s->isRed &&
           (!sl || !sl->isRed) && (!sr || !sr->isRed)){
            // cout << "In forgetFix case 3\n";
            s->isRed = true;
            if(key == root->key && !root->left && !root->right)del(root, p);
            forgetFix(p, key);
            return;
        }
        // case 5 in tushar roy's video (!p->isRed || p->isRed) = true
        if(root == p->left && true && !s->isRed && 
           (!sr || !sr->isRed) && (sl && sl->isRed)){
            // cout << "In forgetFix case 5\n";
            rightRotate(s);
            s->isRed = true;
            sl->isRed = false;
            forgetFix(root, key);
            return;
        }
        else if(root == p->right && true && !s->isRed && 
           (sr && sr->isRed) && (!sl || !sl->isRed)){
            // cout << "In forgetFix case 5\n";
            leftRotate(s);
            s->isRed = true;
            sr->isRed = false;
            forgetFix(root, key);
            return;
        }
        // case 2 in tushar roy's video
        if(!p->isRed && s->isRed && (!sl || !sl->isRed) && (!sr || !sr->isRed)){
            // cout << "In forgetFix case 2\n";
            if(root == p->left)leftRotate(p);
            else rightRotate(p);
            p->isRed = true;
            s->isRed = false;
            forgetFix(root, key);
            return;
        }
    }

    void _forget(Node* root, int key){
        // INFO_MSG("START");
        while(root != NULL){
            if(key < root->key)root = root->left;
            else if(key > root->key)root = root->right;
            else if(key == root->key){
                // case 0: no child
                if(root->left == NULL && root->right == NULL){
                    if(root->parent == NULL){
                        freeNode(root);
                        this->root = NULL;
                    }
                    else if(root->isRed){
                        decrement(root, root->val);
                        if(root->parent->left == root)root->parent->left = NULL;
                        else root->parent->right = NULL;
                        freeNode(root);
                    }
                    else forgetFix(root, key);
                    break;
                }
                // case 1: one child
                else if(root->right == NULL){
                    decrement(root, root->val);
                    Node* p = root->parent;
                    if(p == NULL){
                        this->root = root->left;
                        root->left->parent = NULL;
                    }
                    else{
                        if(p->left == root)p->left = root->left;
                        else if(p->right == root)p->right = root->left;
                        root->left->parent = p;
                    }
                    root->left->isRed = false;
                    freeNode(root);
                    break;
                }
                else if(root->left == NULL){
                    decrement(root, root->val);
                    Node* p = root->parent;
                    if(p == NULL){
                        this->root = root->right;
                        root->right->parent = NULL;
                    }
                    else{
                        if(p->left == root)p->left = root->right;
                        else if(p->right == root)p->right = root->right;
                        root->right->parent = p;
                    }
                    root->right->isRed = false;
                    freeNode(root);
                    break;
                }
                // case 2: two child
                else{
                    Node* suc = findMin(root->right);
                    Node* tmp = root;
                    if(suc != tmp->right){
                        if(suc->isRed){
                            decrement(suc, suc->val);
                            suc->l = tmp->l;
                            suc->r = tmp->r;
                            suc->lc = tmp->lc;
                            suc->rc = tmp->rc;
                            suc->parent->left = NULL;
                            suc->parent = tmp->parent;
                            suc->left = tmp->left;
                            suc->right = tmp->right;
                            suc->isRed = tmp->isRed;
                            suc->left->parent = suc;
                            setParentsChild(suc, tmp);
                            suc->right->parent = suc;
                            decrementCount(suc, tmp->val-suc->val);
                            freeNode(tmp);
                        }
                        else if(!suc->right){
                            decrementCount(suc, suc->val);
                            suc->l = tmp->l;
                            suc->r = tmp->r;
                            suc->lc = tmp->lc;
                            suc->rc = tmp->rc;
                            Node* ps = suc->parent;
                            suc->parent->left = tmp;
                            suc->parent = tmp->parent;
                            suc->left = tmp->left;
                            suc->right = tmp->right;
                            suc->isRed = tmp->isRed;
                            suc->left->parent = suc;
                            setParentsChild(suc, tmp);
                            suc->right->parent = suc;
                            tmp->parent = ps;
                            tmp->left = NULL;
                            tmp->right = NULL;
                            tmp->isRed = false;
                            tmp->l = 0;
                            tmp->r = 0;
                            tmp->lc = 0;
                            tmp->rc = 0;
                            decrementCount(suc, tmp->val-suc->val);
                            decrementCount(tmp, -tmp->val);
                            forgetFix(tmp, key);
                        }
                        else{
                            decrement(suc, suc->val);
                            Node* ps = suc->parent;
                            Node* sr = suc->right;
                            suc->l = tmp->l;
                            suc->r = tmp->r;
                            suc->lc = tmp->lc;
                            suc->rc = tmp->rc;
                            suc->parent->left = sr;
                            suc->parent = tmp->parent;
                            suc->left = tmp->left;
                            suc->right = tmp->right;
                            suc->isRed = tmp->isRed;
                            suc->left->parent = suc;
                            setParentsChild(suc, tmp);
                            suc->right->parent = suc;
                            sr->parent = ps;
                            sr->isRed = false;
                            decrementCount(suc, tmp->val-suc->val);
                            freeNode(tmp);
                        }
                    }
                    else{
                        if(suc->isRed){
                            suc->l = tmp->l;
                            suc->r = 0;
                            suc->lc = tmp->lc;
                            suc->rc = 0;
                            suc->parent = tmp->parent;
                            suc->left = tmp->left;
                            suc->right = NULL;
                            suc->isRed = tmp->isRed;
                            suc->left->parent = suc;
                            setParentsChild(suc, tmp);
                            decrement(suc, tmp->val);
                            freeNode(tmp);
                        }
                        else if(!suc->right){
                            Node* curr = suc;
                            suc->l = tmp->l;
                            suc->r = tmp->r;
                            suc->lc = tmp->lc;
                            suc->rc = tmp->val;
                            suc->parent = tmp->parent;
                            suc->left = tmp->left;
                            suc->right = tmp;
                            suc->isRed = tmp->isRed;
                            suc->left->parent = suc;
                            setParentsChild(suc, tmp);
                            suc->right->parent = suc;
                            tmp->left = NULL;
                            tmp->right = NULL;
                            tmp->isRed = false;
                            tmp->l = 0;
                            tmp->r = 0;
                            tmp->lc = 0;
                            tmp->rc = 0;
                            forgetFix(tmp, key);
                        }
                        else{
                            decrement(suc, suc->val);
                            Node* sr = suc->right;
                            suc->l = tmp->l;
                            suc->r = tmp->r;
                            suc->lc = tmp->lc;
                            suc->parent = tmp->parent;
                            suc->left = tmp->left;
                            suc->isRed = tmp->isRed;
                            suc->left->parent = suc;
                            setParentsChild(suc, tmp);
                            sr->isRed = false;
                            decrementCount(suc, tmp->val-suc->val);
                            freeNode(tmp);
                        }
                    }
                }
            }
        }
    }

    void forget(int key){
        // INFO_MSG("START");
        _forget(root, key);
    }

    void modify(int key, int diff){
        INFO_MSG("START");
        Node* tmp = root;
        while(tmp != NULL){
            if(key < tmp->key)tmp = tmp->left;
            else if(key > tmp->key)tmp = tmp->right;
            else if(key == tmp->key){
                tmp->val += diff;
                decrementCount(tmp, -diff);
                break;
            }
        }
    }

    Node* _priority(Node* root, int x){
        INFO_MSG("START");
        if(root == NULL)return root;
        else if(root->lc >= x)return _priority(root->left, x);
        else if(root->lc+root->val >= x)return root;
        else return _priority(root->right, x-(root->lc+root->val));
    }

    void priority(int x){
        INFO_MSG("START");
        Node* node = _priority(root, x);
        if(node)cout << green << "Priority " << x << ": key = " << node->key 
                     << ", val = " << node->val << nocolor << endl;
        else cout << red << "Priority " << x << ": None" << nocolor << endl;
    }

    int _rank(Node* root, int x){
        // INFO_MSG("START");
        if(root == NULL)return -1;
        if(x < root->key)return _rank(root->left, x);
        if(x == root->key)return root->l+1;
        if(x > root->key){
            int R = _rank(root->right, x);
            if(R != -1)return root->l+1+R;
            return R;
        }
        return -1;
    }

    void rank(int x){
        INFO_MSG("START");
        cout << green << "Rank of " << x << ": " << _rank(root, x) << nocolor
             << endl;
    }

    Node* _find(Node* root,int x){
        INFO_MSG("START");
        if(root == NULL)return root;
        if(root->key == x)return root;
        if(x < root->key)return _find(root->left, x);
        if(x > root->key)return _find(root->right, x);
        return root;
    }

    void find(int x){
        INFO_MSG("START");
        Node* node = _find(root, x);
        if(node != NULL)cout << green << "Found, val: " << node->val \
            << nocolor << "\n";
        else cout << red << "Not found" << nocolor << "\n";
    }

    int _height(Node* root){
        // INFO_MSG("START");
		if(root == NULL)return 0;
		return 1+max(_height(root->left), _height(root->right));
	}

	int height(){
        // INFO_MSG("START");
		return _height(root);
	}

    void _printCurrentLevel(Node* root, int d){
		if(root == NULL)return;
		if(d == 1){
            string color = root->isRed ? red : black;
            cout << color << root->key << "  " << nocolor;
        }
		if(d > 1){
			_printCurrentLevel(root->left, d-1);
			_printCurrentLevel(root->right, d-1);
		}
	}

	void printCurrentLevel(int d){
		_printCurrentLevel(root, d);
	}

	void printLevelOrderTraversal(){
		cout << "Printing Levelorder Traversal : \n";
		for (int d = 1; d <= height(); d++){
			printCurrentLevel(d);
			cout << endl;
		}
	}

    bool _isValidRBTree(Node* root, int& blackCount){
        if(root == NULL){
            blackCount = 0;
            return true;
        }
        if(root->isRed && !root->parent)return false;
        if(root->isRed){
            if((root->left && root->left->isRed) || 
                (root->right && root->right->isRed)){
                    cout << "Error:\n";
                    print1(root->key);
                    return false;
            }
        }
        int leftBlackCount = 0, rightBlackCount = 0;
        bool isLeftValid = _isValidRBTree(root->left, leftBlackCount);
        bool isRightValid = _isValidRBTree(root->right, rightBlackCount);
        if(leftBlackCount != rightBlackCount){
            cout << "Error:\n";
            print3(root->key, leftBlackCount, rightBlackCount);
            return false;
        }
        blackCount = leftBlackCount+(root->isRed ? 0 : 1);
        return isLeftValid and isRightValid;
    }

    void isValidRBTree(){
        int blackCount = 0;
        if(!_isValidRBTree(root, blackCount)){
            cout << "Error:\n";
            print2(root, blackCount);
            exit(1);
        }
    }

    bool _checkValidity(Node* root){
        if(root == NULL)return true;
        if(root->left){
            if(root->lc != root->left->lc+root->left->val+root->left->rc){
                cout << "Error:\n";
                print4(root->lc, root->left->val, \
                    root->left->lc, root->left->rc);
                return false;
            }
            if(root->l != root->left->l+1+root->left->r){
                cout << "Error:\n";
                print3(root->l, root->left->l, root->left->r);
                return false;
            }
            if(root->left->parent != root){
                cout << "Error:\n";
                print2(root->key, root->left->key);
                return false;
            }
            if(root->left->key >= root->key){
                cout << "Error:\n";
                print2(root->key, root->left->key);
                return false;
            }
        }
        else if(root->l || root->lc){
            cout << "Error:\n";
            print2(root->l, root->lc);
            return false;
        }
        if(root->right){
            if(root->rc != root->right->lc+root->right->val+root->right->rc){
                cout << "Error:\n";
                print4(root->rc, root->right->val, \
                    root->right->lc, root->right->rc);
                return false;
            }
            if(root->r != root->right->l+1+root->right->r){
                cout << "Error:\n";
                print3(root->r, root->right->l, root->right->r);
                return false;
            }
            if(root->right->parent != root){
                cout << "Error:\n";
                print2(root->key, root->right->key);
                return false;
            }
            if(root->right->key <= root->key){
                cout << "Error:\n";
                print2(root->key, root->right->key);
                return false;
            }
        }
        else if(root->r || root->rc){
            cout << "Error:\n";
            print2(root->r, root->rc);
            return false;
        }
        return _checkValidity(root->left) and _checkValidity(root->right);
    }

    void checkValidity(){
        if(!_checkValidity(root)){
            cout << "Error:\n";
            print1(root);
            exit(1);
        }
        if(root && numNodes != root->l+1+root->r){
            cout << "Error:\n";
            print3(numNodes, root->l, root->r);
            exit(1);
        }
        if(root == NULL && numNodes != 0){
            cout << "Error:\n";
            print1(numNodes);
            exit(1);
        }
    }

    void _printSorted(Node* root){
        if(root == NULL)return;
        _printSorted(root->left);
        string color = root->isRed ? red : black;
        cout << color << root->key << "(" << root->val << ") " << nocolor;
        _printSorted(root->right);
    }

    void printSorted(){
        cout << "Sorted bst is: ";
        _printSorted(root);
        cout << endl;
    }

    void _printTree(Node* root){
        if(root == NULL)return;
        string color = root->isRed ? red : black;
        cout << color << root->key << "(" << ((root->isRed)? "r" : "b") << ")" \
            << "\t" << nocolor;
        if(root->left != NULL){
            color = root->left->isRed ? red : black;
            cout << color << root->left->key << "\t" << nocolor;
        }
        else cout << black << "Not\t" << nocolor;
        if(root->right != NULL){
            color = root->right->isRed ? red : black;
            cout << color << root->right->key << "\t" << nocolor;
        }
        else cout << black << "Not\t" << nocolor;
        if(root->parent){
            color = root->parent->isRed ? red : black;
            cout << color << root->parent->key << "\t" << nocolor;
        }
        else cout << black << "Not\t" << nocolor;
        cout << "(" << root->l << "," << root->r << ")\t";
        cout << root->val << "\t";
        cout << "(" << root->lc << "," << root->rc << ")\t";
        cout << endl;
        _printTree(root->left);
        _printTree(root->right);
    }

    void printTree(){
        cout << yellow << "BST is:" << nocolor << "\n";
        print1(numNodes);
        cout << "Height or Depth: " << height() << endl;
        cout << "node\tleft\tright\tparent\t(l,r)\tval\t(lc,rc)\n";
        _printTree(root);
        printLevelOrderTraversal();
        printSorted();
    }
};

int main(){
    initializePool();
    RedBlackTree t1;
    // t1.insert(-20,-20);
    // t1.insert(-10,-10);
    // t1.insert(0,0);
    // t1.insert(10,10);
    // t1.insert(20,20);
    // t1.insert(30,30);
    // t1.insert(40,40);
    // t1.insert(50,50);
    // t1.insert(60,60);
    // t1.insert(70,70);
    // t1.insert(80,80);
    // t1.insert(90,90);
    // t1.insert(100,100);
    // t1.printTree();
    string str;
    int x, y, count = 0;
    timer1.start();
    while(true){
        cout << yellow << "Possible commands:\n"
             << "find x, add x y, del x, rank x, modify x diff, priority x"
             << ", stop 1\n" << nocolor;
        cin >> str;
        cin >> x;
        print2(str, x);
        if(str == "find")t1.find(x);
        if(str == "add"){ cin >> y; print1(y); t1.insert(x, y); }
        if(str == "del")t1.forget(x);
        if(str == "rank")t1.rank(x);
        if(str == "modify"){ cin >> y; print1(y); t1.modify(x, y); }
        if(str == "priority")t1.priority(x);
        if(str == "stop")break;
        t1.printTree();
        t1.checkValidity();
        t1.isValidRBTree();
        print1(count++);
    }
    long long int time_taken = timer1.get_elapsed_ns();
    print1(time_taken);
}