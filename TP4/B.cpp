#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

bool invertedSort (int i,int j) { return (i>j); }

int main(){

	int n;
	cin >> n;

	vector<double> nums (n);

	for (int i = 0; i < n; ++i) {
		double tmp;
		cin >> tmp;
		nums[i] = tmp;
	}

	if (n == 1) {
		cout << 1 << endl;
		return 0;
	}

	sort(nums.begin(), nums.end());

	std::vector<double> cantRep (n+1, 1);

	for (int i = n-2; i >= 0; --i) {
		if (nums[i+1]==nums[i]) {
			cantRep[i] += cantRep[i+1];
		}
	}

	double sol = 0;

	vector<double> probAcum (n, 0);

	for (int i = 0; i < n-1; ++i) {
		double x = (1-probAcum[i]);
		for (int j = i+1; j < n-1; ++j) {
			x /= (n-j);
			x *= cantRep[j];
			probAcum[j] += x;
		}
		sol += ((1-probAcum[i]) * (n-i) / cantRep[i]); 
	}

	cout << sol << endl;

	return 0;
}