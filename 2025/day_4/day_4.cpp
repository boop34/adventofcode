#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int part_one(const std::vector<std::vector<int>>& grid) {
    int accessible = 0;

    std::vector<int> dirs = {-1, 0, 1};

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] != 1) {
                continue;
            }
            int sum = 0;
            for (int x: dirs) {
                for (int y: dirs) {
                    if (x == 0 && y == 0) {
                        continue;
                    }
                    if (((i + x) < 0) || ((i + x) >= grid.size())) {
                        continue;
                    }
                    if (((j + y) < 0) || ((j + y) >= grid[i].size())) {
                        continue;
                    }
                    if (grid[i + x][j + y] == 1) {
                        sum++;
                    }
                }
            }
            if (sum < 4) {
                accessible++;
            }
        }
    }
    return accessible;
}

int part_two(std::vector<std::vector<int>>& grid) {
    int removable = 0, old_removable = -1;

    std::vector<int> dirs = {-1, 0, 1};

    while (old_removable != removable) {
        old_removable = removable;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] != 1) {
                    continue;
                }
                int sum = 0;
                for (int x: dirs) {
                    for (int y: dirs) {
                        if (x == 0 && y == 0) {
                            continue;
                        }
                        if (((i + x) < 0) || ((i + x) >= grid.size())) {
                            continue;
                        }
                        if (((j + y) < 0) || ((j + y) >= grid[i].size())) {
                            continue;
                        }
                        if (grid[i + x][j + y] == 1) {
                            sum++;
                        }
                    }
                }
                if (sum < 4) {
                    removable++;
                    grid[i][j] = 0;
                }
            }
        }
    }
    return removable;
}

int main() {
    std::ifstream input_file("day_4.in");
    std::vector<std::vector<int>> grid;

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> row;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == '.') {
                row.push_back(0);
            } else if (line[i] == '@') {
                row.push_back(1);
            }
        }
        grid.push_back(row);
    }

    int part_one_sol = part_one(grid);
    int part_two_sol = part_two(grid);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
