#include "get_vocabulary.h"

GetVocabulary::GetVocabulary() : _file("output.txt", std::ios::in)
{
	// GetNotionAPI.py�� ������� output.txt ������ ���� ������ ��
	if (!_file.is_open())
	{
		std::cerr << "output.txt ������ ���� ���߽��ϴ�.\n";
		return;
	}
}

GetVocabulary::~GetVocabulary()
{
    _file.close();
}

void GetVocabulary::SetVocabulary()
{
    // _file�� ������ _json_result�� �Ҵ�
    // _json_result�� ���ڿ� ��Ʈ�� ��ü _ss�� �Ҵ� 
    _json_result.assign(std::istreambuf_iterator<char>(_file),
        std::istreambuf_iterator<char>());
    _ss.str(_json_result);

    _ss >> _j;

    if (IsError(_j))
    {
        for (const auto& result : _j["results"])
        {
            std::string word = result["properties"]["Vocabulary"]["rich_text"][0]["plain_text"];
            std::string meaning = result["properties"]["meaning"]["rich_text"][0]["plain_text"];
            _word_pairs[word] = meaning;
        }

        if (_word_pairs.empty())
        {
            std::cerr << "No word pairs extracted.\n";
            return;
        }
    }
}

bool GetVocabulary::IsError(json j)
{
    // JSON ������ �Ľ��ϸ� ���� üũ

    if (!j.contains("results"))
    {
        std::cerr << "JSON dosen't contain results.\n";
        return false;
    }

	for (const auto& result : j["results"])
	{
        if (!result.contains("properties"))
        {
            std::cerr << "Missing 'properties' key.\n";
            return false;
        }

        if (!result["properties"].contains("Vocabulary"))
        {
            std::cerr << "Missing 'Vocabulary' key.\n";
            return false;
        }

        if (!result["properties"]["Vocabulary"].contains("rich_text"))
        {
            std::cerr << "Missing 'rich_text' under 'Vocabulary'.\n";
            return false;
        }

        if (result["properties"]["Vocabulary"]["rich_text"].empty())
        {
            std::cerr << "'rich_text' under 'Vocabulary' is empty.\n";
            return false;
        }

        if (!result["properties"].contains("meaning"))
        {
            std::cerr << "Missing 'meaning' key.\n";
            return false;
        }

        if (!result["properties"]["meaning"].contains("rich_text"))
        {
            std::cerr << "Missing 'rich_text' under 'meaning'.\n";
            return false;
        }

        if (result["properties"]["meaning"]["rich_text"].empty())
        {
            std::cerr << "'rich_text' under 'meaning' is empty.\n";
            return false;
        }
	}

    return true;
}

int GetVocabulary::GetVocabularyNum()
{
    // ���� �ܾ �� �� ����ִ��� ��ȯ
    return _word_pairs.size();
}

std::string GetVocabulary::PrintVocabulary(int index)
{
    // ���� �ε����ؼ� key�� ��ȯ
    auto it = std::next(_word_pairs.begin(), index);
    return it->first;
}

std::string GetVocabulary::PrintVocabulary(std::string input)
{
    // ���� Ű�� ������ value�� ��ȯ
    return _word_pairs[input];
}