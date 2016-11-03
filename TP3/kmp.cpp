#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

/* Funcion de prefijos */
vector<int> pf(string &t, int t_length) {
  // Inicializo variables
  vector<int> pf(t_length+1);
  pf[0] = -1;
  // Armo vector de prefijos
  for (int i = 0; i < t_length; ++i) {
    pf[i+1] = pf[i];
    while (pf[i+1] > -1 and t[pf[i+1]] != t[i]) {
      pf[i+1] = pf[pf[i+1]];
    }
    pf[i+1]++;
  }
  return pf;
}

/* Funcion principal : Knuth - Morris - Pratt */
int kmp(string &t, string &s) {
  // Inicializo variables
  int res = -1;
  int t_length = t.size();
  int s_length = s.size();
  vector<int> f = pf(t, t_length);
  // en 'm' guardo el maximo indice de 't' menor que el indice del caracter que estoy recorriendo actualmente 
  // en 't', tal que t[0..m] es prefijo de t y al mismo tiempo sufijo de 't'
  int m = 0;

  // Recorro el string principal 's', buscando la presencia del substring 't'
  for (int i = 0; i < s_length; ++i){
    while (m > -1 and t[m] != s[i]) { // retrocedo en t todo lo necesario
      m = f[m];
    }
    m = m + 1;
    if (m == t_length) { // recorri todo t, luego, en el proximo (ultimo) paso, pruebo retroceder con f(t)
      res = i - t_length + 1;
	    m = f[t_length];
    }
  }
  return res;
}

int main(){
  string t, s;
  cin >> s >> t;
  cout << kmp(t, s) << endl;
  return 0;
}