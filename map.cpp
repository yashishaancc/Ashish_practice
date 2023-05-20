#include <iostream>
#include <map>
using namespace std;

int main() {
    // Create a map
    map<string, int> mymap;

    // Insert key-value pairs
    mymap.insert(make_pair("apple", 5));
    mymap.insert(make_pair("banana", 2));
    mymap.insert(make_pair("orange", 3));
    mymap.insert(make_pair("orange", 3));
    mymap.insert(make_pair("Grape", 8));

    // Access a value by key
    cout << "The value of apple is: " << mymap["apple"] << endl;

    // Modify a value by key
    mymap["banana"] = 4;
    cout << "The new value of banana is: " << mymap["banana"] << endl;

    // Iterate through the map
    for (auto it = mymap.begin(); it != mymap.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
    }

    return 0;
}