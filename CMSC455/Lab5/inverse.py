import utility

print("Please enter b: ")
b = int(input())
b = utility.exteuclid(18648, b) % 18648
print(b)
