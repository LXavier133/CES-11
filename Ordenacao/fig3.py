import numpy as np, matplotlib.pyplot as plt, math


f=open("data_b.txt","r") #m or b or q
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
	
plt.xlabel("Tempo de execução (s)")
plt.ylabel("Número de Comparações")

a,b=np.polyfit(yTime, yNComp, 1)

x=np.linspace(yTime[0],yTime[len(yTime)-1],1000)

plt.scatter(yTime,yNComp,color="black",s=10,label="BubbleSort") #change name
plt.plot(x,a*x,color="red",label="Aproximação Linear")

plt.legend(loc="upper left")

plt.show()



