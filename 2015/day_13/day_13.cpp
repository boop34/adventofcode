#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <queue>

int part_one(
        std::unordered_map<std::string, std::unordered_map<std::string, int>>& scores
) {
    int result = INT_MIN;
    std::string first_person = "";
    std::vector<std::string> person_list;

    for (const auto& pair: scores) {
        if (first_person.length() == 0) {
            first_person = pair.first;
        } else {
            person_list.push_back(pair.first);
        }
    }

    std::sort(person_list.begin(), person_list.end());

    do {
        std::vector<std::string> seating_order;
        seating_order.push_back(first_person);
        seating_order.insert(seating_order.end(), person_list.begin(), person_list.end());

        int total = 0;
        int n = seating_order.size();

        for (size_t i = 0; i < n; ++i) {
            const auto& a = seating_order[i];
            const auto& b = seating_order[(i + 1) % n];

            total += scores[a][b];
            total += scores[b][a];
        }

        result = std::max(result, total);

    } while (std::next_permutation(person_list.begin(), person_list.end()));

    return result;
}

int part_two(
        std::unordered_map<std::string, std::unordered_map<std::string, int>> scores
) {
    int result = INT_MIN;
    std::string first_person = "";
    std::vector<std::string> person_list;

    for (const auto& pair: scores) {
        if ((first_person.length() == 0) && (pair.first != "Me")) {
            first_person = pair.first;
        } else {
            person_list.push_back(pair.first);
        }
    }
    scores["Me"][first_person] = 0;
    scores[first_person]["Me"] = 0;

    for (auto s: person_list) {
        scores[s]["Me"] = 0;
        scores["Me"][s] = 0;
    }

    person_list.push_back("Me");

    std::sort(person_list.begin(), person_list.end());

    do {
        std::vector<std::string> seating_order;
        seating_order.push_back(first_person);
        seating_order.insert(seating_order.end(), person_list.begin(), person_list.end());

        int total = 0;
        int n = seating_order.size();

        for (size_t i = 0; i < n; ++i) {
            const auto& a = seating_order[i];
            const auto& b = seating_order[(i + 1) % n];

            total += scores[a][b];
            total += scores[b][a];
        }

        result = std::max(result, total);

    } while (std::next_permutation(person_list.begin(), person_list.end()));

    return result;
}

int main() {
    std::unordered_map<std::string, std::unordered_map<std::string, int>> scores;
    std::ifstream input_file("day_13.in");

    std::string line;
    while (std::getline(input_file, line)) {
        size_t l = line.length();
        size_t a = line.find(' ');
        std::string person_a = line.substr(0, a);
        size_t b = line.rfind(' ');
        std::string person_b = line.substr(b+1, l-b-2);

        std::string score_str = "";
        for (size_t i = 0; i < l; ++i) {
            if (std::isdigit(line[i])) {
                score_str += line[i];
            }
        }

        int score = std::stoi(score_str);

        if (line.find("lose") != std::string::npos) {
            score = -score;
        }

        scores[person_a][person_b] = score;
    }

    int part_one_sol = part_one(scores);
    int part_two_sol = part_two(scores);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
