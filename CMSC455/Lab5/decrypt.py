import math

def multiply(num, d, N):
	"""Compute num ^ d mod N"""
	if num >= N:
		print("Too large")
		return 0
	value = 1

	#This could be done much more efficiently with square-and-multiply, but brute force is easier to code
	for t in range(d):
		value = (value * num) % N
	return value

def decrypt(num, d, N):
	"""Given a number 'num', decrypt it and then convert it to a string"""
	m = multiply(num, d, N)

	#convert to a string
	a = chr(int(m/676)%26 + ord('a'))
	b = chr(int(m/26)%26 + ord('a'))
	c = chr(int(m)%26 + ord('a'))
	print(a, end="")
	print(b, end="")
	print(c, end="")

#Read a decryption key from the terminal, then use it to decrypt our message
print("Please type the decryption exponent:")
d = int(input())
print("Please type the decryption modulus:")
N = int(input())
print("Please type your message:")
m = int(input())
while(m > 0):
	decrypt(m, d, N)
	m = int(input())
