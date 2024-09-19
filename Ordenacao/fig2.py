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
plt.ylabel("Número de Comparações")

x=np.linspace(sizes[0],sizes[len(sizes)-1],1000)

plt.plot(sizes,yNComp,color="black")
#plt.plot(x,x**2,color="red",label=r"$n^2")
plt.plot(x,x*np.log2(x),color="red",label=r"nlog(n)")

plt.legend(loc="upper left")

plt.show()



