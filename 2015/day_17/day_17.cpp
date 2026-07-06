#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<int, int> map;
int part_one_sol = 0;

void get_combinations(const std::vector<int>& list,
        int target, size_t idx, std::vector<int>& current
        ) {
    if (target == 0) {
        map[(int)current.size()]++;
        part_one_sol++;
        return;
    }

    if (target < 0 || idx == list.size()) return;

    // consider current element to be valid
    current.push_back(list[idx]);
    get_combinations(list, target - list[idx], idx+1, current);
    // skip current element
    current.pop_back();
    get_combinations(list, target, idx+1, current);
}

long long part_one(std::vector<int>& list, const int target) {
    std::vector<int> current;
    get_combinations(list, target, 0, current);

    return part_one_sol;
}

int part_two() {
    int min_sum = 5000;

    for (auto& [key, value]: map) {
        if (key < min_sum) min_sum = key;
    }

    return map[min_sum];
}

int main() {
    std::ifstream input_file("day_17.in");
    std::string line;
    std::vector<int> list;
    const int target = 150;

    while (std::getline(input_file, line)) {
        list.push_back(std::stoi(line));
    }

    long long part_one_sol = part_one(list, target);

    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    int part_two_sol = part_two();

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
