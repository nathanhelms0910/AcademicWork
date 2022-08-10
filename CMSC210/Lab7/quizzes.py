import requests
import json
import datetime

token = "Bearer " + input()
base_url = 'https://canvas.longwood.edu/api/v1'
heads = {'Authorization' : token}
response = requests.get(base_url + '/courses/1300953/quizzes?per_page=50', headers=heads)
doc = response.json()

quizzes = {}
for quiz in doc:
	title = quiz["title"]
	if "due_at" in quiz and quiz["due_at"] != None:
		due = datetime.datetime.strptime(quiz["due_at"], "%Y-%m-%dT%H:%M:%SZ")
		if "published" in quiz and quiz["published"] == True:
			quizzes[due] = title

for t in sorted(quizzes):
	print(t, quizzes[t])
