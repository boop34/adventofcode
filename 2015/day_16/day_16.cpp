#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

class Sue {
    public:
        std::unordered_map<std::string, int> compounds = {
            {"children", -1},
            {"cats", -1},
            {"samoyeds", -1},
            {"pomeranians", -1},
            {"akitas", -1},
            {"vizslas", -1},
            {"goldfish", -1},
            {"cars", -1},
            {"perfumes", -1},
        };
};

size_t part_one(std::vector<Sue>& list, std::unordered_map<std::string, int>& target) {
    for (size_t i = 0; i < list.size(); ++i) {
        bool f = true;
        for (const auto& pair: list[i].compounds) {
            if ((target.count(pair.first) <= 0) || (pair.second == -1)) {
                continue;
            }

            if (pair.second != target[pair.first]) {
                f = false;
                break;
            }
        }

        if (f) {
            return i + 1;
        }
    }

    return 0;
}

size_t part_two(const std::vector<Sue>& list, const std::unordered_map<std::string, int>& target) {
    size_t result = 0;

    for (size_t i = 0; i < list.size(); ++i) {
        bool f = true;
        for (const auto& pair: list[i].compounds) {
            auto it = target.find(pair.first);
            if ((it == target.end()) || (pair.second == -1)) {
                continue;
            }

            int val = it->second;

            if (
                    ((pair.first == "cats") || (pair.first == "trees"))
                    && (pair.second <= val)
                )
            {
                f = false;
                break;
            } else if (
                    ((pair.first == "pomeranians") || (pair.first == "goldfish"))
                    && (pair.second >= val)
                    )
            {
                f = false;
                break;
            } else if (
                    ((pair.first != "cats") && (pair.first != "trees")
                     && (pair.first != "pomeranians") && (pair.first != "goldfish"))
                    && (pair.second != val)
                    ) {
                f = false;
                break;
            }
        }

        if (f) {
            return i + 1;
        }
    }

    return result;
}

int main() {
    std::vector<Sue> list;
    std::unordered_map<std::string, int> target;
    std::ifstream input_file("day_16.in");

    std::regex pattern (R"(\w+:\s+\d+)");

    std::string line;
    while (std::getline(input_file, line)) {
        std::sregex_iterator begin(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        Sue s;

        for (std::sregex_iterator it = begin; it != end; ++it) {
            std::string pair = it->str();
            size_t idx = pair.find(':');

            std::string comp = pair.substr(0, idx);
            int val = std::stoi(pair.substr(idx+1));

            s.compounds[comp] = val;
        }

        list.push_back(s);
    }

    target["children"] = 3;
    target["cats"] = 7;
    target["samoyeds"] = 2;
    target["pomeranians"] = 3;
    target["akitas"] = 0;
    target["vizslas"] = 0;
    target["goldfish"] = 5;
    target["trees"] = 3;
    target["cars"] = 2;
    target["perfumes"] = 1;

    size_t part_one_sol = part_one(list, target);
    size_t part_two_sol = part_two(list, target);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
