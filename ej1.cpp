#include <iostream>
#include <vector>
#include <limits>
#include <iterator>
#include <queue>

using namespace std;

pair< int, vector<int> > BreadthFirstSearch(int cantNodos, vector< vector<int> >& Capacidades, vector< vector<int> >& Vecinos, int fuente, int sumidero, vector< vector<int> >& FuncionFlujo){ //pasado del pseudocodigo de wikipedia

    pair< int,vector<int> > res;
    vector<int> Padres (cantNodos, -1);
    Padres[fuente] = -2; //(make sure source is not rediscovered)
    vector<int> FlujoEnNodo(cantNodos, 0); //(Capacity of found path to node)
    int inf = std::numeric_limits<int>::max();
    FlujoEnNodo[fuente] = inf;
    queue<int> Cola;
    Cola.push(fuente);
    int nodoActual;
    vector<int>::iterator itVecinos;
    while (Cola.size() > 0) {
        nodoActual = Cola.front();
        Cola.pop();
        for (itVecinos = Vecinos[nodoActual].begin(); itVecinos != Vecinos[nodoActual].end(); ++itVecinos){

            if (((Capacidades[nodoActual][*itVecinos] - FuncionFlujo[nodoActual][*itVecinos]) > 0) && (Padres[*itVecinos] == -1) ){ //(If there is available capacity, and v is not seen before in search)
                Padres[*itVecinos] = nodoActual;
                FlujoEnNodo[*itVecinos] = min(FlujoEnNodo[nodoActual], (Capacidades[nodoActual][*itVecinos] - FuncionFlujo[nodoActual][*itVecinos]));
                if (*itVecinos != sumidero){
                    Cola.push(*itVecinos);
                }else{
                    res = make_pair(FlujoEnNodo[sumidero], Padres);
                    return res;
                }
            }
        }
    }
    res = make_pair(0, Padres);
    return res;
}

int EdmondsKarp(int cantNodos, vector< vector<int> >& Capacidades, vector< vector<int> >& Vecinos, int fuente, int sumidero){ //pasado del pseudocodigo de wikipedia

    int flujoTotal = 0;

    vector< vector<int> > FuncionFlujo (cantNodos, vector<int>(cantNodos, 0)); //Residual capacity from u to v is Capacidades[u][v] - FuncionFlujo[u][v])

    pair< int, vector<int> > bfsResult; //el first es el aumento del flujo y el second es el camino de aumento

    int nodoAux1;
    int nodoAux2;
    while (true){

        bfsResult = BreadthFirstSearch(cantNodos, Capacidades, Vecinos, fuente, sumidero, FuncionFlujo);

        if (bfsResult.first == 0) break;

        flujoTotal += bfsResult.first;

        //(Backtrack search, and write flow)
        nodoAux2 = sumidero;
        while (nodoAux2 != fuente){
            nodoAux1 = bfsResult.second[nodoAux2]; //es decir nodoAux1 es el padre de nodoAux2 en el camino de aumento que me dio el BFS
            FuncionFlujo[nodoAux1][nodoAux2] += bfsResult.first;
            FuncionFlujo[nodoAux2][nodoAux1] -= bfsResult.first;
            nodoAux2 = nodoAux1;
        }
    }
    return flujoTotal;
}



int nodoRepresentante(int cantEsquinas, int numeroDeEsquina, char parteEsquina){ //esto devuelve, dada una esquina y un char 'a' o 'b' el nodo que representa a lo buscado. Si numeroDeEsquina es 0 se asume que es la fuente y si es cantEsquinas*2+1 se asume que es el sumidero.

    if (numeroDeEsquina==0 || numeroDeEsquina==(cantEsquinas*2+1)) return numeroDeEsquina;
    if (parteEsquina=='a') return numeroDeEsquina;
    else if (parteEsquina=='b') return (numeroDeEsquina+cantEsquinas);
}

void duplicarEsquina(int cantEsquinas, int numeroDeEsquina, vector< vector<int> >& Vecinos, vector< vector<int> >& Capacidades){

    int nodoA = nodoRepresentante(cantEsquinas, numeroDeEsquina, 'a');
    int nodoB = nodoRepresentante(cantEsquinas, numeroDeEsquina, 'b');

    Vecinos[nodoA].push_back(nodoB);

    Capacidades[nodoA][nodoB] = 1;
}

void conectarEsquinas(int cantEsquinas, int numeroDeEsquinaX, int numeroDeEsquinaY, vector< vector<int> >& Vecinos, vector< vector<int> >& Capacidades){

    if (numeroDeEsquinaX==numeroDeEsquinaY) {
        cout << endl << "Se intento conectar dos esquinas que en realidad son la misma: la " << numeroDeEsquinaX << endl;
        return;
    }

    int nodoXA = nodoRepresentante(cantEsquinas, numeroDeEsquinaX, 'a');
    int nodoXB = nodoRepresentante(cantEsquinas, numeroDeEsquinaX, 'b');
    int nodoYA = nodoRepresentante(cantEsquinas, numeroDeEsquinaY, 'a');
    int nodoYB = nodoRepresentante(cantEsquinas, numeroDeEsquinaY, 'b');

    Vecinos[nodoXB].push_back(nodoYA);
    Vecinos[nodoYB].push_back(nodoXA);
    int inf = std::numeric_limits<int>::max();
    Capacidades[nodoXB][nodoYA] = inf;
    Capacidades[nodoYB][nodoXA] = inf;
}

int main(){

	int cantEsquinas;
	int cantCalles;
	cin >> cantEsquinas;
	cin >> cantCalles;

	int cantNodos = (cantEsquinas*2+2); //porque cada esquina la duplicamos y ademas agregamos la fuente y el sumidero.
    int fuente = 0;
    int sumidero = cantNodos-1;

    vector< vector<int> > Capacidades (cantNodos, vector<int>(cantNodos));
    vector< vector<int> > Vecinos (cantNodos, vector<int>(1));

    char tipoEsquina;
    for(int i=1; i<=cantEsquinas; i++){
        duplicarEsquina(cantEsquinas, i, Vecinos, Capacidades); //duplico todas las esquinas
        cin>>tipoEsquina;
        if(tipoEsquina=='A'){
            conectarEsquinas(cantEsquinas, fuente, i, Vecinos, Capacidades); //si es la casa de un estudiante, la hago vecino con la fuente.
        }else if (tipoEsquina=='E'){
            conectarEsquinas(cantEsquinas, sumidero, i, Vecinos, Capacidades); //si es una escuela la hago vecino con el sumidero.
        }else if (tipoEsquina!='X'){
            cout << endl << "se leyo un tipo de esquina inexistente" << endl;
        }
    }

    int esquinaX;
    int esquinaY;
    for(int i=0; i<cantCalles; i++){
        cin>>esquinaX;
        cin>>esquinaY;
        conectarEsquinas(cantEsquinas, esquinaX, esquinaY, Vecinos, Capacidades);
    }

    int flujoMaximo = EdmondsKarp(cantNodos, Capacidades, Vecinos, fuente, sumidero);
    cout << flujoMaximo;
    return 0;
}
