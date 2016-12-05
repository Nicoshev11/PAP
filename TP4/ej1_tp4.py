def pcruz(o, a, b):
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

def comparar(x,y): #compara segun producto cruz
    pc=pcruz(pivot,x,y)    
    if pc>0: #si el producto es positivo x va antes que y
        return -1
    if pc<0:
        return 1
    else:
        if x[1]<y[1]: #si son colineares primero devuelve el de menor coord y
            return 1
        else:#son el mismo punto
            return 0
    


n=int((raw_input().strip())[0])
puntos=[]
for i in xrange(n-2):
    P= map(int, raw_input().split())
    for i in range(0,6,2):
        if ((P[i],P[i+1])) not in puntos:
            puntos.append((P[i],P[i+1]))

pivot=min(puntos) #lo usa la funcion de comparacion
print sorted(puntos,cmp=comparar)
