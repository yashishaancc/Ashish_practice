#include <iostream>
#include "Cat.h"
using namespace std;

void Cat::speak(){
    if(happy)cout << "Meowww!!!" << endl;
    else cout << "Ssssss" << endl;
}

void Cat::jump(){
    cout << "Jumping to top of bookcase" << endl;
}

void Cat::makeHappy(){
    happy = true;
}

void Cat::makeSad(){
    happy = false;
}

Cat::Cat(){
    cout << "Cat created" << endl;
    happy = true;
}

Cat::Cat(string newName){
    name = newName;
    cout << name << endl;
}

Cat::~Cat(){
    cout << "Cat " << name << " destroyed" << endl;
}