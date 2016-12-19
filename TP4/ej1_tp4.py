def pcruz(o, a, b):
    return ( o[0] -a[0]) * (-b[1] + o[1]) - (-a[1] + o[1]) * (-b[0] + o[0])

def comparar(x,y): #compara segun producto cruz
    pc=pcruz(pivot,x,y)
    if pc<0: 
        return -1
    if pc>0:
        return 1
    else:
#        return 0
        if x[1]<y[1]: #si son colineares primero devuelve el de menor coord y
            return -1
        else:#son el mismo punto
            return 1
#            if x[0]<y[0]:
#                return -1
#            else:
#                return 0
#    


n=int((raw_input()))
#print n
puntos=[]
for i in xrange(n-2):
    P= map(int, raw_input().split())
    for i in range(0,6,2):
         puntos.append((P[i],P[i+1]))
pivot=min(puntos) #lo usa la funcion de comparacion
a=set(puntos)
a.remove(pivot)
print pivot[0],pivot[1],
for elem in sorted(a,cmp=comparar):
    print elem[0],elem[1],
