#include<iostream>
#include<vector>
using namespace std;
template <typename T>
void print(vector<T> v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
}
int main(){
    vector<int> vi = {1, 2, 3, 4, 5};
    vector<string> vs = {"a", "bc", "def", "ghij", "klmno"};
    vector<float> vf = {.1, .2, .3, .4, .5};
    print(vi);
    print(vs);
    print(vf);
}