#include "get_api.h"

GetAPI::GetAPI()
{
	// SetConsoleCP 함수를 이용하여 콘솔 인코딩을 UTF-8로 설정
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	// GetNotionAPI.py 스크립트를 실행하여 노션 API 호출
	system("python GetNotionAPI.py");
	system("cls");
}