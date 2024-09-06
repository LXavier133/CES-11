import random

f=open("entrada1.txt","w")
q=open("saida1.txt","w")
alp="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:,! "

for j in range(0,4):
	linha=""
	for i in range(0,random.randint(0,70)):
		linha+=alp[random.randint(0,len(alp)-1)]
	f.write(linha+"\n")
f.write("=========================================\nMESSAGE           FLIGHT  FROM\n\nINICIO              0000	-\n")

q.write("Oi, meu nome é Leonardo e esse é meu primeiro código em C++\nBanana's Enterprise ltda. >>>>>>>>>> Teclado Mecanico\nAUTORIZACOES DE POUSO\n=========================================\nFLIGHT  FROM\n\n")

lis=[]
aqui=[]
urg=[]
nNome={}
for i in range(0,random.randint(0,1000)):
	cod=random.randint(0,4)
	if cod//2 ==0:
		nome=""
		n=random.randint(1,9999)
		while (n in lis):
			n=random.randint(1,9999)
		lis.append(n)
		aqui.append(n)
		nome+=alp[random.randint(0,len(alp)-2)]
		for m in range(0,random.randint(3,29)):
			 nome+=alp[random.randint(0,len(alp)-1)]
		f.write("pede_pouso	"+"{:04n}".format(n)+" "+nome+"\n")
		nNome[n]=nome;
	if cod//2==1:
		f.write("pista_liberada	0000	-\n")
		if len(urg) != 0:
			q.write("{:04n}".format(urg[0])+"\t"+nNome[urg[0]]+"\n")
			del urg[0]
		elif len(aqui) != 0:
			q.write("{:04n}".format(aqui[0])+"\t"+nNome[aqui[0]]+"\n")

			del aqui[0]
		else:
			q.write("0000	Nenhum aviao pousando\n")
	if cod==4 and len(aqui)!=0:		
		n=aqui[random.randint(0,len(aqui)-1)]
		aqui.remove(n)
		urg.append(n);
		f.write("URGENCIA 	"+"{:04n}".format(n)+"	-\n")
f.write("FIM	0000	-")
q.write("\nSituacao da fila\n\n")

if(len(urg)==0 and len(aqui) == 0) :
	q.write("Nada a ser visto por aqui")

while(len(urg)!=0) :
	q.write("{:04n}".format(urg[0])+"\t"+nNome[urg[0]]+"\n")
	del urg[0]
while(len(aqui)!=0) :
	q.write("{:04n}".format(aqui[0])+"\t"+nNome[aqui[0]]+"\n")
	del aqui[0]
f.close()
q.close()
