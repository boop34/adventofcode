#include <unordered_set>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

int part_one(std::ifstream& input_file) {
    std::unordered_set<std::string> houses;
    houses.insert("0,0");

    std::string line;
    while (std::getline(input_file, line)) {
        std::pair<int, int> coords = {0, 0};
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '<') {
                coords.first--;
            } else if (line[i] == '>') {
                coords.first++;
            } else if (line[i] == '^') {
                coords.second++;
            } else if (line[i] == 'v') {
                coords.second--;
            }

            std::string curr_house = std::to_string(coords.first)
                                     + ","
                                     + std::to_string(coords.second);
            houses.insert(curr_house);
        }
    }

    return houses.size();
}

int part_two(std::ifstream& input_file) {
    std::unordered_set<std::string> houses;
    houses.insert("0,0");

    std::string line;
    while (std::getline(input_file, line)) {
        std::pair<int, int> santa_coords = {0, 0};
        std::pair<int, int> robo_coords = {0, 0};
        for (size_t i = 0; i < line.length(); ++i) {
            std::pair<int, int> *coords = &santa_coords;
            if ((i % 2) != 0)  {
                coords = &robo_coords;
            }
            if (line[i] == '<') {
                coords->first--;
            } else if (line[i] == '>') {
                coords->first++;
            } else if (line[i] == '^') {
                coords->second++;
            } else if (line[i] == 'v') {
                coords->second--;
            }

            std::string curr_house = std::to_string(coords->first)
                                     + ","
                                     + std::to_string(coords->second);
            houses.insert(curr_house);
        }
    }

    return houses.size();
}

int main() {
    std::ifstream input_file("day_3.in");

    int part_one_sol = part_one(input_file);

    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    int part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
