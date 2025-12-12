#include <iostream>
#include <fstream>
#include <string>
#include <vector>

long long part_one(std::ifstream& input_file) {
    long long result = 0ll;

    std::string line;
    while (std::getline(input_file, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '(') {
                result++;
            } else if (line[i] == ')') {
                result--;
            }
        }
    }

    return result;
}

size_t part_two(std::ifstream& input_file) {
    size_t result = 0ll;

    std::string line;
    while (std::getline(input_file, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '(') {
                result++;
            } else if (line[i] == ')') {
                result--;
            }

            if (result == -1) {
                return i + 1;
            }
        }
    }

    return result;
}

int main() {
    std::ifstream input_file("day_1.in");

    long long part_one_sol = part_one(input_file);

    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    size_t part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
