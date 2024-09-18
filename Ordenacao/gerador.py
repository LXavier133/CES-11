import random
f=open("entrada3.txt","w")

alph="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

n=random.randint(0,10000)

f.write(str(n)+"\n")

for _ in range(0,n):
	wrd="\n"
	for __ in range(0,random.randint(1,51)):
		wrd=random.choice(alph)+wrd
	f.write(wrd)

f.close()
