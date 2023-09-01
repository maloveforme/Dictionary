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

class Test
{
	int _test_num;
	std::set<int> _selected_index;
	std::map<std::string, std::string> _answers;
	std::ofstream _result;


public:
	Test();
	~Test();
	void Run(GetAPI& _getApi, GetVocabulary& _getVocabulary);
	std::string GetUTF8Input();
};

#endif