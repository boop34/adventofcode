#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

long long part_one(std::ifstream& input_file) {
    long long sum = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
			token.erase(
				std::remove_if(
					token.begin(),
					token.end(),
					[](char c) { return std::isspace(static_cast<unsigned char>(c)); }
				),
				token.end()
			);
            size_t sep = token.find('-');
            long long start = std::stoll(token.substr(0, sep));
            long long end = std::stoll(token.substr(sep + 1));

            for (long long i = start; i <= end; ++i) {
                std::string num_str = std::to_string(i);
                size_t str_len = num_str.size();
                std::string first = num_str.substr(0, str_len / 2);
                std::string second = num_str.substr(str_len / 2);

                if (first == second) { sum+= i; }
            }
        }
    }

    return sum;
}

long long part_two(std::ifstream& input_file) {
    long long sum = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
			token.erase(
				std::remove_if(
					token.begin(),
					token.end(),
					[](char c) { return std::isspace(static_cast<unsigned char>(c)); }
				),
				token.end()
			);
            size_t sep = token.find('-');
            long long start = std::stoll(token.substr(0, sep));
            long long end = std::stoll(token.substr(sep + 1));

            for (long long i = start; i <= end; ++i) {
                std::string num_str = std::to_string(i);
                size_t str_len = num_str.size();

                for (size_t k = 1; k <= str_len / 2; ++k) {
                    if ((str_len % k) != 0) { continue; }

                    bool is_valid = true;

                    for (size_t j = k; j < str_len; ++j) {
                        if (num_str[j] != num_str[j % k]) {
                            is_valid = false;
                            break;
                        }
                    }
                    if (is_valid) {
                        sum += i;
                        break;
                    }
                }
            }
        }
    }

    return sum;
}

int main() {
    std::ifstream input_file("day_2.in");

    long long part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    long long part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
