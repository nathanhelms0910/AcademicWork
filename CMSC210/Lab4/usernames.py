#!/usr/bin/python3

print("<!DOCTYPE html>")
print("<html lang=en>")
print("<head>")
print("<title>Lab4</title>")
print("<meta charset=utf-8>")
print("</head>")
print("<body>")

bob = {}
bob['ssn'] = 123
bob['username'] = "bob"
bob['name'] = "Bob"
bob['salary'] = 54000.10

sam = {}
sam['ssn'] = 456
sam['username'] = "sam"
sam['name'] = "Sam"
sam['salary'] = 43000.45

henry = {}
henry['ssn'] = 789
henry['username'] = "henry"
henry['name'] = "Henry"
henry['salary'] = 48500.21

accounts = []
accounts += [bob]
accounts += [sam]
accounts += [henry]

for a in accounts:
	print(a["salary"])

print("<div>")
print("<ul>")
for b in accounts:
	print("<li>" + b["username"] + ": " + b["name"] + "</li>")

print("</ul>")
print("</div>")
print("</body>")
print("</html>")
