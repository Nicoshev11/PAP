#include <iostream>
#include <vector>
#include <algorithm>    // std::sort
#include <iterator>

using namespace std;


long double busquedaBinariaPorDebajo(vector<long double>::iterator ppio, vector<long double>::iterator fin, long double buscar){

	vector<long double>::iterator low;
	fin--;
	low = lower_bound(ppio, fin, buscar); //O(log2(2^(N/2)))= O(N/2)
	if ( *low>buscar) low--; //este es el caso en el que no hay ningun elemento igual pero hay elementos mayores, ya que lower_bound devuelve el primer elemento mayor o igual en caso de existir, o el elemento más cercano "por debajo" en caso de no haber ninguno mayor o igual.
	return *low;
}

int main(){

	long double dineroDisponible;
	int cantPaquetes;
	cin >> dineroDisponible;
	cin >> cantPaquetes;

    vector<long double> paquetes(cantPaquetes, 0);
    long double cantDonasPaquete;
    for(int i=0; i<cantPaquetes; i++){
        cin >> cantDonasPaquete;
        paquetes[i]=cantDonasPaquete;
    }
	int mitad = cantPaquetes/2; // recordemos que tomamos los intervalos cerrados a izquierda y abiertos a derecha, osea el primero seria [0,mitad) y el segundo [mitad,cantPaquetes).

	vector<long double> subTotales1((1<<mitad), -1);
	vector<long double> subTotales2((1<<(cantPaquetes-mitad)), -1);


	for(int maskActual = 0; maskActual<(1<<mitad); maskActual++){ //esto recorre todos los posibles subconjuntos de la primer mitad de paquetes (2^(N/2) conjuntos) y para cada uno corre (N/2) veces el if (que internamente es O(1)). En total es O((2^(N/2))*(N/2))
		subTotales1[maskActual]=0;
		for(int i=0; i<mitad; i++){
			if ((maskActual & (1<<i)) == (1<<i)){
				subTotales1[maskActual]+= paquetes[i]; //para cada uno de los posibles paquetes se fija si está en mi conjunto y de ser asi lo suma.
			}
		}
		if (subTotales1[maskActual]>dineroDisponible) subTotales1[maskActual]=0;//para no hacer cuentas de más
	}


	for(int maskActual = 0; maskActual<(1<<(cantPaquetes-mitad)); maskActual++){ //mismo que el anterior pero para la segunda mitad de paquetes, misma complejidad.
		subTotales2[maskActual]=0;
		for(int i=0; i<(cantPaquetes-mitad); i++){
			if ((maskActual & (1<<i)) == (1<<i)){
				subTotales2[maskActual]+= paquetes[i+mitad];
			}
		}
		if (subTotales2[maskActual]>dineroDisponible) subTotales2[maskActual]=0;
	}

	vector<long double>::iterator it1;
    vector<long double>::iterator it2;

	sort(subTotales1.begin(), subTotales1.end()); //complejidad O((2^(N/2))*log2(2^(N/2)))= O(2^(N/2))*(N/2))
	it1 = unique(subTotales1.begin(), subTotales1.end()); //O(2^(N/2))
    subTotales1.resize(distance(subTotales1.begin(),it1));

    sort(subTotales2.begin(), subTotales2.end()); //complejidad O((2^(N/2))*log2(2^(N/2)))= O(2^(N/2))*(N/2))
    it2 = unique(subTotales2.begin(), subTotales2.end()); //O(2^(N/2))
    subTotales2.resize(distance(subTotales2.begin(),it2));

	long double rta = 0;
	long double primerMitad;
	long double segundaMitadIdeal;
	long double segundaMitadOptima;
	for(vector<long double>::const_iterator i = subTotales1.begin(); i != subTotales1.end(); ++i){ //este ciclo es O((2^(N/2))*(N/2))
		primerMitad = *i;
		segundaMitadIdeal = dineroDisponible-primerMitad;
		if (segundaMitadIdeal>=0){
			segundaMitadOptima = busquedaBinariaPorDebajo(subTotales2.begin(), subTotales2.end(), segundaMitadIdeal); //O(log2(2^(N/2)))=O(N/2)
			if (rta<(primerMitad+segundaMitadOptima)) rta = primerMitad+segundaMitadOptima;
		}
	}

    if(rta<0) cout << endl << "Evidentemente hubo un error, la respuesta parece ser negativa.";
    else cout << (int)rta << endl;

	return 0;
}
