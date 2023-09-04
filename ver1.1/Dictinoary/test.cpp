#include "test.h"

Test::Test()
{
	_test_num = 0;
	// result.txt 파일 생성
	_result.open("result.txt", std::ios::out | std::ios::binary);
}

Test::~Test()
{
	// .txt 파일 수정을 끝마치고 파일을 엶
	_result.close();
	system("notepad result.txt");
}

void Test::Run(GetAPI& _getApi, GetVocabulary& _getVocabulary)
{
	std::cout << u8"영어 단어 시험 프로그램 made by maloveforme\n";
	std::cout << u8"시험 볼 단어의 개수를 입력하세요: ";
	std::cin >> _test_num;
	std::cin.ignore();

	// 시험 볼 단어의 개수가 데이터베이스의 단어 개수보다 모자랄 때
	if (_test_num > _getVocabulary.GetVocabularyNum())
	{
		std::cerr << u8"데이터베이스의 단어의 개수가 모자랍니다.\n";
		return;
	}

	std::cout << u8"영어 단어가 나오면 답을 입력하세요.\n";

	// 난수 생성
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	int count = 0;

	while (count != _test_num)
	{
		std::uniform_int_distribution<int> distribution(0, _getVocabulary.GetVocabularyNum() - 1);
		int random_index = distribution(generator);
		std::string answer;

		// 이미 사용된 번호를 생략하기 위한 반복문
		while (_selected_index.find(random_index) != _selected_index.end())
			random_index = distribution(generator);
		_selected_index.insert(random_index);

		// UTF-8 인코딩 후 결과 벡터에 저장
		std::cout << _getVocabulary.PrintVocabulary(random_index) << ": ";
		answer = GetUTF8Input();
		_answers[_getVocabulary.PrintVocabulary(random_index)] = answer;

		count++;
	}

	if (!_result.is_open())
	{
		std::cerr << u8"result.txt 파일을 열지 못했습니다.\n";
		return;
	}
	
	// UTF-8 인코딩을 위한 BOM
	unsigned char utf8BOM[] = { 0xEF, 0xBB, 0xBF };
	_result.write((char*)utf8BOM, sizeof(utf8BOM));

	_result << u8"문제\t\t\t입력\t\t\t정답\n";
	for (const auto& pairs : _answers)
		_result << pairs.first << "\t\t\t" << pairs.second << "\t\t\t" << _getVocabulary.PrintVocabulary(pairs.first) << "\n";
}

std::string Test::GetUTF8Input()
{
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	WCHAR buffer[1024];
	DWORD numRead;

	ReadConsoleW(hConsole, buffer, 1024, &numRead, NULL);
	buffer[numRead - 1] = L'\0';

	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, NULL, 0, NULL, NULL);
	std::string utf8String(sizeNeeded - 1, 0);
	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &utf8String[0], sizeNeeded, NULL, NULL);

	while (!utf8String.empty() && (utf8String.back() == '\n' || utf8String.back() == '\r')) {
		utf8String.pop_back();
	}

	return utf8String;
}