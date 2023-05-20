#include<iostream>
using namespace std;

class Animal{
public:
    void speak(){ cout << "Grrr" << endl; }
};

class Cat: public Animal{
public:
    void speak(){ cout << "Meowww" << endl; }
    void jump(){ cout << "jumping" << endl; }
};

class Tiger: public Cat{
public:
    void attack(){ cout << "Attacking" << endl; }
};

int main(){
    Animal a;
    a.speak();
    Cat c;
    c.speak();
    c.jump();
    Tiger t;
    t.speak();
    t.jump();
    t.attack();
}