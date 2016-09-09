# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 18:48:57 2016

@author: hh_s
"""
import sys

def fiesta(n):#calculo cuanto suman si van todos los que estan en 1 a la misma fiesta
    ones=[i for i, b in enumerate((bin(n)[2:][::-1])) if b == '1'] # enumerate tira pares (indice,elemento). bin me da un string con 0bXXX donde XXX es n en binario. Saco los primeros 2 caracteres con [2:] y despues hago reverse con [::-1] para tener el indice posta de los unos.
    res=0
    for invitado in ones:#en ones están ordenados min->max los índices de los bits que estaban en 1 en n.
        for invitado2 in ones[(ones.index(invitado))+1:]:
            res+=entrada[invitado][invitado2]
    return res
            
            
   
def dp(n): #interpreto el n como binario donde hay 1 si puedo asignar a una fiesta, 0 si no
    global mejores_fiestas #pongo global porque la edito mas abajo
    if (n & (n-1)==0): #party con 1 persona suma 0, no chequea 0 porque no entra nunca
        return 0
    if (mejores_fiestas[n]!=-1): #si ya tengo solucion, no calculo
        return mejores_fiestas[n]
        
    dp_value=0
    mask_tmp=n
    
    while(mask_tmp!=0): #Igual al for de las diapos solo recorre subsets sin el vacio ni el conjunto original
        mask_tmp=n&(mask_tmp-1)
        opuesto=n&(~mask_tmp) #opuesto es el subconjunto que tiene a los que quedaron sin fiesta en mask_tmp
        if opuesto<mask_tmp: #como recorre subconjuntos de mayor a menor, solo llamo a dp para los que son menores, si el subconjunto da más grande no tiene sentido
            dp_sub=dp(mask_tmp)+dp(opuesto)#sumo la mejor fiestita del subconjunto + la mejor fiestita de los que quedaron afuera
            if dp_value < dp_sub:
                dp_value=dp_sub
    mejores_fiestas[n]=max(diversiones[n],dp_value)#actualizo matriz de resultados de dp                   
    return mejores_fiestas[n]

    
input=sys.stdin
N=int(input.readline())

entrada = [map(int, row.split()) for row in input] #lee entrada Si tiene más lineas que las que dice N, puede explotar

diversiones=[-10 for i in xrange(pow(2,N))] #aca van a ir las 2**N posibles fiestas. Va (-10) por poner algo, puede ser NoNe también. 
mejores_fiestas=[-1 for i in xrange(pow(2,N))] #aca se van a guardar las 2^N - epsilon mejores fiestas combinaciones de fiestas (i.e. las soluciones de dp)
for i in xrange(pow(2,N)):
    if ((i!=0) and (i & (i-1)!=0)):#solo lleno el vector para mas de 1 invitado (este es el epsilon que no llena)
        diversiones[i]=fiesta(i)
print dp(pow(2,N)-1)      
    




    
