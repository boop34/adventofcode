#include <iostream>
#include <fstream>
#include <string>

int part_one(std::ifstream& input_file) {
    int pswd = 0;
    int current_num = 50;

    std::string line;
    while (std::getline(input_file, line)) {
        int parsed_num = std::stoi(line.substr(1));
        switch (line[0]) {
            case 'L':
                current_num = (current_num - parsed_num) % 100;
                break;
            case 'R':
                current_num = (current_num + parsed_num) % 100;
                break;
        }

        if (current_num == 0) {
            pswd++;
        }
    }

    return pswd;
}

int part_two(std::ifstream& input_file) {
    int pswd = 0;
    int current_num = 50;

    std::string line;
    while (std::getline(input_file, line)) {
        int parsed_num = std::stoi(line.substr(1));
        switch (line[0]) {
            case 'L':
                current_num -= parsed_num;
                if (current_num <= 0) {
                    if ((current_num + parsed_num) == 0) {
                        pswd += std::abs(current_num / 100);
                    } else {
                        pswd += std::abs(current_num / 100) + 1;
                    }
                }
                break;
            case 'R':
                current_num += parsed_num;
                pswd += (current_num / 100);
                break;
        }
        current_num = ((current_num % 100) + 100) % 100;
    }

    return pswd;
}

int main() {
    std::ifstream input_file("day_1.in");

    int part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    int part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;
    return 0;
}
