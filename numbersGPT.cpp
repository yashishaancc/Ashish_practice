#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <limits.h>
using namespace std;
bool sortByFreq(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}
int main() {
    int n;
    cin >> n;
    unordered_map<int, int> freqMap;
    vector<pair<int, int>> freqVec;
    int maxFreq = 0;
    int maxFreqNum = INT_MIN;
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        freqMap[num]++;
        if(freqMap[num] > maxFreq) {
            maxFreq = freqMap[num];
            maxFreqNum = num;
        }
    }
    cout << "Number with maximum frequency: " << maxFreqNum << endl;
    for(auto it = freqMap.begin(); it != freqMap.end(); it++) {
        freqVec.push_back(make_pair(it->first, it->second));
    }
    sort(freqVec.begin(), freqVec.end(), sortByFreq);
    for(int i = 0; i < freqVec.size(); i++) {
        for(int j = 0; j < freqVec[i].second; j++) {
            cout << freqVec[i].first << " ";
        }
    }
    return 0;
}