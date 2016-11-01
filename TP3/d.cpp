#include <iostream>
#include <vector>

using namespace std;


int primerPotenciaDeDos (int valor){ //esta funcion, dado un valor devuelve la menor de las potencias de 2 que cumple con ser mayor o igual al valor. Ej: primerPotenciaDeDos(2)=2. primerPotenciaDeDos(12)=16.
    int i = 0;
    int temp;
    while(true){
        temp = (1<<i);
        if (temp>=valor) return temp;
        i++;
    }
    return 0; //para que no chille nomas
}

pair<int,int> dosMaximos (pair<int,int> maximos1, pair<int,int> maximos2){ //aca usamos que en cada par el primer elemento es el mayor

    if (maximos1.second >= maximos2.first) return maximos1;
    else if (maximos2.second >= maximos1.first) return maximos2;
    else if (maximos1.first >= maximos2.first) return make_pair(maximos1.first, maximos2.first);
    else return make_pair(maximos2.first, maximos1.first);
}


pair<int,int> calcularMaximosIntervalo(vector< pair<int,int> >& SegTree, int root,int minimoIntervalo, int maximoIntervalo, int inicioIntervalo, int finIntervalo){
    pair<int,int> inexistente = make_pair(0,0);
    if(inicioIntervalo >= finIntervalo) return inexistente;
    else if(minimoIntervalo>=maximoIntervalo) return inexistente;
    else if(maximoIntervalo<=inicioIntervalo || minimoIntervalo>=finIntervalo) return inexistente;
    else if(inicioIntervalo<=minimoIntervalo && finIntervalo>=maximoIntervalo) return SegTree[root];
    else {
        pair<int,int> res = dosMaximos(calcularMaximosIntervalo(SegTree, 2*root, minimoIntervalo, (minimoIntervalo+maximoIntervalo)/2, inicioIntervalo, finIntervalo), calcularMaximosIntervalo(SegTree, (2*root)+1, (minimoIntervalo+maximoIntervalo)/2, maximoIntervalo, inicioIntervalo, finIntervalo));
        return res;
    }

    }


int main(){

    int D;
    int R;
    cin >> D;
    cin >> R;
    int Daux = primerPotenciaDeDos(D);
    vector< pair<int,int> > SegTree(2*Daux, make_pair(0,0)); // esto es el segment tree que en cada posicion tiene un par con los dos mayores del intervalo correspondiente. En las hojas se completa con un 0, tomandolo como elemento neutro de la función máximo (siendo que aplica sobre enteros no-negativos). Para facilitar las operaciones de comparación establecemos que dentro de cada par el primer elemento siempre sera mayor o igual al segundo.

    //recordemos que las hojas están en las posiciones [Daux, 2*Daux). Y que los hijos de SegTree[i] son SegTree[i*2] y SegTree[i*2+1]. Asi como el padre de SegTree[i] es SegTree[i/2].

    int diversion;
    for (int i=0; i<D; i++) {
        cin >> diversion;
        SegTree[Daux+i] = make_pair(diversion,0);
    }

    for (int i=Daux-1; i>0; i--){ //completamos los nodos internos del segment tree
        SegTree[i]=dosMaximos(SegTree[i*2],SegTree[i*2+1]);
    }

    pair<int,int> maximosIntervalo;
    int diversionIntervalo;
    int inicio;
    int fin;
    for (int i=0; i<R; i++){
        cin >> inicio;
        cin >> fin;
        maximosIntervalo = calcularMaximosIntervalo(SegTree,1,0,Daux,inicio,fin);
        diversionIntervalo = maximosIntervalo.first + maximosIntervalo.second;
        cout << diversionIntervalo << endl;
    }
    return 0;
}
