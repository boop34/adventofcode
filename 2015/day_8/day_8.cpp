#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int part_one(std::ifstream& input_file) {
    int result = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        int total_chars = line.length();
        int memo_chars = total_chars - 2;
        size_t idx = 1;
        while (idx < line.length() - 1) {
            if ((line[idx] == '\\') && (line[idx-1] == '\\')) {
                idx++;
                memo_chars--;
            } else if ((line[idx] == '\"') && (line[idx-1] == '\\')) {
                idx++;
                memo_chars--;
            } else if ((line[idx] == 'x') && (line[idx-1] == '\\')) {
                memo_chars -= 3;
                idx += 2;
            }
            idx++;
        }

        result += (total_chars - memo_chars);
    }

    return result;
}

int part_two(std::ifstream& input_file) {
    int result = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        int total_chars = line.length();
        int enc_chars = total_chars + 4;
        size_t idx = 1;
        while (idx < line.length() - 1) {
            if ((line[idx] == '\\') && (line[idx-1] == '\\')) {
                idx++;
                enc_chars += 2;
            } else if ((line[idx] == '\"') && (line[idx-1] == '\\')) {
                idx++;
                enc_chars += 2;
            } else if ((line[idx] == 'x') && (line[idx-1] == '\\')) {
                enc_chars += 1;
                idx += 2;
            }
            idx++;
        }

        result += (enc_chars - total_chars);
    }

    return result;
}

int main() {
    std::ifstream input_file("day_8.in");

    int part_one_sol = part_one(input_file);

    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    int part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
