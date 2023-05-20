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
}