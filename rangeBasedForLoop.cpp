#include<iostream>
#include<unordered_map>
using namespace std;
int main(){
    int arr[] = {2, 1, 3, 4, 5};
    for(int x: arr)
        cout << x << " ";
    cout << endl;
    for(auto x: {1, 2, 3, 4, 5}){
        cout << x << " ";
        cout << typeid(x).name() << endl;
    }
    cout << endl;
    for(int &x: arr){
        x++;
        cout << x << " ";
    }
    cout << endl;
    unordered_map<int, string> myMap;
    // Inserting elements into the unordered_map
    myMap.insert(std::make_pair(1, "Apple"));
    myMap.insert(std::make_pair(2, "Banana"));
    myMap.insert(std::make_pair(3, "Orange"));
    for(auto x: myMap){
        cout << x.first << " " << x.second << " ";
        cout << typeid(x).name() << endl;
    }
    cout << endl;
    for(const auto [key, val]: myMap){
        cout << key << " " << val << " ";
        cout << typeid(val).name() << endl;
    }
    cout << endl;
    // next few lines describe how range based for loop is implemented.
    auto begin = std::begin(arr);
    auto end = std::end(arr);
    for(;begin != end; ++begin)
        auto v = *begin;
}