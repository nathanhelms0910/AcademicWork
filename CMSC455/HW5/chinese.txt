#Code by Nathan Helms for CMSC455 HW5 Problem 5.6. Attribute any usage to me, thank you
  
print("Are you solving for M and y (1), or doing the final calc (2)?")
choice = int(input())
if(choice == 1):
	print("Enter first modulo")
	m1 = int(input())
	print("Enter second modulo")
	m2 = int(input())
	print("Enter mod for y calculation")
	modu = int(input())
	mult = m1*m2
	y = mult % modu
	print("M: ", mult)
	print("y: ", y)
elif(choice == 2):
	print("For how many equations?")
	num = int(input())
	mods = 0
	final_mod = 1
	while(mods < num):
	  print("Enter modulo " , mods+1)
	  entry = int(input())
	  final_mod = final_mod * entry
	  mods = mods + 1
	i = 0
	total = 0
	mod = 1
	while(i < num):
	  print("Enter a: ")
	  a = int(input())
	  print("Enter M: ")
	  M = int(input())
	  print("Enter y: ")
	  y = int(input())
	  prod = a*M*y
	  total = total + prod
	  i = i + 1
	ans = total % final_mod
	print("Final calc: ", ans)
else:
	pass 

