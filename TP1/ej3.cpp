#include<vector>
#include<iostream>

using namespace std;

int main(){
	long long int n, tmp;
	cin >> n;
	if (n<=0) {
		cout << 0 << endl;
		return 0;
	}
	vector<long long int> intervalos;
	intervalos.reserve(n);
	cin >> tmp;
	bool esNegativo = tmp < 0;
	intervalos.push_back(tmp);
	for (int i = 1; i < n; ++i){
		cin >> tmp;
		if (esNegativo == tmp < 0){
			intervalos.back() += tmp;
		} else {
			intervalos.push_back(tmp);
			esNegativo ^= true;
		}
	}
	long long int best = 0;
	long long int current = 0;
	for (int i = 0; i < intervalos.size(); ++i){
		if (intervalos[i]+current <= 0) {
			current = 0;
		} else {
			current+=intervalos[i];
			if (current > best) {
				best=current;
			}
		}
	}
	cout << best << endl;
}