from utility import *

def f(x):
	return x*x + 1

def pollard_rho(n, x1):
	x = x1
	x_p = f(x) % n
	p = gcd(x-x_p, n)

	while(p == 1):
		#in the i-th iteration, x = x_i and x_p = x_2i
		x = f(x) % n
		x_p = f(x_p) % n
		x_p = f(x_p) % n
		p = gcd(x - x_p, n)
	
	if(p == n):
		return "failure"
	else:
		return p

print("Enter the exponent: ")
e = int(input())
print("Enter the modulus: ")
N = int(input())

p = pollard_rho(N, 1)
q = N / p
phin = (p-1) * (q-1)
d = exteuclid(phin, e)
if d > 0 and d < N:
	print("The decryption exponent is: ", d)
