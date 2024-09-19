import numpy as np, matplotlib.pyplot as plt, math


f=open("data_q.txt","r") #m or b or q
lines=f.readlines()
f.close()

sizes=[]
yTime=[]
yNComp=[]

for line in lines:
	line.strip()
	size,time,nComp=line.split(" ")
	sizes.append(int(size))
	yTime.append(float(time))
	yNComp.append(int(nComp))
	
plt.xlabel("Tamanho do vetor")
plt.ylabel("Tempo para ordenar (s)")

plt.plot(sizes,yTime,color="black")

plt.show()

plt.ylabel("Número de Comparações")

plt.plot(sizes,yNComp,color="black")
plt.show()
