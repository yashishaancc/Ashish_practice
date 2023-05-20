#include<iostream>
using namespace std;

#define NUMCHARS 62

typedef struct node{
    int val;
    bool isVal;
    node* parent;
    int parIdx;
    node* arr[62];
}Node;

#define POOLSIZE 1024
// Node pool[POOLSIZE];
Node* pool = (Node*)malloc(POOLSIZE*sizeof(Node));
// int poolIdx = 0;
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
    // cout << "node: " << node << " sizeof(node): " << sizeof(Node) << endl;
    return node;
}

void freeMem(Node* node){
    Node** tmp = (Node**)node;
    *tmp = freeList;
    freeList = node;
    return;
}

Node* getNewNode(int val, bool isVal){
    // Node* node = (Node*)malloc(sizeof(Node));
    // Node* node = &pool[poolIdx++];
    Node* node = allocMem();
    node->val = val;
    node->isVal = isVal;
    for(int i = 0; i < 62; i++)node->arr[i] = NULL;
    node->parent = NULL;
    return node;
}

char intToChar(int i){
    char c;
    if(i < 26)c = 'a'+i;
    else if(i < 52)c = 'A'+i-26;
    else c = '0'+i-52;
    return c;
}

int charToInt(char c){
    int i;
    if(c >= 'a' && c <= 'z')i = c-'a';
    else if(c >= 'A' && c <= 'Z')i = c-'A'+26;
    else i = c-'0'+52;
    return i;
}

class Trie{
    Node* head;
public:
    Trie(){
        head = getNewNode(-1,false);
    }

    void insert(string str, int val){
        int l = str.length();
        Node* prev = head;
        for(int i = 0; i < l; i++){
            if(prev->arr[charToInt(str[i])] == NULL){
                Node* node = getNewNode(-1,false);
                prev->arr[charToInt(str[i])] = node;
                node->parent = prev;
                node->parIdx = charToInt(str[i]);
                prev = node;
                if(i == l-1){
                    node->val = val;
                    node->isVal = true;
                }
            }
            else{
                Node* node = prev->arr[charToInt(str[i])];
                prev = node;
                if(i == l-1){
                    node->val = val;
                    node->isVal = true;
                }
            }
        }
    }

    Node* _find(string str){
        int l = str.length();
        Node* prev = head;
        for(int i = 0; i < l; i++){
            if(i != l-1){
                if(prev->arr[charToInt(str[i])] != NULL)
                    prev = prev->arr[charToInt(str[i])];
                else return NULL;
            }
            else{
                if(prev->arr[charToInt(str[i])] != NULL){
                    prev = prev->arr[charToInt(str[i])];
                    // return prev->val;
                    return prev;
                }
                else return NULL;
            }
        }
        return NULL;
    }

    int find(string str){
        Node* node = _find(str);
        if(node == NULL)return -1;
        else return node->val;
    }

    void forget(string str){
        int l = str.length();
        Node* prev = head;
        for(int i = 0; i < l; i++){
            if(i != l-1){
                if(prev->arr[charToInt(str[i])] != NULL)
                    prev = prev->arr[charToInt(str[i])];
                else return;
            }
            else{
                if(prev->arr[charToInt(str[i])] != NULL){
                    prev = prev->arr[charToInt(str[i])];
                    prev->isVal = false;
                    while(prev->parent != NULL){
                        // cout << "prev->val: "<< prev->val << endl;
                        Node* parent = prev->parent;
                        if(!(prev->isVal)){
                            prev->isVal = false;
                            prev->val = -1;
                            bool isNotAllNull = false;
                            for(int j = 0; j < 62; j++){
                                if(prev->arr[j] != NULL){
                                    isNotAllNull = true;
                                    break;
                                }
                            }
                            if(!isNotAllNull){
                                prev->parent->arr[prev->parIdx] = NULL;
                                freeMem(prev);
                                prev = parent;
                            }
                            else break;
                        }
                        else return;
                    }
                }
                else return;
            }
        }
    }

    void _reset(Node* node){
        int c = 0;
        for(int i = 0; i < 62; i++){
            if(node->arr[i] == NULL)
                c++;
        }
        if(c = 62)
            free(node);
        for(int i = 0; i < 62; i++){
            if(node->arr[i] != NULL)
                _reset(node->arr[i]);
        }
    }

    void reset(){
        _reset(head);
    }

    void _print(Node* node, string str=""){
        if(node->isVal)cout << str << " \t" << node->val << endl;
        // cout << "Hello\n";
        for(int i = 0; i < 62; i++){
            if(node->arr[i] != NULL){
                char c = intToChar(i);
                // cout << "Hi c: " << c << endl;
                _print(node->arr[i], str+c);
            }
        }
    }

    void _printByLevels(Node* node, string str=""){
        if(node->isVal)cout << str << " \t" << node->val << endl;
        for(int i = 0; i < 62; i++){
            if(node->arr[i] != NULL){
                char c = intToChar(i);
                std::cout << str << c << std::endl;
                _printByLevels(node->arr[i], str+"\t");
            }
        }
    }

    void print(){
        cout << "\x1b[32m";
        _print(head, "");
        // cout << "Between prints" << endl;
        _printByLevels(head, "");
        cout << "\x1b[0m";
    }
};

int main(){
    initializePool();
    Trie g1;
    string comm, str;
    int val;
    cout << "\x1b[33mpossible commands are "
         << "in <string> <val>, find <string>, del <string>\x1b[0m" 
         << endl;
    while(true){
        cin >> comm;
        if(comm == "in"){
            cin >> str;
            cin >> val;
            g1.insert(str, val);
        }
        if(comm == "find"){
            cin >> str;
            int v = g1.find(str);
            if(v == -1)cout << "Not found" << endl;
            else cout << "Value of " << str << ":\t" << v << endl;
        }
        if(comm == "del"){
            cin >> str;
            g1.forget(str);
        }
        if(comm == "reset"){
            // g1.reset();
        }
        g1.print();
    }
    return 0;
}
