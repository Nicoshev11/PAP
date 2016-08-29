#include <vector>
#include <iostream>
#include "matriz.h"
#include <utility>

using namespace std;

int main(){
	int n, l;
	cin >> n >> l;
	Matriz expected;
	cin >> expected;
	vector<pair<int, int> > stack;
	int height = 0;
	for (int width = 1; l>1; l /= 2){
		if (l&1==1){
			stack.push_back(make_pair(height, width));
		}
		height++;
		width = width << 1;
	}
	vector<vector<Matriz> > dc (height+stack.size()+1, vector<Matriz> (0));
	Matriz tmp;	
	for (int i = 0; i < n; ++i){
		cin >>  tmp; 
		dc[0].push_back(tmp);
	}
	int diff = 1;
	for (int i = 0; i < height; ++i){
		for (int j = 0; j < n-diff; ++j){
			tmp = dc[i][j] * dc[i][j+diff];
			dc[i+1].push_back(tmp);
		}
		diff *= 2;
	}
	for (int i = height; i < stack.size()+height; ++i){
		int h = stack.back().first;
		for (int j = 0; j < n-diff; ++j){
			tmp = dc[i][j] * dc[h][j+diff];
			dc[i+1].push_back(tmp);
		}
		diff += stack.back().second;
	}
	for (int i = 0; i < dc.back().size(); ++i){
		if (dc.back()[i] == expected){
			cout << "SI" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
}