#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Create a vector
    vector<int> myvec;

    // Add elements to the vector
    myvec.push_back(5);
    myvec.push_back(2);
    myvec.push_back(3);
    myvec.push_back(8);

    // Access elements by index
    cout << "The first element of the vector is: " << myvec[0] << endl;

    // Modify elements by index
    myvec[1] = 4;
    cout << "The second element of the vector is now: " << myvec[1] << endl;

    // Iterate through the vector
    for (int i = 0; i < myvec.size(); ++i) {
        cout << myvec[i] << endl;
    }
    myvec.pop_back();
    for (int i = 0; i < myvec.size(); ++i) {
        cout << myvec[i] << endl;
    }
    return 0;
}