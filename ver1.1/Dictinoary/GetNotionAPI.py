import requests
import json
import os
from dotenv import load_dotenv

if not os.path.exists('.env'):
    print("노션 API키와 데이터베이스 ID가 존재하지 않습니다.\n")
    with open('.env', 'w') as f:
        notion_key = input("NOTION API KEY를 입력하세요: ")
        database_id = input("DATABASE ID를 입력하세요: ")
        
        f.write(f'NOTION_API_KEY="{notion_key}"\n')
        f.write(f'DATABASE_ID="{database_id}"\n')

load_dotenv(dotenv_path="./.env")

NOTION_API_KEY = os.getenv("NOTION_API_KEY")
DATABASE_ID = os.getenv("DATABASE_ID")

url = f"https://api.notion.com/v1/databases/{DATABASE_ID}/query"

headers = {
    "Authorization": f"Bearer {NOTION_API_KEY}",
    "Notion-Version": "2021-05-13",  
    "Content-Type": "application/json"
}

# API 요청
response = requests.post(url, headers=headers)
data = response.json()

with open('output.txt', 'w', encoding='utf-8') as outfile:
    json.dump(data, outfile, ensure_ascii=False, indent=4)