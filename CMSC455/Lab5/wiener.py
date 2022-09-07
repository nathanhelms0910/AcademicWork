import math
from utility import *

def frac(a, b):
	"""Converts the fraction b/a into a continued fraction of the form a0 / (a1 + (1 / a2 + ... )). Returns the terms a0, a1, and so forth."""
	nums = []
	if b == 0:
		return nums

	if a > b:
		val = int(a/b)
		nums += [val]
		rem = a - (val*b)
		nums += frac(b, rem)
	return nums

def convergents(terms):
	"""Finds the convergents of a continued fraction. This is very similar to Extended Euclid"""
	prevnumer = 1
	prevdenom = 0

	numer = 0
	denom = 1

	outputs = []
	for term in terms:
		# a_i = n_i / d_i where n_i = term * n_(i-1) + n_(i-2) and d_i = term*d_(i-1) + d_(i-2)
		
		tmp = numer
		numer = term*numer + prevnumer
		prevnumer = tmp

		tmp = denom
		denom = term*denom + prevdenom
		prevdenom = tmp

		outputs += [(numer, denom)]
	return outputs

def factor(N, e):
	terms = frac(N, e)
	C = convergents(terms)

	for c in C:
		#Phi(n) = (e*d - 1)/k where:
		# e is the public key, d is the private key and k/d is a candidate convergent of the continued fraction
		
		t = (e * c[1] - 1) / c[0]

		#If it's an integer, we found a solution
		if(t == int(t)):
			#Use quadratic formula to find the roots of x^2 - (N - phin + 1)*x + N
			a = 1
			b = -(N - int(t) + 1)
			c = N
			(p,q) = quadratic(a, b, c)
			phin = (p-1)*(q-1)
			d = exteuclid(phin, e)
			if d > 0 and d < N:
				print(d)
				print("The decryption exponent is: ", d)
				return
	return "Failure"


print("Enter exponent: ")
e = int(input())
print("Enter modulus: ")
N = int(input())
factor(N,e)
