#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iomanip>
#include <set>
using namespace std;
#define ll long long
const int MAX = 1000005;

int n, a[MAX];

int main() {
	// Leo la entrada
	cin >> n;
	for(int i=1; i<=n; i++) cin >> a[i];

	// Resuelvo: 
	// EXTRA: esta comentado el codigo para si quisieramos guardar inicio y fin del subarreglo solucion
	// int init = 1, fin = 1, init_new = 1;
	int suma_actual = 0, suma_max = 0;
	int i = 1;
	while(i <= n) {
		suma_actual += a[i];
		if(suma_actual < 0) {
			suma_actual = 0;
			//init_new = i+1;
		}
		if(suma_actual > suma_max) {
			suma_max = suma_actual;
			//init = init_new;
			//fin = i;
		}
		i++;
	}

	cout << suma_max << endl;
	// cout << "Desde " << init << " hasta " << fin << endl;

	return 0;
}