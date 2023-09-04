#ifndef GET_VOCABULARY_H
#define GET_VOCABULARY_H

#include "json.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

// 단어 DB에 접근하고 단어를 추출하는 클래스
class GetVocabulary
{
	std::map<std::string, std::string> _word_pairs; // 단어와 그 의미를 저장하는 벡터
	std::ifstream _file; // DB 파일 스트림
	json _j; // json 객체
	std::string _json_result; // json 결과 문자열
	std::istringstream _ss; // 문자열 스트림

public:
	GetVocabulary();
	~GetVocabulary();
	void SetVocabulary(); // DB를 설정하는 함수
	bool IsError(json j); // json 파일 오류 검사 함수
	int GetVocabularyNum(); // 현재 저장된 단어의 개수를 반환하는 함수
	std::string PrintVocabulary(int index); // 주어진 인덱스에 해당하는 단어를 추출하는 함수
	std::string PrintVocabulary(std::string input); // 주어진 단어의 의미를 추출하는 함수
};

#endif // !GET_VOCABULARY_H
