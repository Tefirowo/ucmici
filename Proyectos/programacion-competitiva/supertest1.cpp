#include <bits/stdc++.h>

using namespace std;

int main(){
    int k;
    int n;

    cout << "Hermanito won, dime cantidad de numeros: ";

    cin >> n;

    vector<int> arrn(n);

    for (k = 0; k < n; k++){
        cout << "Hermanito, digame el valor del numero " << k + 1 << ", (hasta " << n  << "):";

        cin >> arrn.at(k);
        
    }

    cout << "\nAber, tienes un vector con " << n << " elementos y sus valores son: \n";

    for (k = 0; k < n; k++){
        cout << arrn.at(k) << "\n";
    }

    return 0;
}