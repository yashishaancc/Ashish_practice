#include<iostream>
#include<vector>
// #include<string>
using namespace std;
#define INFO_MSG(msg) printf("[%d][%s] %s\n", __LINE__, __func__, msg);

template <typename T>
void print(T x){
    INFO_MSG("START");
    cout << "TypeID: " << typeid(T).name() << endl;
    cout << x << " ";
}

template <typename T>
void print(vector<T> v){
    INFO_MSG("START");
    cout << "TypeID: " << typeid(T).name() << endl;
    for(auto x: v){
        print(x);
    }
    cout << endl;
}

template <typename T>
ostream& operator<<(ostream& os, vector<T> v){
    for(const auto& x: v){
        os << x << " ";
    }
    cout << endl;
    return os;
}

int main(){
    vector<int> v1 = {1, 3, 2};
    vector<char> v2 = {'h', 'e', 'l'};
    vector<string> v3 = {"h", "e", "ll"};
    vector<vector<int>> v4;
    // cout << v4;
    for(int i = 0; i < 10; i++){
        vector<int> v(i+1,i);
        // for(int j = 0; j <= i; j++){

        // }
        v4.push_back(v);
        // print(v);
    }
    cout << v4;
    // print(v1);
    // print(v2);
    // print(v3);
    // print(v4);
}