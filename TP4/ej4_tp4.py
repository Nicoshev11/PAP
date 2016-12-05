# -*- coding: utf-8 -*-
"""
Created on Sun Dec 04 16:03:52 2016

@author: hh_s
"""
def gcd(a,b):
    """Return greatest common divisor using Euclid's Algorithm."""
    while b:      
        a, b = b, a % b
    return a
    
def ciclos_impares(p):
    n = len(p)
    longitudes=[]
    for i in range(n):
        if p[i]>=0: # if this item has not been visited
            length = 0 # length of current cycle starting with i
            j = i # j is the moving index in the cycle starting with i
            while j!=i or length==0:            
                tmp = j 
                length += 1
                j = p[j]
                p[tmp] = -1  # indicate that this item has been visited
            if length%2==0:
                return []
            else:
                longitudes.append(length)
            print length
    return longitudes

def mod_exp(b,e,m):
    X = b
    E = e
    Y = 1
    while E > 0:
        if E % 2 == 0:
            X = (X * X) % m
            E = E/2
        else:
            Y = (X * Y) % m
            E = E - 1
    return Y

n=int((raw_input().strip())[0])
P= map(int, raw_input().split())
for i in xrange(n):
    P[i]-=1
modulo=int(1e9+7)
print n
print P
longitudes=ciclos_impares(P)
print longitudes
if not longitudes:
    print '0'
else:
    exponente_final=0
    for i in xrange(len(longitudes)):#recorrer por indice
        exponente_final+=((longitudes[i]-1)/2)
        for j in xrange(i+1,len(longitudes)): #recorrer desde L1
                exponente_final+=gcd(longitudes[i],longitudes[j])
    print mod_exp(2,exponente_final,modulo)

