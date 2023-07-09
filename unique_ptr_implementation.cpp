#include<iostream>

struct Node; 

struct Node{
    int key;
    
    Node(){
        std::cout << "[Node] No argument(default) constructor called\n";
        key = 0;
    }

    explicit Node(int key): key(key){
        std::cout << "[Node] One argument constructor called\n";
    }

    Node(const Node& other){
        key = other.key;
    }

    ~Node(){
        std::cout << "[Node] Destructor called, key: " << key << "\n";
        key = -1;
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& c){
        os << "val: " << c.key;
        return os;
    }
};

