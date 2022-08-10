Nathan Helms
CMSC 242 - Lab 1 - Word Stats
Dr Blaheta

Overview:
This program will take in a max of 5 words entered by the user per cycle of the program, 
and return the alphabetically first word of the batch entered, 
as well as the integer length of the longest word of the batch.

If the user enters a word longer than 10 characters long OR enters a word with any non-lowercase letters,
the program will throw "Error" and terminate

If the user enters in all uppercase the word "DONE", the program will cease taking in more words,
and return the alphabetical first word and the integer length of the longest word in the current batch provided.
The program will then terminate following printing this information.


To run this program:

type in the command prompt : 

gcc main.c alphaCheck.c maxLength.c lowercaseCheck.c 

to compile all files, and generate the a.out file


then type:

./a.out

the program will then start, and await word entries from the user


Test Cases:

Test Case 1:
nathan
helms
cmsc
lab
one
First: cmsc
Longest: 6
cmsc
DONE
First: cmsc
Longest: 4


Test Case 2:
nathan
helms
CMSC
Error


Test Case 3:
nathan
helms
cmsclabonewoohoo
Error



