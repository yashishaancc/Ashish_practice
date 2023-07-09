#ifndef CAT_H_
#define CAT_H_
#include<iostream>
using namespace std;

class Cat{
private:
    bool happy;
    string name;
public:
    void speak();
    void jump();
    void makeHappy();
    void makeSad();
    Cat();
    Cat(string name);
    Cat(string name, bool Happy): name(name){ name = name; happy = Happy;}
    ~Cat();
};

#endif /* CAT_H_ */