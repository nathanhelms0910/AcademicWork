import requests
import json
import markovify

base_url = "https://canvas.longwood.edu/api/v1"
print("Please enter your access token:")
token = "Bearer " + input()
response = requests.get("http://marmorstein.org/~robert/Spring2021/cs210/pg697.txt")

model = markovify.Text(response.text)
message = ""

for x in range(0, 30):
	message += model.make_sentence() + " "

heads = {"Authorization": token}
post_data = {"recipients": 4012626, "subject": 'student3', "body": message}

response = requests.post(base_url + '/conversations', headers=heads, data=post_data)

doc = response.json()
print(json.dumps(doc))
