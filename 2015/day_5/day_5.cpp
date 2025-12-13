#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

bool is_nice_one(std::string& str) {
    std::string vowels = "aeiou";

    int vowel_count = 0;
    bool double_check = false;
    bool good_pattern_check = true;
    for (size_t i = 0; i < str.length(); ++i) {
        if (i < str.length() - 1) {
            if (str[i] == str[i+1]) {
                double_check = true;
            }

            std::string s = str.substr(i, 2);
            if ((s == "ab")
                || (s == "cd")
                || (s == "pq")
                || (s == "xy"))
            {
                good_pattern_check = false;
            }
        }

        if (vowels.find(str[i]) != std::string::npos) {
            vowel_count++;
        }
    }

    bool vowel_check = (vowel_count >= 3) ? true : false;

    return vowel_check && double_check && good_pattern_check;
}

bool is_nice_two(std::string& str) {
    std::regex pattern(R"((..).*\1)");
    bool repeat_check = std::regex_search(str, pattern);
    bool middle_check = false;

    for (size_t i = 0; i < str.length(); ++i) {
        if (i < str.length() - 2) {
            if (str[i] == str[i+2]) {
                middle_check = true;
            }
        }
    }

    return repeat_check && middle_check;
}

int part_one(std::vector<std::string>& strs) {
    int result = 0;

    for (size_t i = 0; i < strs.size(); ++i) {
        if (is_nice_one(strs[i])) {
            result++;
        }
    }

    return result;
}

long long part_two(std::vector<std::string>& strs) {
    int result = 0;

    for (size_t i = 0; i < strs.size(); ++i) {
        if (is_nice_two(strs[i])) {
            result++;
        }
    }

    return result;
}

int main() {
    std::vector<std::string> strs;
    std::ifstream input_file("day_5.in");

    std::string line;
    while (std::getline(input_file, line)) {
        strs.push_back(line);
    }

    int part_one_sol = part_one(strs);
    long long part_two_sol = part_two(strs);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
