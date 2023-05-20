#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<limits.h>
using namespace std;
bool sortByFreq(pair<int, int> f, pair<int, int> s){
    return f.second > s.second;
}
int main(){
    int n, num, maxFreq = 0, maxFreqNum = INT_MIN;
    cout << "Enter number of numbers: ";
    cin >> n;
    unordered_map<int, int> map;
    vector<pair<int,int>> vec;
    cout << "Enter numbers: ";
    for(int i = 0; i < n; i++){
        cin >> num;
        map[num]++;
        if(map[num] > maxFreq){
            maxFreq = map[num];
            maxFreqNum = num;
        }
    }
    cout << "Number with maximum frequency: " << maxFreqNum;
    cout << endl;
    cout << "Maximum frequency: " << maxFreq;
    cout << endl;
    for(auto it = map.begin(); it != map.end(); it++){
        vec.push_back(make_pair(it->first, it->second));
    }
    sort(vec.begin(), vec.end(), sortByFreq);
    for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec[i].second; j++){
            cout << vec[i].first << " ";
        }
    }
    cout << endl;
}