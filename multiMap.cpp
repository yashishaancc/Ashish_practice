#include <iostream>
#include <map>
using namespace std;

int main() {
    // Create a multimap
    multimap<int, string> mymap;

    // Insert key-value pairs
    mymap.insert(make_pair(3, "apple"));
    mymap.insert(make_pair(2, "banana"));
    mymap.insert(make_pair(3, "orange"));
    mymap.insert(make_pair(3, "crange"));
    mymap.insert(make_pair(3, "orange"));
    mymap.insert(make_pair(3, "brange"));
    mymap.insert(make_pair(3, "drange"));
    mymap.insert(make_pair(1, "grape"));
    mymap.insert(make_pair(4, "pear"));

    // Iterate through the multimap
    for (auto it = mymap.begin(); it != mymap.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
    }

    return 0;
}