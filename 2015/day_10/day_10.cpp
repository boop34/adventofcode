#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string soln(std::string& str) {
    std::string result = "";

    char curr = str[0];
    int count = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != curr)  {
            result += std::to_string(count) + curr;
            count = 0;
            curr = str[i];
        }

        if (str[i] == curr) {
            count += 1;
        }
    }

    result += std::to_string(count) + curr;

    return result;
}

long long part_one(std::string& seq) {
    std::string result = seq;
    for (size_t i = 0; i < 40; ++i) {
        result = soln(result);
    }

    return result.length();
}

long long part_two(std::string& seq) {
    std::string result = seq;
    for (size_t i = 0; i < 50; ++i) {
        result = soln(result);
    }

    return result.length();
}

int main() {
    std::ifstream input_file("day_10.in");

    std::string seq;
    std::getline(input_file, seq);

    long long part_one_sol = part_one(seq);
    long long part_two_sol = part_two(seq);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
