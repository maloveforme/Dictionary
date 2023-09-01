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

class GetVocabulary
{
	std::map<std::string, std::string> _word_pairs;
	std::ifstream _file;
	json _j;
	std::string _json_result;
	std::istringstream _ss;

public:
	GetVocabulary();
	~GetVocabulary();
	void SetVocabulary();
	bool IsError(json j);
	int GetVocabularyNum();
	std::string PrintVocabulary(int index);
	std::string PrintVocabulary(std::string input);
};

#endif // !GET_VOCABULARY_H
