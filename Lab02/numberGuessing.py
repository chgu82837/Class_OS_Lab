#!/usr/bin/python

import sys,random

def numberGuessGame(target):
	upper = 10
	lower = 1
	input = 0
	while input != target:
		try:
			input = int(raw_input("Please input a number between "+str(upper)+" and "+str(lower)+":"))
		except Exception, e:
			input = 0
		if input >= target:
			upper = input - 1
		else:
			lower = input + 1
	print "Bingo!!"

print "Welcome to Number Guessing Game!"

if len(sys.argv) >= 2:
	target = int(sys.argv[1])
else:
	target = 0

if not target:
	try:
		target = int(raw_input("Please enter the target number ranging 1 to 10 (or press enter to randomly generate one):"))
	except Exception, e:
		target = 0

if (target > 10) or (target < 1):
	print "generating a number from 1 to 10..."
	target = random.randint(1,10)
numberGuessGame(target)
