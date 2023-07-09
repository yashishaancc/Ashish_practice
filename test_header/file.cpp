#include <iostream>
#include<sstream>
#include "file.h"

Test::Test():a(1){
    this->a = 0;
    a = 3;
    this->print();
}

Test::Test(int a){
    this->a = a;
    this->print();
}

Test::~Test(){
    std::cout << "Destroyed" << std::endl;
}

int Test::get(){
    return this->a;
}

void Test::set(int a){
    this->a = a;
    this->print();
}

void Test::initialize(int a){
    this->a = a;
    this->print();
}

void Test::print(){
    std::cout << "a: " << a << std::endl;
    std::cout << "this: " << this << std::endl;
}

void Test::add(int inc){
    a = a + inc;
    this->print();
}

int main(){
    Test t0;

    Test t1(2);
    t1.set(54);
    int b = t1.get();
    std::cout << "Address of t1: " << &t1 << std::endl;
    std::string name = "Bob";
    int age = 32;
    std::stringstream ss;
    ss << "Name is: ";
    ss << name;
    ss << "; Age is: ";
    ss << age;
    std::string info = ss.str();
    std::cout << info << std::endl;
    // t1.initialize(2);

    Test *t2 = new Test(5);
    t2->initialize(3);
    delete t2;
}