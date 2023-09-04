#ifndef TEST_H
#define TEST_H

#include "get_api.h"
#include "get_vocabulary.h"
#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <vector>
#include <string>

// 단어 테스트를 진행하는 클래스
class Test
{
	int _test_num; // 시험 볼 단어의 개수
	std::set<int> _selected_index; // 이미 선택된 단어의 인덱스
	std::map<std::string, std::string> _answers; // 사용자의 답변을 저장하는 벡터
	std::ofstream _result; // 결과를 기록할 파일 스트림


public:
	Test();
	~Test();
	void Run(GetAPI& _getApi, GetVocabulary& _getVocabulary); // 테스트 함수
	std::string GetUTF8Input(); // UTF-8로 인코딩된 입력을 받는 함수
};

#endif