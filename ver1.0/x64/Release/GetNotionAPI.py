import requests
import json

# 노션 API 키 및 데이터베이스 ID 입력
NOTION_API_KEY = "secret_SQwIZLtr20cgMVvsB8nhbPJLavjQlNqS21RGNLmUctG"
DATABASE_ID = "f4d95bf8194349e1ad87770de8563e7c"

# API endpoint 설정
url = f"https://api.notion.com/v1/databases/{DATABASE_ID}/query"

# 헤더 설정
headers = {
    "Authorization": f"Bearer {NOTION_API_KEY}",
    "Notion-Version": "2021-05-13",  # API 버전
    "Content-Type": "application/json"
}

# API 요청
response = requests.post(url, headers=headers)
data = response.json()

# 결과 출력
print(json.dumps(data, indent=4))