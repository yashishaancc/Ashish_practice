#include<iostream>
using namespace std;

typedef struct node{
    int val, l, r;
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

Node* getNewNode(int val, bool isRed){
    Node* node = allocMem();
    node->val = val;
    node->l = 0;
    node->r = 0;
    node->isRed = isRed;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

class RedBlackTree{
    Node* root;
public:
    RedBlackTree(){
        root = NULL;
    }

    void decrement(Node* node){
		Node* tmp=node;
		while(tmp->parent != NULL){
			if(tmp->parent->left == tmp)tmp->parent->l--;
			if(tmp->parent->right == tmp)tmp->parent->r--;
			tmp = tmp->parent;
		}
	}

    void leftRotate(Node* root){
        Node* p = root->parent;
        root->parent = root->right;
        root->right = root->parent->left;
        root->r = root->parent->l;
        root->parent->left = root;
        root->parent->l = 1+root->l+root->r;
        root->parent->parent = p;
        if(root == this->root)this->root = root->parent;
        else{
            if(p->left == root)p->left = root->parent;
            if(p->right == root)p->right = root->parent;
        }
    }

    void rightRotate(Node* root){
        Node* p = root->parent;
        root->parent = root->left;
        root->left = root->parent->right;
        root->l = root->parent->r;
        root->parent->right = root;
        root->parent->r = 1+root->l+root->r;
        root->parent->parent = p;
        if(root == this->root)this->root = root->parent;
        else{
            if(p->left == root)p->left = root->parent;
            if(p->right == root)p->right = root->parent;
        }
    }

    void fix(Node* root){
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

    void _insert(Node* root, int val){
        if(root == NULL)this->root = getNewNode(val, false);
        while(root != NULL){    
            if(val == root->val){
                decrement(root);
                break;
            }
            else if(val < root->val){
                root->l += 1;
                if(root->left == NULL){
                    root->left = getNewNode(val, true);
                    root->left->parent = root;
                    if(!root->isRed)break;
                    fix(root->left);
                    break;
                }
                else root = root->left;
            }
            else if(val > root->val){
                root->r += 1;
                if(root->right == NULL){
                    root->right = getNewNode(val, true);
                    root->right->parent = root;
                    if(!root->isRed)break;
                    fix(root->right);
                    break;
                }
                else root = root->right;
            }
        }
    }

    void insert(int val){
        _insert(root, val);
    }

    Node* findMin(Node* root){
        if(root->left == NULL)return root;
        return findMin(root->left);
    }

    void del(Node* root, Node* p){
        decrement(root);
        if(root == p->left)p->left = NULL;
        else p->right = NULL;
        freeMem(root);
    }

    void forgetFix(Node* root, int val){
        cout << "In forgetFix\n";
        if(root == this->root){
            return;//case 1 in tushar roy's video(terminating)
            cout << "In forgetFix case 1\n";
        }
        Node* p = root->parent;
        Node* s;// s for sibling
        if(root == p->left)s = p->right;
        else s = p->left;
        Node* sl = s->left, * sr = s->right;
        // case 4 in tushar roy's video(terminating)
        if(p->isRed && !s->isRed && (!sl || !sl->isRed) && (!sr || !sr->isRed)){
            cout << "In forgetFix case 4\n";
            p->isRed = false;
            s->isRed = true;
            if(val == root->val && !root->left && !root->right)del(root, p);
            return;
        }
        // case 6 in tushar roy's video(terminating)
        if(root == p->left && !s->isRed && sr->isRed){
            cout << "In forgetFix case 6\n";
            leftRotate(p);
            s->isRed = p->isRed;
            p->isRed = false;
            sr->isRed = false;
            if(val == root->val && !root->left && !root->right)del(root, p);
            return;
        }
        else if(root == p->right && !s->isRed && sl->isRed){
            cout << "In forgetFix case 6\n";
            rightRotate(p);
            s->isRed = p->isRed;
            p->isRed = false;
            sl->isRed = false;
            if(val == root->val && !root->left && !root->right)del(root, p);
            return;
        }
        // case 3 in tushar roy's video
        if(!p->isRed && !s->isRed &&
           (!sl || !sl->isRed) && (!sr || !sr->isRed)){
            cout << "In forgetFix case 3\n";
            s->isRed = true;
            if(val == root->val && !root->left && !root->right)del(root, p);
            forgetFix(p, val);
            return;
        }
        // case 5 in tushar roy's video
        if(root == p->left && !p->isRed && !s->isRed && 
           (!sr || !sr->isRed) && (sl && sl->isRed)){
            cout << "In forgetFix case 5\n";
            rightRotate(s);
            s->isRed = true;
            sl->isRed = false;
            forgetFix(root, val);
            return;
        }
        else if(root == p->right && !p->isRed && !s->isRed && 
           (sr && sr->isRed) && (!sl || !sl->isRed)){
            cout << "In forgetFix case 5\n";
            leftRotate(s);
            s->isRed = true;
            sr->isRed = false;
            forgetFix(root, val);
            return;
        }
        // case 2 in tushar roy's video
        if(!p->isRed && s->isRed && (!sl || !sl->isRed) && (!sr || !sr->isRed)){
            cout << "In forgetFix case 2\n";
            if(root == p->left)leftRotate(p);
            else rightRotate(p);
            p->isRed = true;
            s->isRed = false;
            forgetFix(root, val);
            return;
        }
    }

    // this function was written by chatGPT and it produce errors
    // void forgetFix(Node* node,int val) {
    //     while (node != root && !node->isRed) {
    //         if (node == node->parent->left) {
    //             Node* sibling = node->parent->right;
    //             if (sibling && sibling->isRed) {
    //                 // Case 1: Sibling is red
    //                 sibling->isRed = false;
    //                 node->parent->isRed = true;
    //                 leftRotate(node->parent);
    //                 sibling = node->parent->right;
    //             }
    //             if ((!sibling->left || !sibling->left->isRed) && (!sibling->right || !sibling->right->isRed)) {
    //                 // Case 2: Sibling and its children are black
    //                 sibling->isRed = true;
    //                 node = node->parent;
    //             } else {
    //                 if (!sibling->right || !sibling->right->isRed) {
    //                     // Case 3: Sibling's right child is black
    //                     sibling->left->isRed = false;
    //                     sibling->isRed = true;
    //                     rightRotate(sibling);
    //                     sibling = node->parent->right;
    //                 }
    //                 // Case 4: Sibling's right child is red
    //                 sibling->isRed = node->parent->isRed;
    //                 node->parent->isRed = false;
    //                 sibling->right->isRed = false;
    //                 leftRotate(node->parent);
    //                 node = root;  // Exit the loop
    //             }
    //         } else {
    //             Node* sibling = node->parent->left;
    //             if (sibling && sibling->isRed) {
    //                 // Case 1: Sibling is red
    //                 sibling->isRed = false;
    //                 node->parent->isRed = true;
    //                 rightRotate(node->parent);
    //                 sibling = node->parent->left;
    //             }
    //             if ((!sibling->left || !sibling->left->isRed) && (!sibling->right || !sibling->right->isRed)) {
    //                 // Case 2: Sibling and its children are black
    //                 sibling->isRed = true;
    //                 node = node->parent;
    //             } else {
    //                 if (!sibling->left || !sibling->left->isRed) {
    //                     // Case 3: Sibling's left child is black
    //                     sibling->right->isRed = false;
    //                     sibling->isRed = true;
    //                     leftRotate(sibling);
    //                     sibling = node->parent->left;
    //                 }
    //                 // Case 4: Sibling's left child is red
    //                 sibling->isRed = node->parent->isRed;
    //                 node->parent->isRed = false;
    //                 sibling->left->isRed = false;
    //                 rightRotate(node->parent);
    //                 node = root;  // Exit the loop
    //             }
    //         }
    //     }
    //     if (node) {
    //         node->isRed = false;
    //     }
    // }

    void _forget(Node* root, int val){
        while(root != NULL){
            if(val < root->val)root = root->left;
            else if(val > root->val)root = root->right;
            else if(val == root->val){
                // case 0: no child
                if(root->left == NULL && root->right == NULL){
                    if(root->parent == NULL){
                        freeMem(root);
                        this->root = NULL;
                    }
                    else if(root->isRed){
                        decrement(root);
                        if(root->parent->left == root)root->parent->left = NULL;
                        else root->parent->right = NULL;
                        freeMem(root);
                    }
                    else forgetFix(root, val);
                    break;
                }
                // case 1: one child
                else if(root->right == NULL){
                    decrement(root->left);
                    root->val = root->left->val;
                    freeMem(root->left);
                    root->left = NULL;
                    break;
                    // if(root->parent->left == root)
                    //     root->parent->left = root->left;
                    // else if(root->parent->right == root)
                    //     root->parent->right = root->left;
                    // root->left->parent = root->parent;
                    // freeMem(root);
                }
                else if(root->left == NULL){
                    decrement(root->right);
                    root->val = root->right->val;
                    freeMem(root->right);
                    root->right = NULL;
                    break;
                    // if(root->parent->left == root)
                    //     root->parent->left = root->right;
                    // else if(root->parent->right == root)
                    //     root->parent->right = root->right;
                    // root->right->parent = root->parent;
                    // freeMem(root);
                }
                // case 2: two child
                else{
                    Node* suc = findMin(root->right);
                    decrement(suc);
                    root->val = suc->val;
                    root = root->right;
                    val = suc->val;
                }
            }
        }
    }

    void forget(int val){
        _forget(root, val);
    }

    int _rank(Node* root, int x){
        if(root == NULL)return -1;
        if(x < root->val)return _rank(root->left, x);
        if(x == root->val)return root->l+1;
        if(x > root->val){
            int R = _rank(root->right, x);
            if(R != -1)return root->l+1+R;
            return R;
        }
        return -1;
    }

    void rank(int x){
        cout << "Rank of " << x << ": " << _rank(root, x) << endl;
    }

    Node* _find(Node* root,int x){
        if(root == NULL)return root;
        if(root->val == x)return root;
        if(x < root->val)return _find(root->left, x);
        if(x > root->val)return _find(root->right, x);
        return root;
    }

    void find(int x){
        Node* node = _find(root, x);
        if(node != NULL)cout << "\x1b[32mFound\x1b[0m\n";
        else cout << "\x1b[31mNot found\x1b[0m\n";
    }

    int _height(Node* root){
		if(root == NULL)return 0;
		return 1+max(_height(root->left), _height(root->right));
	}

	int height(){
		return _height(root);
	}

    void _printCurrentLevel(Node* root, int d){
		if(root == NULL)return;
		if(d == 1){
            int color = root->isRed ? 31 : 30;
            cout << "\x1b[" << color << "m" << root->val << "  \x1b[0m";
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

    void _printSorted(Node* root){
        if(root == NULL)return;
        _printSorted(root->left);
        int color = root->isRed ? 31 : 30;
        cout << "\x1b[" << color << "m" << root->val << " \x1b[0m";
        _printSorted(root->right);
    }

    void printSorted(){
        cout << "Sorted bst is: ";
        _printSorted(root);
        cout << endl;
    }

    void _printTree(Node* root){
        if(root == NULL)return;
        int color = root->isRed ? 31 : 30;
        cout << "\x1b[" << color << "m" << root->val << "    \x1b[0m";
        if(root->left != NULL){
            color = root->left->isRed ? 31 : 30;
            cout << "\x1b[" << color << "m" << root->left->val << "    \x1b[0m";
        }
        else cout << "\x1b[30mNot   \x1b[0m";
        if(root->right != NULL){
            color = root->right->isRed ? 31 : 30;
            cout << "\x1b[" << color << "m" << root->right->val 
                 << "    \x1b[0m";
        }
        else cout << "\x1b[30mNot   \x1b[0m";
        cout << "(" << root->l << "," << root->r << ")";
        cout << endl;
        _printTree(root->left);
        _printTree(root->right);
    }

    void printTree(){
        cout << "\x1b[33mBST is: \x1b[0m\n";
        _printTree(root);
        printLevelOrderTraversal();
        printSorted();
    }
};

int main(){
    initializePool();
    RedBlackTree t1;
    // t1.insert(-20);
    // t1.insert(-10);
    // t1.insert(0);
    // t1.insert(10);
    // t1.insert(20);
    // t1.insert(30);
    // t1.insert(40);
    // t1.insert(50);
    // t1.insert(60);
    // t1.insert(70);
    // t1.insert(80);
    // t1.insert(90);
    // t1.insert(100);
    t1.printTree();
    string str;
    int x;
    while(true){
        cout << "\x1b[33mPossible commands:\n"
             << "find x, add x, del x, rank x\x1b[0m\n";
        cin >> str;
        cin >> x;
        if(str == "find")t1.find(x);
        if(str == "add")t1.insert(x);
        if(str == "del")t1.forget(x);
        if(str == "rank")t1.rank(x);
        t1.printTree();
    } 
}