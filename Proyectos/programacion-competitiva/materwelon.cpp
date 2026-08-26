#include <bits/stdc++.h>
using namespace std;


int main(){
    int peso;
    cout << "Ingrese el peso del materwelon: ";
    cin >> peso;
    if (peso < 1 || peso > 100){
        cout << "\nPeso fuera de rango\n";
    }
    else {
        if (peso == 2 || peso == 1){
            cout << "NO\n";
        }
        else if (peso % 2 == 0){
            cout << "SI\n";
        }
        else {
            cout << "NO\n";
        }
    }
    return 0;
}