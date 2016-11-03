#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  //freopen("C.in", "r", stdin);
  int c, a, q;
  cin >> c >> a >> q;
  int m[c+2][a+2], v[c+2][a+2];

  // leo la entrada
  for (int i = 0; i < c; ++i) {
    for (int j = 0; j < a; ++j) {
      cin >> m[i][j];
    }
  }

  // precalculo v
  // casos base
  v[0][0] = 0;
  for (int i = 0; i < c+1; ++i) {
    v[i][0] = 0;
  }
  for (int j = 0; j < a+1; ++j) {
    v[0][j] = 0;
  }
  // caso general
  for (int i = 0; i < c; ++i) {
    for (int j = 0; j < a; ++j) {
      v[i+1][j+1] = v[i+1][j] + v[i][j+1] - v[i][j] + m[i][j];
    }
  }

  // proceso queries
  for (int querie = 0; querie < q; ++querie) {
    int c1, a1, c2, a2;
    cin >> c1 >> a1 >> c2 >> a2;
    cout << v[c2][a2] - v[c1][a2] - v[c2][a1] + v[c1][a1] << endl;
  }

  return 0;
}
