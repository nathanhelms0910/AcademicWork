Nathan Helms
CMSC242: Project 1

Overview: This program takes in a tested program as well as a directory of test cases. These tests cases must contain integers separated by a newline (see one of the provided test cases for an example). 

The program will open the provided test case directory, and parse through the files within and run each test case one by one.

First, the program will return whether the current test case has a matching .expect file somewhere else in the directory, and printing out whether it does or doesn't

Secondly, the program will automatically run the test case through the test program, in which the tested program takes in each integer and divides them by 2 for the output.



To run the program, first it is recommended to compile it by using:

gcc project1.c



Once compiled, run the test program by typing

./a.out tested <your test case directory here>


replace <your test case directory here> accordingly



for example, to run with my set of test cases, type

./a.out tested tests/

The program will then begin to parse through the test cases provided to it, and print results as it processes out to the user

Afterwards, the program will enter a similar state as the tested program, but for taking user input. You can enter any positive integer you wish, and the program will divide it by 2. Enter a 0 here as stated to exit gracefully.Enter a negative number to exit with an Error.
