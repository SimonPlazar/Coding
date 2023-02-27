#!/bin/bash

#set -x

OUTPUT=""
CURDIR=$(pwd) #trenutni dir

#for i in $(find . -name "posel_"*".sh" -type f | grep $); do 
#find . -type f -name "posel_"*".sh" | grep $ | while read i; do 
while read i; do 
	read -r line<"$i" # prebere prvo vrstico
	if [[ "$line" == "#!/bin/bash" ]]; then
		#has #!/bin/bash first line
		
		DIR=$(dirname "$i") #dir datoteke, ki se bo izvedla
		FILE=$(basename "$i") #ime datoteke, ki se bo izvedla

		cd "$DIR" #premakni se v dir datoteke
		FILENAME="${FILE::-2}out" #ime out datoteke

		touch "$FILENAME" #kreira file ce je potrebno
		
		out="$(bash "$FILE")" #zapise v out output scripta
		
		
		if [[ $out == *"Fail" ]]; then
			OUTPUT+='"'"$FILE"'"'", " # doda ime fajla v output spremenljivko
		elif [[ $out == *"Ok" ]]; then
			echo "$out" > "$FILENAME" # zapise v .out file vsebino out
		fi
		
		cd $CURDIR #nazaj v glavni dir	
	fi
	
done <<< $(find . -type f -name "posel_*.sh" | grep $)

if [[ $OUTPUT ]]; then
	echo "${OUTPUT::-2}" # izpis neuspesnih poslov
fi

#set +x
