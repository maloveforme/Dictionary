import requests
import json
import os
from dotenv import load_dotenv

# 주어진 API 키와 DB ID가 유효한지 확인하는 함수
def check_keys_valid(api_key, db_id):
    check_url = f"https://api.notion.com/v1/databases/{db_id}"
    headers = {
        "Authorization": f"Bearer {api_key}",
        "Notion-Version": "2021-05-13"
    }
    response = requests.get(check_url, headers=headers)
    
    # 응답의 상태 코드와 내용을 출력
    print(f"Status code: {response.status_code}")
    print(f"Response: {response.text}")
    
    return response.status_code == 200

# .env 파일이 존재하지 않으면 API 키와 DB ID를 입력받아 생성
if not os.path.exists('.env'):
    print("노션 API키와 데이터베이스 ID가 존재하지 않습니다.\n")
    with open('.env', 'w') as f:
        notion_key = input("NOTION API KEY를 입력하세요: ")
        database_id = input("DATABASE ID를 입력하세요: ")
        
        f.write(f'NOTION_API_KEY="{notion_key}"\n')
        f.write(f'DATABASE_ID="{database_id}"\n')

# .env 파일 로드
load_dotenv(dotenv_path="./.env")

NOTION_API_KEY = os.getenv("NOTION_API_KEY")
DATABASE_ID = os.getenv("DATABASE_ID")

# 유효하지 않은 API 키나 DB ID를 수정할 수 있는 반복문
while not check_keys_valid(NOTION_API_KEY, DATABASE_ID):
    print("해당하는 정보가 존재하지 않습니다. 수정을 원하십니까?(y/n)")
    choice = input().lower()
    if choice == 'y':
        with open('.env', 'w') as f:
            NOTION_API_KEY = input("NOTION API KEY를 다시 입력하세요: ")
            DATABASE_ID = input("DATABASE ID를 다시 입력하세요: ")
            
            f.write(f'NOTION_API_KEY="{NOTION_API_KEY}"\n')
            f.write(f'DATABASE_ID="{DATABASE_ID}"\n')
    else:
        print("잘못된 정보로 계속 진행합니다.")
        break

# Notion API를 호출하여 데이터를 받아오는 부분
url = f"https://api.notion.com/v1/databases/{DATABASE_ID}/query"
headers = {
    "Authorization": f"Bearer {NOTION_API_KEY}",
    "Notion-Version": "2021-05-13",  
    "Content-Type": "application/json"
}
response = requests.post(url, headers=headers)
data = response.json()

# 받아온 데이터를 'output.txt'에 저장
with open('output.txt', 'w', encoding='utf-8') as outfile:
    json.dump(data, outfile, ensure_ascii=False, indent=4)