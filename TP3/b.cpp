#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct nodo {
	int cnt;
	map<char, nodo> letterArray;
	nodo(){cnt = 0;}
};

int main(){
	
	int cantWords;
	cin >> cantWords;
	nodo root = nodo();
	vector<nodo*> words;
	words.reserve(cantWords);
	for (int i = 0; i < cantWords; ++i){
		string email;
		int prefix;
		cin >> email >> prefix;
		nodo* currentNode = &root;
		for (int j = 0; j < prefix; ++j){
			currentNode = &(currentNode->letterArray[email[j]]);
			currentNode->cnt++;
		}
		words.push_back(currentNode);
		for (int j = prefix; j < email.size(); ++j){
			currentNode = &(currentNode->letterArray[email[j]]);
			currentNode->cnt++;
		}
	}
	int sol = 0;
	for (int i = 0; i < cantWords; ++i){
		if (words[i]->cnt > sol)
			sol = words[i]->cnt;
	}
	cout << sol << endl;
	return 0;
}