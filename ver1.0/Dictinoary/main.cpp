#include "main.h"

std::string getUtf8Input()
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

int main()
{/*
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    system("chcp 65001 > nul");*/
    system("python GetNotionAPI.py");
    system("cls");

    int test_num;
    std::cout << u8"영어 단어 시험지 made by maloveforme\n\n";
    std::cout << u8"시험 치고자 하는 단어 개수를 입력하세요: ";
    std::cin >> test_num;
    std::cout << "\n";
    std::cin.ignore();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::vector<std::pair<std::string, std::string>> word_pairs;
    std::vector<std::string> answers;
    std::vector<int> word_index;
    std::ifstream file("output.txt", std::ios::in);

    if (!file.is_open())
    {
        std::cerr << "Error opening output.txt\n";
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::istringstream ss(content);

    json j;

    try
    {
        ss >> j;

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
            word_pairs.push_back({ word, meaning.c_str() });
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

    if (word_pairs.size() < test_num)
    {
        std::cout << u8"문제가 부족합니다\n";
        return 0;
    }

    std::cout << u8"영어 단어가 나오면 답을 입력하세요\n";
    std::set<int> selected_index;

    int count = 0;
    while (count != test_num)
    {
        std::uniform_int_distribution<int> distribution(0, word_pairs.size() - 1);
        int random_index = distribution(generator);
        std::string answer;

        while (selected_index.find(random_index) != selected_index.end())
            random_index = distribution(generator);
        selected_index.insert(random_index);

        std::cout << word_pairs[random_index].first << ": ";
        answer = getUtf8Input();
        answers.push_back(answer);
        word_index.push_back(random_index);

        count++;
    }

    std::ofstream result("result.txt", std::ios::out | std::ios::binary);
    unsigned char utf8BOM[] = { 0xEF, 0xBB, 0xBF };
    result.write((char*)utf8BOM, sizeof(utf8BOM));

    result << u8"번호\t문제\t\t\t입력\t\t\t정답\n";
    for (int i = 0; i < test_num; ++i)
        result << i << "\t" << word_pairs[word_index[i]].first << "\t\t\t" << answers[i] << "\t\t\t" << word_pairs[word_index[i]].second << "\n";

    result.close();
    file.close();

    system("notepad result.txt");
    return 0;
}