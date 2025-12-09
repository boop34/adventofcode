#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <cmath>

long long part_one(std::ifstream& input_file) {
    long long max_area = 0;
    std::vector<std::pair<long long, long long>> points_arr;

    std::string line;
    while (std::getline(input_file, line)) {
        size_t i = line.find(',');

        long long x = std::stoll(line.substr(0, i));
        long long y = std::stoll(line.substr(i+1));

        points_arr.push_back(std::make_pair(x, y));
    }

    for (size_t i = 0; i < points_arr.size(); ++i) {
        for (size_t j = i; j < points_arr.size(); ++j) {
            auto p1 = points_arr[i];
            auto p2 = points_arr[j];

            long long curr_area = (std::abs(p1.first - p2.first) + 1ll)
                * (std::abs(p1.second - p2.second) + 1ll);

            if (curr_area > max_area) max_area = curr_area;
        }
    }

    return max_area;
}

long long part_two(std::ifstream& input_file) {
    long long max_area = 0;
    std::vector<std::pair<long long, long long>> points_arr;
    std::vector<std::vector<long long>> edges;

    std::string line;
    while (std::getline(input_file, line)) {
        size_t i = line.find(',');

        long long x = std::stoll(line.substr(0, i));
        long long y = std::stoll(line.substr(i+1));

        points_arr.push_back(std::make_pair(x, y));
    }

    for (size_t i = 0; i < points_arr.size(); ++i) {
        auto p1 = points_arr[i];
        size_t j = i + 1;
        if (i == points_arr.size() - 1) {
            j = 0;
        }

        auto p2 = points_arr[j];

        edges.push_back({p1.first, p1.second, p2.first, p2.second});
    }

    // AABB collision detection -> https://kishimotostudios.com/articles/aabb_collision/
    auto intersections = [&](long long min_x, long long min_y,
            long long max_x, long long max_y) -> bool
    {
        for (auto &e: edges) {
            long long tmp_min_x = std::min(e[0], e[2]);
            long long tmp_max_x = std::max(e[0], e[2]);
            long long tmp_min_y = std::min(e[1], e[3]);
            long long tmp_max_y = std::max(e[1], e[3]);

            if ((min_x < tmp_max_x) && (max_x > tmp_min_x)
                && (min_y < tmp_max_y) && (max_y > tmp_min_y)) {
                    return true;
                }
        }
        return false;
    };

    for (size_t i = 0; i < points_arr.size() - 1; ++i) {
        for (size_t j = i; j < points_arr.size(); ++j) {
            auto p1 = points_arr[i];
            auto p2 = points_arr[j];

            long long min_x = std::min(p1.first, p2.first);
            long long max_x = std::max(p1.first, p2.first);
            long long min_y = std::min(p1.second, p2.second);
            long long max_y = std::max(p1.second, p2.second);

            long long dist = std::abs(p1.first - p2.first)
                + std::abs(p1.second - p2.second);

            if (std::pow(dist, 2) > max_area) {
                if (!intersections(min_x, min_y, max_x, max_y)) {
                    long long curr_area = (std::abs(p1.first - p2.first) + 1ll)
                        * (std::abs(p1.second - p2.second) + 1ll);

                    if (curr_area > max_area) {
                        max_area = curr_area;
                    }
                }
            }
        }
    }


    return max_area;
}

int main() {
    std::ifstream input_file("day_9.in");

    long long part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    long long part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
