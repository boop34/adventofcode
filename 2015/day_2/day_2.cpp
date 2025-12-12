#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

long long part_one(std::ifstream& input_file) {
    long long result = 0ll;

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> dims;

        size_t c = 0;
        size_t n = 0;

        while ((n = line.find('x', c)) != std::string::npos) {
            int a = std::stoi(line.substr(c, n - c));
            dims.push_back(a);
            c = n + 1;
        }
        int a = std::stoi(line.substr(c));
        dims.push_back(a);

        long long x = dims[0] * dims[1];
        long long y = dims[1] * dims[2];
        long long z = dims[2] * dims[0];
        long long tmp = 2 * x + 2 * y + 2 * z;

        long long min = std::min({x, y, z});

        result += tmp + min;
    }
    return result;
}

long long part_two(std::ifstream& input_file) {
    long long result = 0ll;

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> dims;

        size_t c = 0;
        size_t n = 0;

        while ((n = line.find('x', c)) != std::string::npos) {
            int a = std::stoi(line.substr(c, n - c));
            dims.push_back(a);
            c = n + 1;
        }
        int a = std::stoi(line.substr(c));
        dims.push_back(a);

        std::sort(dims.begin(), dims.end());

        long long v = dims[0] * dims[1] * dims[2];
        long long extra = 2 * dims[0] + 2 * dims[1];

        result += v + extra;

    }
    return result;
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
