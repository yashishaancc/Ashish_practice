#include <iostream>
#include "Cat.h"

using namespace std;

int main(){
    {
    Cat cat1;
    cat1.makeHappy();
    cat1.speak();
    }
    // cat1.jump();
    Cat cat2("Bob");
    cat2.makeSad();
    cat2.speak();
    cat2.jump();
    Cat cat3("coc", true);
    cat2.makeSad();
    cat2.speak();
    cat2.jump();
}