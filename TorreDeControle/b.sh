g++ -o o Lab1_Leonardo_Xavier_Dantas.cpp
while true
do
	python3 gerador.py
	./o || exit 1
	cmp -s saida1.txt Lab1_Leonardo_Xavier_Dantas.txt || exit 1
done
