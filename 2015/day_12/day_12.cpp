#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include "json.hpp"

using json = nlohmann::json;

long long part_one(std::string json_str) {
    long long result = 0ll;

    std::string num = "0";

    for (size_t i = 0; i < json_str.length(); ++i) {
        if (std::isdigit(json_str[i])) {
            num += json_str[i];
        } else if (json_str[i] == '-') {
            num = "-";
        } else {
            result += std::stoi(num);
            num = "0";
        }
    }

    return result;
}

long long part_two(const json& json_obj) {
    if (json_obj.is_number()) {
        return json_obj.get<long long>();
    }

    if (json_obj.is_array()) {
        long long total = 0;
        for (const auto& v : json_obj) {
            total += part_two(v);
        }
        return total;
    }

    if (json_obj.is_object()) {
        for (const auto& [k, v] : json_obj.items()) {
            if (v.is_string() && v == "red") {
                return 0;
            }
        }

        long long total = 0;
        for (const auto& [k, v] : json_obj.items()) {
            total += part_two(v);
        }
        return total;
    }

    return 0;
}

int main() {
    std::ifstream input_file("day_12.in");
    std::string json_str;
    json json_obj;

    std::getline(input_file, json_str);

    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    input_file >> json_obj;

    long long part_one_sol = part_one(json_str);
    long long part_two_sol = part_two(json_obj);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
