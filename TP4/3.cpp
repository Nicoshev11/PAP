#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Punto {
  int x, y;

  bool operator < (Punto p) {
    if (x != p.x)
      return x < p.x;
    return y < p.y;
  }
  bool operator == (Punto p) {
    return x == p.x && y == p.y;
  }

  Punto() {}
  Punto(int xx, int yy) {
    x = xx; y = yy;
  }
};

int h, e;
vector<Punto> ph, pe;
Punto pivot;

// Nos dice si los tres Puntos generan un giro anti-horario si devuelve > 0,
// caso contrario es horario (o colinear si da 0)
int ccw(Punto p1, Punto p2, Punto p3) {
  return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
}

// Calcula la distancia cuadrada entre dos puntos
int distancia(Punto a, Punto b)  {
    int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Compara dos puntos por angulo, teniendo en cuenta el pivot que tomamos
// como referencia
bool comp_angulo(Punto a, Punto b) {
  return ccw(pivot, a, b) > 0;
}

float sign(Punto p1, Punto p2, Punto p3) {
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool puntoEnTriangulo(Punto pt, Punto v1, Punto v2, Punto v3) {
  bool b1, b2, b3;
  b1 = sign(pt, v1, v2) < 0.0f;
  b2 = sign(pt, v2, v3) < 0.0f;
  b3 = sign(pt, v3, v1) < 0.0f;
  return ((b1 == b2) && (b2 == b3));
}

// Calcula la cantidad de puntos dentro del triangulo pivot, i, j
vector<vector<int>> mem;
int puntosDentro(int i, int j) {
  int& ret = mem[i][j];
  if (ret != -2) return ret;

  ret = 0;
  for (int k = 0; k < pe.size(); ++k) {
    if (puntoEnTriangulo(pe[k], pivot, ph[i], ph[j])) {
      return (ret = -1);
    }
  }
  for (int k = 1; k < ph.size(); ++k) {
    if (k != i && k != j && puntoEnTriangulo(ph[k], pivot, ph[i], ph[j])) {
      ret++;
    }
  }
  return ret;
}

// dinamica
vector<vector<int> > dp;
int calc(int i, int j) {
  int& ret = dp[i][j];
  if (ret != -1) return ret;

  ret = 0;
  for (int k = j+1; k < ph.size(); ++k) {
    if (ccw(ph[i], ph[j], ph[k]) <= 0) continue;
    int rr = puntosDentro(j, k);
    if (rr != -1) {
      ret = max(ret, calc(j, k) + rr + 1);
    }
  }
  return ret;
}

void setPivot(Punto p) {
  pivot = p;
  for (int i = 0; i<ph.size(); ++i) {
    if (ph[i] == p) {
      swap(ph[0], ph[i]);
      break;
    }
  }
}

int main() {
  //freopen("3.in", "r", stdin);

  // leo entrada
  cin >> h >> e;
  ph.resize(h); pe.resize(e);
  for (int i = 0; i < h; ++i) {
    cin >> ph[i].x >> ph[i].y;
  }
  for (int i = 0; i < e; ++i) {
    cin >> pe[i].x >> pe[i].y;
  }

  vector<Punto> copia_ph(ph);
  int ret = (ph.size() > 0 ? 1 : 0);
  for (Punto p : copia_ph) {
    setPivot(p);
    // Ordenamos los puntos por angulo
    sort(ph.begin()+1, ph.end(), comp_angulo);

    // Limpio la estructura de la dinamica
    dp = vector<vector<int>>(ph.size(), vector<int>(ph.size(), -1));
    mem = vector<vector<int>>(ph.size(), vector<int>(ph.size(), -2));
    
    for (int i = 1; i < ph.size(); ++i) {
      ret = max(ret, calc(0, i) + 2);
    }
  }
  cout << ret << endl;
  return 0;
}
