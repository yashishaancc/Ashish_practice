#include <iostream>
using namespace std;

class Animal{
    string name;
public:
    Animal(){ cout << "Animal created" << endl;}
    ~Animal(){ cout << "Animal " << name << " destroyed" << endl;}
    // this next one is copy constructor
    Animal(const Animal& otherAn): name(otherAn.name){
        // name = otherAn.name;// no need for this now
        // otherAn.speak();// can't call a non const method, give error
        cout << "Animal created by copying" << endl;
    }
    void setName(string name){ this->name = name;}
    void speak(){ cout << "My name is " << name << endl;}
};

int main(){
    Animal a1;
    a1.setName("Alice");
    Animal a2 = a1;
    a2.speak();
    a2.setName("Bob");
    a1.speak();
    a2.speak();
    Animal a3(a2);
    a3.speak();
    Animal *a4 = new Animal;
    (*a4).setName("Dogy");
    a4->speak();
    delete a4;
}