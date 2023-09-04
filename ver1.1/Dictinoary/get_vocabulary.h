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

// �ܾ� DB�� �����ϰ� �ܾ �����ϴ� Ŭ����
class GetVocabulary
{
	std::map<std::string, std::string> _word_pairs; // �ܾ�� �� �ǹ̸� �����ϴ� ����
	std::ifstream _file; // DB ���� ��Ʈ��
	json _j; // json ��ü
	std::string _json_result; // json ��� ���ڿ�
	std::istringstream _ss; // ���ڿ� ��Ʈ��

public:
	GetVocabulary();
	~GetVocabulary();
	void SetVocabulary(); // DB�� �����ϴ� �Լ�
	bool IsError(json j); // json ���� ���� �˻� �Լ�
	int GetVocabularyNum(); // ���� ����� �ܾ��� ������ ��ȯ�ϴ� �Լ�
	std::string PrintVocabulary(int index); // �־��� �ε����� �ش��ϴ� �ܾ �����ϴ� �Լ�
	std::string PrintVocabulary(std::string input); // �־��� �ܾ��� �ǹ̸� �����ϴ� �Լ�
};

#endif // !GET_VOCABULARY_H
