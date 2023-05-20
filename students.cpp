#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;
void printMap(unordered_map<string, int> umap){
    cout << "Database: \n";
    for(auto it = umap.begin(); it != umap.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
}
int main(){
    unordered_map<string, int> umap;
    for(int i = 0; i < 1000; i++){
        string str, Name, Old, New;
        int age;
        printMap(umap);
        cout << "\x1b[33mpossible commands are: \n"
             << "add Name age \n"
             << "find Name \n"
             << "change oldName newName \n"
             << "del Name\n\x1b[0m";
        cin >> str;
        if(str == "add"){
            cin >> Name >> age;
            umap.insert(make_pair(Name, age));
        }
        if(str == "find"){
            cin >> Name;
            if(umap.find(Name) != umap.end())
                cout << umap.find(Name)->second << endl;
            else cout << "Not found\n";
        }
        if(str == "change"){
            cin >> Old >> New;
            int f = 0, val;
            auto itr = umap.find(Old);
            if(itr != umap.end()){
                val = itr->second;
                umap.erase(itr);
                umap.insert(make_pair(New, val));
            }
            else cout << "Not found\n";
        }
        if(str == "del"){
            cin >> Name;
            umap.erase(Name);
        }
    }
}