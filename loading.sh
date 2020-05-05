#!/bin/bash

spinner=( 0oooooooo o0oooooooo oo0oooooo ooo0ooooo \
		oooo0oooo ooooo0ooo oooooo0oo ooooooo0o\
		oooooooo0)
copy(){
#	echo "============== COMPILING ==============="
	spin &
	pid=$!

	for i in `seq 1 1`
		do
			sleep 1
		done
	kill $pid
	echo ""
}
spin(){
	while [ 1 ]
#	do
#		for i in "${spinner[@]}"
			do
				echo -n "."
#				echo -ne "\r$i"
				sleep 0.025
			done
#	done
} 

copy
