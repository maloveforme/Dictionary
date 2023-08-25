#include "main.h"

struct res
{
    std::string problem, input, answer;
};

int main()
{
    std::cout << "영어 단어 시험지 made by maloveforme\n";
    std::cout << "영어 단어가 나오면 답을 입력하세요\n";

    system("python GetNotionAPI.py > output.txt");
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::vector<std::pair<std::string, std::string>> word_pairs;
    std::vector<std::string> answers;
    std::vector<int> word_index;
    std::ifstream file("output.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening output.txt\n";
        return 1;
    }

    json j;

    try
    {
        file >> j;

        if (!j.contains("results"))
        {
            std::cerr << "JSON does not contain 'results'.\n";
            return 1;
        }

        for (const auto& result : j["results"])
        {
            if (!result.contains("properties"))
            {
                std::cerr << "Missing 'properties' key.\n";
                continue;
            }

            if (!result["properties"].contains("Vocabulary"))
            {
                std::cerr << "Missing 'Vocabulary' key.\n";
                continue;
            }

            if (!result["properties"]["Vocabulary"].contains("rich_text"))
            {
                std::cerr << "Missing 'rich_text' under 'Vocabulary'.\n";
                continue;
            }

            if (result["properties"]["Vocabulary"]["rich_text"].empty())
            {
                std::cerr << "'rich_text' under 'Vocabulary' is empty.\n";
                continue;
            }

            if (!result["properties"].contains("meaning"))
            {
                std::cerr << "Missing 'meaning' key.\n";
                continue;
            }

            if (!result["properties"]["meaning"].contains("rich_text"))
            {
                std::cerr << "Missing 'rich_text' under 'meaning'.\n";
                continue;
            }

            if (result["properties"]["meaning"]["rich_text"].empty())
            {
                std::cerr << "'rich_text' under 'meaning' is empty.\n";
                continue;
            }

            std::string word = result["properties"]["Vocabulary"]["rich_text"][0]["plain_text"];
            std::string meaning = result["properties"]["meaning"]["rich_text"][0]["plain_text"];
            word_pairs.push_back({ word, meaning.c_str()});
        }

        if (word_pairs.empty())
        {
            std::cerr << "No word pairs extracted.\n";
            return 1;
        }
    }

    catch (const std::exception& e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return 1;
    }

    int count = 0;
    while (count != 10)
    {
        std::uniform_int_distribution<int> distribution(0, word_pairs.size() - 1);
        int random_index = distribution(generator);
        std::string answer;

        std::cout << word_pairs[random_index].first << ": ";
        std::getline(std::cin, answer);
        answers.push_back(answer);
        word_index.push_back(random_index);
        count++;
    }
    std::ofstream testFile("testOutput.txt");

    for (const auto& pair : word_pairs) 
        testFile << pair.first << ": " << pair.second << "\n";
    
    testFile.close();

    std::ofstream result_file("result.txt");

    result_file << "번호\t문제\t입력\t정답\n";
    for(int i = 0; i < 10; ++i)
        result_file << i << "\t" << word_pairs[word_index[i]].first << "\t" << answers[i] << "\t" << word_pairs[word_index[i]].second << "\n";

    result_file.close();
    file.close();
    return 0;
}
