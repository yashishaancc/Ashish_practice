#include <iostream>
#include <memory>

struct Node{
    int key;
    
    Node(){
        std::cout << "No argument(default) constructor called\n";
        key = 0;
    }

    Node(int key): key(key){
        std::cout << "One argument constructor called\n";
    }

    Node(const Node& other){
        std::cout << "Copy constructor called\n";
        key = other.key;
    }

    void operator=(const Node& other){
        std::cout << "Assignment operator called\n";
        key = other.key;
    }

    ~Node(){
        std::cout << "Destructor called, key: " << key << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& c){
        // std::cout << "operator << called" << std::endl;
        // os << "real: " << c.real << ", imag: " << c.imag;
        os << c.key;
        return os;
    }
};

Node fun(){
    // Node* node = new Node;
    std::cout << "Fun() called\n";
    Node n1(5);
    return n1;
}

int main(){
    Node n1(6);
    n1 = fun();
    return 0;
}