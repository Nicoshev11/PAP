#include <vector>
#include <iostream>

using namespace std;

char compare(vector<vector<long long int> > const &valores, int i, int j) {
	bool less = valores[i][0] < valores[j][0];
	for (int k = 0; k < valores[i].size(); ++k){
		if (valores[i][k] == valores[j][k] || (valores[i][k] < valores[j][k] != less))
			return 0;
	}
	if (less) {
		return -1;
	} else {
		return 1;
	}
}

void buildGraph(vector<vector<long long int> > const &valores, vector<vector<bool> >  &grafo) {
	vector<vector<char> > adyMatrix (valores.size(), vector<char> (valores.size(), 0));
	for (int i = 0; i < valores.size(); ++i){
		for (int j = 0; j < i; ++j){
			adyMatrix[i][j] = -adyMatrix[j][i];
		}
		for (int j = i+1; j < valores.size(); ++j){
			adyMatrix[i][j] = compare(valores, i, j);
		}	
	}
	for (int i = 1; i <= valores.size(); ++i) {
		grafo[0][i] = true;
		for (int j = 1; j <= valores.size(); ++j){
			grafo[i][j+valores.size()] = adyMatrix[i-1][j-1] < 0; 
		}
		grafo[i+valores.size()][(valores.size()*2)+1] = true;
	}
}

void updateGraph(vector<vector<bool> >  &grafo, vector<int> const &previousNode) {
	int u = previousNode[previousNode.size()-1];
	int v = previousNode.size()-1;
	while (u != -1) {
		grafo[u][v] = false;
		grafo[v][u] = true;
		v = u;
		u = previousNode[u];
	}
	return;
}

bool hasPathFromSourceToSink(vector<vector<bool> > const &grafo, vector<int>  &previousNode) {
	for (int i = 0; i < previousNode.size(); ++i)
		previousNode[i] = -1;  //inicializamos todos los nodos como no tocados (que el 0 quede en -1 es util)
	vector<int> pila (1, 0);  //inicializamos la pila solo con el nodo source
	pila.reserve(grafo.size());
	while (pila.size()>0) {
		int top = pila.back();
		pila.pop_back();
		if (grafo[top][grafo.size()-1]) {
			previousNode[grafo.size()-1] = top;
			return true;
		}
		for (int i = 1; i < grafo.size()-1; ++i){
			if (grafo[top][i] && previousNode[i]==-1) {
				pila.push_back(i);
				previousNode[i] = top;
			}
		}
	}
	return false;
}

int main() {

	int cantAcciones, cantDias;
	cin >> cantAcciones >> cantDias;
	long long int tmp; //como no hay cota en el anunciado para el valor de las acciones, mandamos long long : p

	vector<vector<long long int> > valores (cantAcciones, vector<long long int> (cantDias) );	
	for (int i = 0; i < cantAcciones; ++i){
		for (int j = 0; j < cantDias; ++j){
			cin >> tmp;
			valores[i][j] = tmp;
		}
	}

	vector<vector<bool> > grafo ((valores.size()*2)+2, vector<bool> ((valores.size()*2)+2, false)); //deberia ser false por default aunque no este explicito, pero por las dudas lo ponemos :p
	
	buildGraph(valores, grafo);

	vector<int> previousNode (grafo.size());
	while(hasPathFromSourceToSink(grafo, previousNode)){
		updateGraph(grafo, previousNode);
	}

	int matchingCardinal = 0;
	for (int i = valores.size()+1; i <= valores.size()*2; ++i){
		for (int j = 1; j <= valores.size(); ++j) {
			if (grafo[i][j])
				matchingCardinal++;
		}
	}

	cout << cantAcciones-matchingCardinal << endl;

	return 0;
}