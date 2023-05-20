#include<iostream>
using namespace std;
void increment(){
    static int a = 0;
    a++;
    cout << "&a: " << &a << endl;
    cout << "a: " << a << endl;
}
void change(int a){
    a = 2;
    cout << "In change a = " << a << endl;
    // increment();
}
void realChange(int& d){
    d = 9;
    cout << "In realChange d = " << d << endl;
    // increment();
}
int main(){
    cout << boolalpha << true << noboolalpha << endl;
    cout << true << endl;
    if(4 != 4)
        cout << 3 << endl;
    cout << 5 << endl;
    int n = (int)7.55;
    int t = (int)-7.55;
    cout << "\n7/2 = "<< 7/2 << endl;
    cout << "-7/2 = "<< -7/2 << endl;
    cout << "7/-2 = "<< 7/-2 << endl;
    cout << "-7/-2 = "<< -7/-2 << endl;
    cout << "7%2 = "<< 7%2 << endl;
    cout << "-7%2 = "<< -7%2 << endl;
    cout << "7%-2 = "<< 7%-2 << endl;
    cout << "-7%-2 = "<< -7%-2 << endl;
    cout << "n = " << n << endl;
    cout << "n++ = " << n++ << endl;
    cout << "n = " << n << endl;
    cout << "++n = " << ++n << endl;
    cout << "t = " << t << endl << endl;
    char text[] = "hello";
    string str = {'h', '\0', 'e', 'l', 'l'};
    cout << "size of str: " << str.size() << endl;
    cout << str << endl;
    char* p = text;
    for(int i = 0; i < 5; i++)
        cout << p[i];
    cout << endl;
    int v = 5;
    int&v2 = v;
    v2 = 10;
    cout << "v: " << v << endl;
    v = 15;
    cout << "v2: " << v2 << endl;
    int b = 2;
    int c = 3;
    const int *a1 = &b;
    int *const a2 = &c;
    int const* a3 = &c; // same as const int * a3 = &c;
    cout << "\nint b = 2;\nint c = 3;\nconst int *a1 = &b\nint *const a2 = &c\n";
    cout << "a1: " << a1 << ", *a1: " << *a1 << ", b: " << b << endl;
    cout << "a2: " << a2 << ", *a2: " << *a2 << ", c: " << c << endl;
    // a1 = 200; // will not compile as 200 is an int not int*;
    a1 = (int*)300; // this will give segFault in cout << *a1;
    a1 = (int*)0x1234; // this will give segFault in cout << *a1;
    a1 = &c; // this will be okay;
    cout << "a1 = &c;\n";
    cout << "a1: " << a1 << ", *a1: " << *a1 << ", b: " << b << endl;
    cout << "a2: " << a2 << ", *a2: " << *a2 << ", c: " << c << endl;
    // a2 = 100;
    // a2 = 0x1223;
    // a2 = &b; // cannot reassign a2;
    // cout << "a2 = &b;\n";
    // cout << "a1: " << a1 << ", *a1: " << *a1 << ", b: " << b << endl;
    // cout << "a2: " << a2 << ", *a2: " << *a2 << ", c: " << c << endl;
    // *a1 = 4; // cannot reassign *a1
    // cout << "*a1 = 4;\n";
    // cout << "a1: " << a1 << ", *a1: " << *a1 << ", b: " << b << endl;
    // cout << "a2: " << a2 << ", *a2: " << *a2 << ", c: " << c << endl;
    *a2 = 5; // this will be okay
    cout << "*a2 = 5;\n";
    cout << "a1: " << a1 << ", *a1: " << *a1 << ", b: " << b << endl;
    cout << "a2: " << a2 << ", *a2: " << *a2 << ", c: " << c << endl;
    b = 6; c = 7;
    cout << "b = 6; c = 7;\n";
    cout << "a1: " << a1 << ", *a1: " << *a1 << ", b: " << b << endl;
    cout << "a2: " << a2 << ", *a2: " << *a2 << ", c: " << c << endl << endl;
    static int a = 1;
    change(a);
    cout << "After change a = " << a << endl;
    int d = 8;
    cout << "d = " << d << endl;
    realChange(d);
    cout << "After realChange d = " << d << endl;
    int e = 10;
    int const &f = e;
    cout << "f: " << f << endl;
    e = 11;
    // f = 12; // cannot reassign f
    cout << "f: " << f << endl << endl;
    increment();
    // change(b);
    increment();
    // realChange(b);
    increment();
}