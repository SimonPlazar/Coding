#!/usr/bin/env bash

FLAG_IME="false"
FLAG_DELOVNA_POT="false"
FLAG_POT_PROGRAMA="false"

while getopts ":hc:d:e:" OPTION; do
	case $OPTION in
	h)
		echo "bash listproc.sh [-h] [-c] [-d] [-e]"
		exit
		;;
	c)
		ukazno_ime=$OPTARG
		FLAG_IME="true";
		;;
	d)
		delovna_pot=$OPTARG
		FLAG_DELOVNA_POT="true";
		;;
	e)
		pot_programa=$OPTARG
		FLAG_POT_PROGRAMA="true";
		;;
	*)
		echo "Incorrect options provided" >&2
		exit 1
		;;
	esac
done

# OPTIND == 1 če ni podano nobenih parametrov
if (( $OPTIND == 1 )); then
	echo "bash listproc.sh [-h] [-c] [-d] [-e]"
	exit
fi

#~ echo "ukazno_ime -> $ukazno_ime"
#~ echo "delovna_pot -> $delovna_pot"
#~ echo "pot_programa -> $pot_programa"

currDir=$(pwd)
cd /proc
array+=($(ls -d [0-9]*/))

for i in "${array[@]}"
do :
	if test -d /proc/"$i"; then
		# do whatever on "$i" here
		pid=${i::-1}
		progName=$(readlink $pid/exe) 
		dirName=$(readlink $pid/cwd)
		name=$(head -n 1 $pid/status | tail -1 | tr -d '\t')
		name=${name//"Name:"/}
		stat=$(head -n 3 $pid/status | tail -1 | tr -d '\t')
		stat=${stat//"State:"/}
		stat=${stat:0:1}
		#VmSize=$(sed '18q;d' $dir/status)
		pot=""
		VmSize=$(head -n 18 $pid/status | tail -1 | tr -d 'VmSize: \t kB')
		#~ VmSize=$(cat /proc/$pid/stat | cut -d" " -f23)
		#VmSize=VmSize*1024 #!!!!
		VmSize=$((VmSize*1024))
		#~ echo "$pid:$stat:$VmSize:$name"
		
		if [ $FLAG_IME == "true" ]; then
			if [ $FLAG_DELOVNA_POT == "true" ]; then
				if [ $FLAG_POT_PROGRAMA == "true" ]; then
					#vse zastavice
					
					if [[ "$name" == "$ukazno_ime" ]]; then
						if [[ ${pot_programa::1} == "." ]]; then
							pot=$currDir
							pot+=${pot_programa:1}
						else
							pot=$pot_programa
						fi
						if [ "$progName" == "$pot" ]; then
							if [[ ${delovna_pot::1} == "." ]]; then
								pot=$currDir
								pot+=${delovna_pot:1}
							else
								pot=$delovna_pot
							fi  
							if [[ "$dirName" -ef "$pot" ]]; then
								echo "$pid:$stat:$VmSize:$name"
							fi
						fi
					fi
					
				else # e false
					#c + d
					if [[ "$name" == "$ukazno_ime" ]]; then
						if [[ ${delovna_pot::1} == "." ]]; then
							pot=$currDir
							pot+=${delovna_pot:1}
						else
							pot=$delovna_pot
						fi
						if [[ "$dirName" -ef "$pot" ]]; then
							echo "$pid:$stat:$VmSize:$name"
						fi
					fi  
				fi
			else # d false
				if [ $FLAG_POT_PROGRAMA == "true" ]; then
					#c + e
					if [[ "$name" == "$ukazno_ime" ]]; then
						if [[ ${pot_programa::1} == "." ]]; then
							pot=$currDir
							pot+=${pot_programa:1}
						else
							pot=$pot_programa
						fi
						if [ "$progName" == "$pot" ]; then
							echo "$pid:$stat:$VmSize:$name"
						fi
					fi
				else # d, e false
					#c
					if [ "$name" == "$ukazno_ime" ]; then
						echo "$pid:$stat:$VmSize:$name"
					fi
				fi
			fi
		else #c false	
			if [ $FLAG_DELOVNA_POT == "true" ]; then
				if [ $FLAG_POT_PROGRAMA == "true" ]; then
					#d + e
					if [[ ${delovna_pot::1} == "." ]]; then
						pot=$currDir
						pot+=${delovna_pot:1}
					else
						pot=$delovna_pot
					fi  
					if [[ "$dirName" -ef "$pot" ]]; then
						if [[ ${pot_programa::1} == "." ]]; then
							pot=$currDir
							pot+=${pot_programa:1}
						else
							pot=$pot_programa
						fi
						if [ "$progName" == "$pot" ]; then
							echo "$pid:$stat:$VmSize:$name"
						fi
					fi
				else # c, e false
					#d
					if [[ ${delovna_pot::1} == "." ]]; then
						pot=$currDir
						pot+=${delovna_pot:1}
					else
						pot=$delovna_pot
					fi
					
					if [[ "$dirName" -ef "$pot" ]]; then
						echo "$pid:$stat:$VmSize:$name"
					fi
				fi
			else # c, d false	
				#e
				if [[ ${pot_programa::1} == "." ]]; then
					pot=$currDir
					pot+=${pot_programa:1}
				else
					pot=$pot_programa
				fi
				if [ "$progName" == "$pot" ]; then
					echo "$pid:$stat:$VmSize:$name"
				fi
			fi
		fi
	fi
done

#| tail -1
#> sed 's/Name\t;//' ''

#cd /proc
#cd /proc/[proc num]
#cat status

#pid: r6
#stat: r3
#VmSize: r18
#name: r1
#cd /proc/20/cwd; pwd -P -> prešteje vse procese
# podatki o procesih shrhanjeni v direktorijih z pid ptega procesa 

#get all pids
#preglej status vseh procesov 

# get all proces dirs
# ls -d [0-9]*/

exit 0;
