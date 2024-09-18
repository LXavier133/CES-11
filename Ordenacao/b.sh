read -p "Nome do código: " cod
g++ -o o "${cod}"
i=0
while true
do
	i=$((i+1))
	echo $i | python3 gerador.py
	read -r comp t <<< $(./o)
	if [ $(echo "$t > 2" | bc) -ne 0 ]
	then
    		echo "$i $comp $t"
		exit 0
    	fi
done
