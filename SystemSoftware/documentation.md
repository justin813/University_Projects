#Project 2

This program is to demonstrate knowledge and practice with the SIC/XE language.

Goal:	To reverse a string

Implementation:	

	I load a string through many words. 
	Then I use a loop to go through each word and place it in a 11 word variable
	in reverse. The oringal string starts at 130 to 151. The reversed strig starts
	at 151 to 16f. In my case the string is 11 words long. And the List of  is 
	defined from the word NUMS which has all the remaing words below it and then
	displays the string in reverse.

Modifications for increase/decreasing string size and words to reverse: 
	x = number of words. NUMS = Words
	
	1. modify the word MEM to 3*(x-1).
	2. In addition modify variable INV to (x-1)
	3. Modify NUMS to x items.
	
	E.g. I want to reverse a 12 word string.
	x = 12;
	1. MEM WORD 33
	2. INV RESW 11

	3. NUMS WORD 17
		WORD 18
		WORD 12
		WORD 13
		WORD 14
		WORD 15
		WORD 16
		WORD 17
		WORD 18
		WORD 19
		WORD 20
		WORD 21
Nagavarun Kanaparthy
10/13/2015
