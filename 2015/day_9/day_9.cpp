#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int part_one(std::unordered_map<std::string, std::unordered_map<std::string, int>>& map,
        std::vector<std::string>& cities) {
    int result = INT_MAX;

    do {
        int total = 0;
        bool valid = true;

        for (size_t i = 0; i < cities.size() - 1; ++i) {
            const auto& from = cities[i];
            const auto& to = cities[i+1];

            if (!map[from].count(to)) {
                valid = false;
                break;
            }

            total += map[from][to];
        }

        if (valid) {
            result = std::min(result, total);
        }

    } while (std::next_permutation(cities.begin(), cities.end()));

    return result;
}

int part_two(std::unordered_map<std::string, std::unordered_map<std::string, int>>& map,
        std::vector<std::string>& cities) {
    int result = INT_MIN;

    do {
        int total = 0;
        bool valid = true;

        for (size_t i = 0; i < cities.size() - 1; ++i) {
            const auto& from = cities[i];
            const auto& to = cities[i+1];

            if (!map[from].count(to)) {
                valid = false;
                break;
            }

            total += map[from][to];
        }

        if (valid) {
            result = std::max(result, total);
        }

    } while (std::next_permutation(cities.begin(), cities.end()));

    return result;
}

int main() {
    std::unordered_map<std::string, std::unordered_map<std::string, int>> map;
    std::vector<std::string> cities;
    std::ifstream input_file("day_9.in");

    std::string line;
    while (std::getline(input_file, line)) {
        size_t a = line.find(' ');
        std::string source = line.substr(0, a);
        size_t b = line.find("to ") + 2;
        size_t c = line.find(' ', b+1);
        std::string dest = line.substr(b+1, c-b-1);
        int dist = std::stoi(line.substr(line.rfind(' ')+1));
        map[source][dest] = dist;
        map[dest][source] = dist;
    }

    for (const auto& pair: map) {
        cities.push_back(pair.first);
    }

    std::sort(cities.begin(), cities.end());

    int part_one_sol = part_one(map, cities);
    int part_two_sol = part_two(map, cities);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
