#include <iostream>
#include <fstream>
#include <string>

int part_one(std::ifstream& input_file) {
    int tot_joltage = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        int max = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            for (size_t j = i + 1; j < line.size(); ++j) {
                int curr = (line[i] - '0') * 10 + (line [j] - '0');

                if (curr > max) {
                    max = curr;
                }
            }
        }

        tot_joltage += max;
    }

    return tot_joltage;
}

long long part_two(std::ifstream& input_file) {
    long long tot_joltage = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        std::string bank_joltage = "";
        int digits_remaining = 12;
        int i = 0;
        while (digits_remaining > 0) {
            long long max = 0;
            for (int j = i; j < line.size() - digits_remaining + 1; ++j) {
                if ((line[j] - '0') > max) {
                    max = line[j] - '0';
                    i = j + 1;
                }
            }
            bank_joltage += std::to_string(max);
            digits_remaining--;
        }
        tot_joltage += std::stoll(bank_joltage);
    }

    return tot_joltage;
}

int main() {
    std::ifstream input_file("day_3.in");

    int part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    long long part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
