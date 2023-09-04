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

// �ܾ� �׽�Ʈ�� �����ϴ� Ŭ����
class Test
{
	int _test_num; // ���� �� �ܾ��� ����
	std::set<int> _selected_index; // �̹� ���õ� �ܾ��� �ε���
	std::map<std::string, std::string> _answers; // ������� �亯�� �����ϴ� ����
	std::ofstream _result; // ����� ����� ���� ��Ʈ��


public:
	Test();
	~Test();
	void Run(GetAPI& _getApi, GetVocabulary& _getVocabulary); // �׽�Ʈ �Լ�
	std::string GetUTF8Input(); // UTF-8�� ���ڵ��� �Է��� �޴� �Լ�
};

#endif