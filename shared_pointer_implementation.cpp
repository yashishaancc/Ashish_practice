#include<iostream>

class Shared_ptr;
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

class Shared_ptr{
    // This is implementation of shared_ptr
    Node* ptr;
    int* count = NULL;
    friend void fun(Shared_ptr& s);
public:
    Shared_ptr(){
        std::cout << "[Shared_ptr] Default constructor called\n";
        ptr = NULL;
        count++;
    }

    Shared_ptr(Node* ptr): ptr(ptr){
        std::cout << "[Shared_ptr] One argument constructor called\n";
        count = new int(1);
    }

    Shared_ptr(const Shared_ptr& other){
        std::cout << "[Shared_ptr] copy constructor called\n";
        ptr = other.ptr;
        count = other.count;
        (*count)++;
    }

    ~Shared_ptr(){
        std::cout << "[Shared_ptr] Destructor called\n";
        (*count)--;
        if(*count == 0){
            if(ptr)(*ptr).~Node();
            delete count;
        }
    }

    Node* operator->(){
        std::cout << "[Shared_ptr] Operator-> called\n";
        return ptr;
    }

    int use_count(){
        return (*count);
    }
};

void fun(Shared_ptr& s){
    if(s.ptr)std::cout << "s.ptr: " << s.ptr << ", *(s.ptr): " \
                       << *(s.ptr) << std::endl;
    else std::cout << "s.ptr: " << s.ptr << ", *(s.ptr): " \
                   << "*(NULL)" << std::endl;
    std::cout << __LINE__ << ": shared_ptr.use_count: " << s.use_count() \
              << std::endl;
    Shared_ptr s2 = s;
    std::cout << __LINE__ << ": shared_ptr.use_count: " << s.use_count() \
              << std::endl;
}

int main(){
    Node node(5);
    Node* ptr = new Node(6);
    Shared_ptr sptr(new Node(7));
    // (sptr.ptr)->key = 8;
    sptr->key = 8;
    std::cout << __LINE__ << ": shared_ptr.use_count: " << sptr.use_count() \
              << std::endl;
    // Shared_ptr sptr2;
    fun(sptr);
    std::cout << __LINE__ << ": shared_ptr.use_count: " << sptr.use_count() \
              << std::endl;
    fun(sptr);
    std::cout << __LINE__ << ": shared_ptr.use_count: " << sptr.use_count() \
              << std::endl;
    return 0;
}