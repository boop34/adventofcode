#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

// visualization helper
void print_grid(const std::vector<std::vector<long long>>& grid) {
    for (const auto& row: grid) {
        for (long long x: row) {
            std::cout << std::setw(4) << x;
        }
        std::cout << std::endl;
    }
}

int part_one(std::ifstream& input_file) {
    int splits = 0;
    std::vector<std::string> grid;

    std::string line;
    while (std::getline(input_file, line)) {
        grid.push_back(line);
    }

    for (size_t i = 1; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].length(); ++j) {
            if (grid[i-1][j] == 'S') {
                grid[i][j] = '|';
            } else if ((grid[i-1][j] == '|') && (grid[i][j] == '^')) {
                grid[i][j-1] = '|';
                grid[i][j+1] = '|';
                splits++;
            } else if ((grid[i-1][j] == '|') && (grid[i][j] == '.')) {
                grid[i][j] = '|';
            }
        }
    }

    return splits;
}

long long part_two(std::ifstream& input_file) {
    long long timelines = 0;
    std::vector<std::vector<long long>> grid;

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<long long> arr;
        for(size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '.') {
                arr.push_back(0);
            } else if (line[i] == 'S') {
                arr.push_back(1);
            } else if (line[i] == '^') {
                arr.push_back(-1);
            }
        }
        grid.push_back(arr);
    }

    for (size_t i = 1; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if ((grid[i-1][j] > 0) && (grid[i][j] == -1)) {
                grid[i][j-1] += grid[i-1][j];
                grid[i][j+1] += grid[i-1][j];
            } else if ((grid[i-1][j] > 0) && (grid[i][j] != -1)) {
                grid[i][j] += grid[i-1][j];
            }
        }
    }

    for (size_t i = 0; i < grid[grid.size() - 1].size(); ++i) {
        timelines += grid[grid.size()-1][i];
    }

    return timelines;
}

int main() {
    std::ifstream input_file("day_7.in");

    int part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    long long part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
