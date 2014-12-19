#!/bin/bash

echo "Welcome to Number Guessing Game!"
printf "Please enter the target number ranging 1 to 10 (or press enter to randomly generate one):"
read target
if ! [ $target ]; then
	target=11
fi
if [[ "$target" -gt 10 ]] || [[ "$target" -lt 1 ]]; then
	echo "generating a number from 1 to 10..."
	target=$(expr $RANDOM \% 10 )
fi
upper=10
lower=1
while [[ "$input" -ne "$target" ]]; do
	echo "Please input a number between $upper and $lower:"
	read input
	if [[ "$input" -ge "$target" ]]; then
		upper=$(expr $input - 1)
	else
		lower=$(expr $input + 1)
	fi
done
echo "Bingo!!"
		
