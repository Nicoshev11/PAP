# -*- coding: utf-8 -*-
"""
Created on Mon Aug 29 13:15:09 2016

@author: hh_s
"""

#Tests simples problema 4
#Uso: python tests_4 | <ejecutable_problema4>

N=6
L=0
si=True #Si quiero que de SI el test, pongo True. Por como genera los tests da si para cualquier L (la matriz inicial es nula y poner si en true hace que la primera matriz de las N sea nula)




matriz_original=[0]*9
if ((L>=1) and (L<=N)):
    print N,L
    print ' '.join(map(str, matriz_original))# imprime matriz original primero
    if(si):
        print ' '.join(map(str, matriz_original))
        N=N-1 #resta uno porque ya imprimió una matriz de las N
    for i in range(N):
        for j in range(9):
            if j<8:
                print (i+j)/2, #como mucho esto es (N+7)/2, no hay problema de rango porque N es como mucho 10000
            else:
                print (i+j)/2
else:
    raise NameError('L es mas grande que N o mas chico que 1')
