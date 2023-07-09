#include<iostream>
#include<vector>
#include<tuple>
// using namespace std;

template <typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream& os, std::tuple<T1, T2, T3> t){
    // for(const auto& x: t){
    //     os << x << " ";
    // }
    os << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t);
    std::cout << std::endl;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v){
    for(const auto& x: v){
        os << x << " ";
    }
    std::cout << std::endl;
    return os;
}

int main(){
    std::tuple<int, char, std::string> t1(2, 'e', "hello");
    std::tuple<int, char, std::string> t2(4, 'r', "hello2");
    std::tuple<int, char, std::string> t3 = std::make_tuple(8, 't', "hello3");
    std::cout << t1;
    std::cout << t3;
    std::vector<std::tuple<int, char, std::string>> v;
    v.push_back(t1);
    v.push_back(t2);
    std::cout << v;
}
