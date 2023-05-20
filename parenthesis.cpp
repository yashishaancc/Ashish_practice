#include<iostream>
#include<stack>
using namespace std;
bool isValid(string s){
    stack<char> st;
    for(int i = 0; i < s.size(); i++){
        if(!(s[i] == '[' || s[i] == ']' || 
             s[i] == '{' || s[i] == '}' ||
             s[i] == '(' || s[i] == ')')){
            return false;
        }
        if(!st.empty()){
            if(st.top() == '[' && s[i] == ']' ||
                st.top() == '{' && s[i] == '}' ||
                st.top() == '(' && s[i] == ')'){
                st.pop();
                continue;
            }
        }
        st.push(s[i]);
    }
    if(st.empty())return true;
    return false;
}
int main(){
    string str;
    while(true){
        cout << "Enter string: ";
        cin >> str;
        cout << boolalpha << isValid(str) << endl;
    }
}