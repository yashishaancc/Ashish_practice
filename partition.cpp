#include<iostream>
using namespace std;
void partition(int n, int max, int arr[], int len, int& count){
    if(n == 0){
        for(int i = 0; i < len; i++){
            cout << arr[i];
            if(i != len-1)cout << "+";
        }
        cout << endl;
        count++;
        return;
    }
    int s = max < n ? max : n;
    for(int i = s; i > 0; i--){
        arr[len] = i;
        partition(n-i, i, arr, len+1, count);
    }
}
int main(){
    int n;
    while(true){
        cout << "Enter a number(0 to 40) whose partitions you want to find: ";
        cin >> n;
        int arr[n];
        int count  = 0;
        partition(n, n, arr, 0, count);
        cout << "Number of partitions of " << n << " are: " << count << endl;
    }
    return 0;
}