
def exteuclid(a,b):
	"""The Extended Euclidean Algorithm. Finds GCD(a,b) and also computes t such that s*a + t*b = GCD(a,b)"""
	a0 = a
	b0 = b
	t0 = 0
	t = 1
	s0 = 1
	s = 0
	q = int(a0/b0)
	r = a0 - q*b0
	while r > 0:
		temp = t0 - q*t
		t0 = t
		t = temp
		temp = s0 - q*s
		s0 = s
		s = temp
		a0 = b0
		b0 = r
		q = int(a0/b0)
		r = a0 - q*b0
	r = b0
	return (r, s, t, s0, t0)

print("Enter a")
a = int(input())
print("Enter b")
b = int(input())
c = exteuclid(a,b)
print("Ext Euclid of a and b is (r, s, t, s0, t0): ", c)
