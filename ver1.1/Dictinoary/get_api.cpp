#include "get_api.h"

GetAPI::GetAPI()
{
	// SetConsoleCP �Լ��� �̿��Ͽ� �ܼ� ���ڵ��� UTF-8�� ����
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	// GetNotionAPI.py ��ũ��Ʈ�� �����Ͽ� ��� API ȣ��
	system("python GetNotionAPI.py");
	system("cls");
}