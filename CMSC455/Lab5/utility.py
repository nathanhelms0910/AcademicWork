import math

def gcd(a,b):
	"""Finds the greatest common divisor of two numbers"""
	if b == 0:
		return a
	return gcd(b, a%b)

def exteuclid(a,b):
	"""The Extended Euclidean Algorithm. Finds GCD(a,b) and also computes t such that s*a + t*b = GCD(a,b)"""
	a0 = a
	b0 = b
	t0 = 0
	t = 1
	q = int(a0/b0)
	r = a0 - q*b0
	while r > 0:
		temp = t0 - q*t
		t0 = t
		t = temp
		a0 = b0
		b0 = r
		q = int(a0/b0)
		r = a0 - q*b0
	r = b0
	return t

def quadratic(a, b, c):
	"""The quadratic formula: (-b +- sqrt(b^2 -4ac)) / 2a"""
	t1 = (-b + math.sqrt(b*b - 4*a*c)) / 2*a
	t2 = (-b - math.sqrt(b*b - 4*a*c)) / 2*a
	return (t1, t2)


