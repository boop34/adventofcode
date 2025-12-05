#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

long long part_one(std::ifstream& input_file) {
    int fresh_total = 0;
    std::vector<std::tuple<long long, long long>> fresh_ranges;
    bool ingredient_section = false;

    std::string line;
    while (std::getline(input_file, line)) {
        if (line.empty()) {
            ingredient_section = true;
            continue;
        }
        if (!ingredient_section)  {
            size_t idx = line.find('-');
            long long first = std::stoll(line.substr(0, idx));
            long long last = std::stoll(line.substr(idx+1));
            fresh_ranges.push_back(std::make_tuple(first, last));
        } else {
            long long ingredient_id = std::stoll(line);
            for (size_t i = 0; i < fresh_ranges.size(); ++i) {
                auto [f, l] = fresh_ranges[i];
                if ((ingredient_id >= f) && (ingredient_id <= l)) {
                    fresh_total++;
                    break;
                }
            }
        }
    }

    return fresh_total;
}

long long part_two(std::ifstream& input_file) {
    long long fresh_total = 0;
    std::vector<std::pair<long long, long long>> fresh_ranges;

    std::string line;
    while (std::getline(input_file, line)) {
        if (line.empty()) {
            break;
        }
        size_t idx = line.find('-');
        long long first = std::stoll(line.substr(0, idx));
        long long last = std::stoll(line.substr(idx+1));
        if (first > last) std::swap(first, last);
        fresh_ranges.push_back(std::make_pair(first, last));
    }

    std::sort(fresh_ranges.begin(), fresh_ranges.end());

    auto [curr_f, curr_l] = fresh_ranges[0];
    fresh_total = curr_l - curr_f + 1;

    for (size_t i = 1; i < fresh_ranges.size(); ++i) {
        auto [f, l] = fresh_ranges[i];

        if (f > curr_l) {
            // disjoint range
            fresh_total += (l - f) + 1;
            curr_f = f;
            curr_l = l;
        } else if (f == curr_l) {
            fresh_total += (l - f);
            curr_l = l;
        } else if (l > curr_l) {
            // extended range
            fresh_total += (l - curr_l);
            curr_l = l;
        }
    }

    return fresh_total;
}

int main() {
    std::ifstream input_file("day_5.in");

    long long part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    long long part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
