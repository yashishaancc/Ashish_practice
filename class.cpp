#include<iostream>
using namespace std;
class Animal{
public:
    static int a;
    void print(){
        cout << "a: " << a << endl;
    }
};
int Animal::a = 2;
int main(){
    Animal a1, a2, a3;
    a1.a = 8;
    a2.a = 9;
    a1.print();
    a2.print();
    a3.print();
}