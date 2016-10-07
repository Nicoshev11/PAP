#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include <unordered_set>
using namespace std;

vector<vector<int>> grafo, ejeId, componentes;
vector<int> depth, low, esPuente, cantBiComp;
stack<pair<int, int>> pila;

void reportarComponente(pair<int, int> pi) {
    pair<int, int> tope;
    unordered_set<int> nodos;
    do {
        tope = pila.top(); pila.pop();
        nodos.insert(tope.first);
        nodos.insert(tope.second);
    } while (tope != pi);

    int k = componentes.size();
    componentes.push_back(vector<int>());

    if (nodos.size() > 2) {
        for (int u : nodos) {
            componentes[k].push_back(u);
        }
    }
}

int dfs(int v, int d, int padre) {
    depth[v] = d;
    low[v] = d;

    if (v != padre) {
        pila.push(make_pair(padre, v));
    }

    for (int i = 0; i < grafo[v].size(); ++i) {
        int w = grafo[v][i];
        if (w == padre) continue;
        if (depth[w] == -1) {
            low[v] = min(low[v], dfs(w, d+1, v));
            if (low[w] >= depth[v]) {
                // no me interesa guardarme los puntos de articulacion
                reportarComponente(make_pair(v,w));
            }

            if (low[w] >= depth[w]) {
                // marcar (v, w) como puente
                esPuente[ejeId[v][i]] = 1;
            }
        } else {
            low[v] = min(low[v], depth[w]);
        }
    }
    return low[v];
}

void biconexas(int raiz) {
    depth = vector<int>(grafo.size(), -1);
    low = vector<int>(grafo.size());
    pila = stack<pair<int, int>>();
    componentes.clear();
    dfs(raiz, 0, raiz);
}

void cargarCantBiComp() {
    // Precalcula cuantos nodos hay en las componentes biconexas que cada nodo
    cantBiComp = vector<int>(grafo.size(), 0);

    for (int i = 0; i<componentes.size(); ++i) {
        for (int u : componentes[i]) {
            cantBiComp[u] += componentes[i].size()-1;
        }
    }
}

vector<int> vistoCamino;
int dfsCamino(int pos, int e2) {
    // devuelve -1 si ese camino no lleva a ningun lado y caso contrario la
    // cantidad de puentes en el camino
    if (pos == e2) {
        return 0;
    }
    vistoCamino[pos] = 1;

    for (int i = 0; i<grafo[pos].size(); ++i) {
        int w = grafo[pos][i];
        if (!vistoCamino[w]) {
            int rd = dfsCamino(w, e2);
            if (rd != -1) {
                return rd + esPuente[ejeId[pos][i]];
            }
        }
    }
    return -1;
}

int main() {
    freopen("C.in", "r", stdin);
    // leo el input
    int n, m;
    cin >> n >> m;

    grafo = vector<vector<int>>(n, vector<int>());
    ejeId = vector<vector<int>>(n, vector<int>());
    esPuente = vector<int>(m, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        grafo[u].push_back(v);
        grafo[v].push_back(u);
        ejeId[u].push_back(i);
        ejeId[v].push_back(i);
    }

    // corro precalculo
    biconexas(0);
    cargarCantBiComp();

    // leo cada querie
    int Q;
    cin >> Q;

    for (int q = 0; q<Q; ++q) {
        string letra;
        cin >> letra;
        int e1, e2, c;

        if (letra == "A") {
            cin >> e1 >> e2;
            vistoCamino = vector<int>(n, 0);
            cout << dfsCamino(e1-1, e2-1) << endl;
        } else if (letra == "B") {
            cin >> c;
            cout << esPuente[c-1] << endl;
        } else {
            cin >> e1;
            cout << cantBiComp[e1-1] << endl;
        }
    }
    return 0;
}