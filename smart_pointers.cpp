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

int main(){
    //raw pointers
    Node* ptr = new Node;
    std::cout << "*ptr: " << *ptr << std::endl;
    delete ptr;

    Node node(6);
    node.~Node();
    //smart pointer: unique ptr
    std::unique_ptr<Node> uptr(new Node(5));
    std::cout << "*uptr: " << *uptr << std::endl;
    
    //smart pointer: shared ptr
    std::shared_ptr<Node> sptr(new Node(5));
    std::cout << "*sptr: " << *sptr << std::endl;
    std::cout << __LINE__ << ": smart_ptr.use_count: " << sptr.use_count() \
              << std::endl;
    return 0;
}