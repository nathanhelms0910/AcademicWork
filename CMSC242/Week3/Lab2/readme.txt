Nathan Helms
CMSC242 - Lab 2
Dr Blaheta

Overview: This program will take in a command from the user, push, pop, or end. push when appended with an integer in the command line, will add a node to a linked list of that integer.
The user may push multiple nodes back to back if they so choose to do so. pop when ran, will pop off the header node of the linked list from the list and print it out in the console. end will print
out the remaining entries to the linked list that were not popped off and then terminate the program.


How to run this program:

Type the following command to compile the program

gcc main.c

After compiling, type the following command to start the program

./a.out


Example usage of commands

push <integer>

push 8

Program Response: ok

pop

Program Response: 8

end

push 8
push 6
push 4
pop
end

Program Response:
6
8

Test cases for users to try:

push 8
ok
push 10
ok
push 11
ok
push 15
ok
pop
15
pop
11
end
10
8

-----------------------------

push 4
ok
pop
4
end


-----------------------------

push 10
ok
push 11
ok
push 20
ok
push 3
ok
push 6
ok
end
6
3
20
11
10

