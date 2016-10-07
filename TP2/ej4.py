# -*- coding: utf-8 -*-
"""
Created on Mon Oct 03 23:07:55 2016

@author: hh_s
"""

def visitar(G,v,visitado,terminados): 
    visitado[v]=True
    for vecino in G[v]:
        if not visitado[vecino]:
            visitar(G, vecino, visitado,terminados)
    terminados.append(v)#lo agrega cuando no tiene mas ejes de salida o cuando todos apuntan a nodos visitados

def DFS(G,n):
    terminados=[]
    visitado=[False]*n# el *n crea una lista de n elementos en False.
    for v in xrange(n):
        if not visitado[v]:
            visitar(G, v, visitado, terminados)
    return terminados

def visitar_scc(G, v, SCC,scc_actual): #visita toda una scc
    SCC[v] = scc_actual
    for vecino in G[v]:
        if not SCC[vecino]: #es lo mismo SCC==0
            visitar_scc(G, vecino, SCC,scc_actual)

def DFS_mod(G,n,orden):
    scc_actual = 0
    SCC=[0]*n #la SCC 0 significa que no tiene asignada una SCC.
    for v in orden:
        if  (SCC[v]==0):
            scc_actual += 1 #cambio de scc
            visitar_scc(G, v, SCC, scc_actual)
    return SCC


n, e = (int(i) for i in raw_input().strip().split())

G = [[] for i in xrange(n)]
Gt = [[] for i in xrange(n)]
for i in xrange(e): #construyo lista de adyacencias con el input. El nodo 1 esta en la posicion 0, el 2 en la 1 and so on.
    u, v = (int(i) for i in raw_input().strip().split())
    G[u-1].append(v-1)
    Gt[v-1].append(u-1)



terminados=DFS(G,n)
componentes=DFS_mod(Gt, n,reversed(terminados))#componentes tiene en el indice correspondiente a cada nodo la componente a la que pertenece

q=int((raw_input().strip().split())[0])#cantidad de preguntas

for i in xrange(q):
    f, t = (int(i) for i in raw_input().strip().split())
    if componentes[f-1]==componentes[t-1]:
        print "S"
    else:
        print "N"
