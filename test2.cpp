#include<iostream>
using namespace std;
typedef struct node{
    int data;
    node* next;
}Node;
int main(){
    node* node = NULL;
    Node* NODE = (Node*)malloc(sizeof(Node));
    if(node)cout << "node\n";
    if(!node)cout << "!node\n";
    if(NODE)cout << "NODE\n";
    if(!NODE)cout << "!NODE\n";
    cout << "1234567812345678123456781234567812345678\n";
    cout << "a\tbc\tdef--ghi\tjkl\n";
    // if()cout << "Empty\n";
    if(0 == 0)exit(1);
    else cout << "else\n";
    cout << "Please print me\n";
}