#include<iostream>
using namespace std;
//This is scoped enum due to class keyword
enum class Color{Red, Green, Blue};
void FillColor(Color color){
    if(color == Color::Red)
        cout << "Red" << endl;
    if(color == Color::Green)
        cout << "Green" << endl;
    if(color == Color::Blue)
        cout << "Blue" << endl;
}
enum Trafficlight{Red, Green, Yellow};
int main(){
    Color c = Color::Red;
    FillColor(c);
    FillColor(Color::Green);
}