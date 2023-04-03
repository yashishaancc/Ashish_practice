#include<iostream>
#include<string>
using namespace std;
typedef struct node{
    int val;
    int l, r;
    node* left;
    node* right;
    node* parent;
}Node;
Node* getNewNode(int in){
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = in;
    node->l = 0;
    node->r = 0;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}
class BST{
    Node* root;
public:
    BST(){
        root = NULL;
    }
    ~BST(){

    }
    void decrement(Node* node){
		Node* tmp=node;
		while(tmp->parent != NULL){
			if(tmp->parent->left == tmp){
				tmp->parent->l--;
			}
			if(tmp->parent->right == tmp){
				tmp->parent->r--;
			}
			tmp = tmp->parent;
		}
	}
    Node* _insert(Node* root, int key){
        if(root == NULL){
            Node* node = getNewNode(key);
            root = node;
            return root;
        }
        if(key == root->val){
            decrement(root);
            return root;
        }
        if(key < root->val){
            root->left = _insert(root->left, key);
            root->left->parent = root;
            root->l += 1;
        }
        else if(key > root->val){
            root->right = _insert(root->right, key);
            root->right->parent = root;
            root->r += 1;
        }
        return root;
    }
    void insert(int key){
        root = _insert(root, key);
    }
    Node* _findval(Node* root, int key){
		if(root == NULL) return NULL;
		if(root->val == key) return root;
		if(key <= root->val) return _findval(root->left, key);
		if(key >= root->val) return _findval(root->right, key);
		return NULL;
	}
	bool findval(int key){
		Node* node = _findval(root, key);
		if(node == NULL)return false;
		else return true;
	}
    int count(Node* root){
        if(root == NULL)return 0;
        return count(root->left)+1+count(root->right);
    }
    int _findRank(Node* root, int key){
        if(root == NULL)return -1;
        if(key < root->val)return _findRank(root->left, key);
        if(key == root->val)return root->l+1;//count(root->left)+1;
        if(key > root->val){
            int R = _findRank(root->right, key);
            if(R != -1)return root->l+1+R;//count(root->left)+1+R;
            return R;
        }
        return -1;
    }
    int findRank(int key){
        return _findRank(root, key);
    }
    Node* findMin(Node* root){
        if(root->left == NULL)return root;
        return findMin(root->left);
    }
    void _forget(Node* root, int key){
        Node* node = _findval(root, key);
        if(node == NULL)return;
        // case 1: no child
        if(node->left == NULL && node->right == NULL){
            if(node->parent != nullptr){
                if(node->parent->left == node)node->parent->left = nullptr;
                else if(node->parent->right == node)node->parent->right = NULL;
            }
            decrement(node);
            if(node == this->root)this->root = NULL;
            free(node);
        }
        // case 2: one child
        else if(node->right == NULL){
            decrement(node);
            if(node->parent != NULL){
                if(node->parent->left == node){
                    node->parent->left = node->left;
                }
                else if(node->parent->right == node){
                    node->parent->right = node->left;
                }
                node->left->parent = node->parent;
                free(node);
            }
            else{
                this->root = node->left;
                this->root->parent = NULL;
                free(node);
            }
        }
        else if(node->left == NULL){
            decrement(node);
            if(node->parent != NULL){
                if(node->parent->left == node){
                    node->parent->left = node->right;
                }
                else if(node->parent->right == node){
                    node->parent->right = node->right;
                }
                node->right->parent = node->parent;
                free(node);
            }
            else{
                this->root = node->right;
                this->root->parent = NULL;
                free(node);
            }
        }
        // case 3: two child
        else{
            Node* suc = findMin(node->right);
            decrement(suc);
            node->val = suc->val;
            if(suc->parent->left == suc)suc->parent->left = suc->right;
            else{
                suc->parent->right = suc->right;
            }
            if(suc->right != NULL)suc->right->parent = suc->parent;
            free(suc);
        }
    }
    void forget(int key){
        _forget(root, key);
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
		if(d == 1)cout << root->val << "  ";
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
        cout << root->val << " ";
        _printSorted(root->right);
    }
    void printSorted(){
        cout << "Sorted bst is: ";
        _printSorted(root);
        cout << endl;
    }
    void _printTree(Node* root){
        if(root == NULL)return;
        cout << root->val << "    ";
        if(root->left != NULL)cout << root->left->val << "    ";
        else cout << "\x1b[31mNot   \x1b[0m";
        if(root->right != NULL)cout << root->right->val << "    ";
        else cout << "\x1b[31mNot   \x1b[0m";
        cout << "(" << root->l << "," << root->r << ")";
        cout << endl;
        _printTree(root->left);
        _printTree(root->right);
    }
    void printTree(){
        cout << "BST is: \n";
        _printTree(root);
        printLevelOrderTraversal();
        printSorted();
    }
};
int main(){
	int i, n, q;
	cout << "Enter size and number of queries: ";
	cin >> n >> q;
	BST b1;
	cout << "Enter numbers: ";
	for(i = 0; i < n; i++){
		int in;
		cin >> in;
		b1.insert(in);
	}
	b1.printTree();
	for(i = 0; i < q; i++){
		int x;
		string str;
		cout << "\x1b[33mPossible commands are: find x, add x, "
			 << "del x, rank x\x1b[0m\n";
		cin >> str;
		if(str == "find"){
			cin >> x;
			cout << boolalpha << b1.findval(x) << endl;
		}
		if(str == "add"){
			cin >> x;
			b1.insert(x);
			b1.printTree();
		}
		if(str == "del"){
			cin >> x;
			b1.forget(x);
			b1.printTree();
		}
		if(str == "rank"){
			cin >> x;
			int rank = b1.findRank(x);
			cout << "Rank of " << x << " : " << rank << endl;
		}
	}
	b1.printTree();
	return 0;
}
// 9 100     30 50 20 60 40 10 80 70 90
/*              30
			   /  \
			  20  50
			 /   /  \
			10  40  60 
					  \
					  80 
					 /  \
					70  90
*/