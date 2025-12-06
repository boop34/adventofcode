#include <iostream>
#include <fstream>
#include <string>
#include <vector>

long long part_one(std::ifstream& input_file) {
    long long result = 0;
    std::vector<std::vector<long long>> arr;
    std::vector<char> op;

    std::string line;
    while (std::getline(input_file, line)) {
        std::string num = "";
        size_t idx = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == ' ') {
                if (!num.empty()) {
                    if (idx >= arr.size()) {
                        arr.push_back({});
                    }
                    arr[idx].push_back(std::stoll(num));
                    idx++;
                }
                num = "";
            } else if ((line[i] == '+') || (line[i] == '*')) {
                op.push_back(line[i]);
            } else {
                num += line[i];
            }
        }

        if (!num.empty()) {
            if (idx >= arr.size()) {
                arr.push_back({});
            }
            arr[idx].push_back(std::stoll(num));
        }
    }

    for (size_t i = 0; i < op.size(); ++i) {
        long long tmp_res = 0;
        for (size_t j = 0; j < arr[i].size(); ++j) {
            if (op[i] == '+') {
                tmp_res += arr[i][j];
            } else if (op[i] == '*') {
                if (tmp_res == 0) tmp_res = 1;
                tmp_res *= arr[i][j];
            }
        }
        result += tmp_res;
    }

    return result;
}

long long part_two(std::ifstream& input_file) {
    long long result = 0;
    std::vector<std::string> arr;

    std::string line;
    while (std::getline(input_file, line)) {
        arr.push_back(line);
    }

    if (!arr.empty()) {
        arr.back() += " ";
    }

    std::string tmp_num = "";
    long long tmp_res = 0;
    char op = '.';
    for (size_t j = 0; j < arr[0].length(); ++j) {
        tmp_num = "";
        bool sep_col = true;
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i][j] != ' ') {
                sep_col = false;
            }
            if ((arr[i][j] == '*') || (arr[i][j] == '+')) {
                op = arr[i][j];
            } else {
                tmp_num += arr[i][j];
            }
        }
        if (sep_col) {
            result += tmp_res;
            tmp_res = 0;
            op = '.';
        }
        if (op == '+') {
            tmp_res += std::stoll(tmp_num);
        } else if (op == '*') {
            if (tmp_res == 0) tmp_res = 1;
            tmp_res *= std::stoll(tmp_num);
        }
    }
    result += tmp_res;

    return result;
}

int main() {
    std::ifstream input_file("day_6.in");

    long long part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    long long part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    input_file.close();

    return 0;
}
