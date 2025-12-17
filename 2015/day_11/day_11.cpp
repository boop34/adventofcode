#include <unordered_set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void increment(std::string& str) {
    for (int i = str.length() - 1; i >= 0; --i) {
        if (str[i] == 'z') {
            str[i] = 'a';
        } else {
            str[i] += 1;
            return;
        }
    }
}

bool is_valid(std::string& str) {
    std::unordered_set<std::string> repeat_pattern;
    bool straight_rule = false;
    bool iol_rule = true;
    int repeat_ignore = -1;

    for (size_t i = 0; i < str.length() - 1; ++i) {
        if (str[i] == 'i' || str[i] == 'o' || str[i] == 'l') {
            iol_rule = false;
            break;
        }

        if ((str[i+2] - str[i+1] == 1)
                && (str[i+1] - str[i] == 1)
                && (i < str.length() - 3))
        {
            straight_rule = true;
        }

        if ((str[i] == str[i+1]) && (repeat_ignore != i)) {
            repeat_pattern.insert(str.substr(i, 2));
            repeat_ignore = i + 1;
        }
    }

    bool repeat_rule = repeat_pattern.size() > 1;

    return straight_rule && iol_rule && repeat_rule;
}

std::string part_one(std::string password) {
    std::string result = password;

    while (true) {
        if (is_valid(result)) {
            break;
        }
        increment(result);
    }

    return result;
}

std::string part_two(std::string password) {
    std::string result = password;

    increment(result);
    while (true) {
        if (is_valid(result)) {
            break;
        }
        increment(result);
    }

    return result;
}

int main() {
    std::ifstream input_file("day_11.in");

    std::string password;
    std::getline(input_file, password);

    std::string part_one_sol = part_one(password);
    std::string part_two_sol = part_two(part_one_sol);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
