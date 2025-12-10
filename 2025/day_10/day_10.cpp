#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int part_one(std::ifstream& input_file) {
    int result = 0;
    std::vector<int> lights;
    std::vector<std::vector<int>> switches_arr;

    std::string line;
    while (std::getline(input_file, line)) {
        bool lights_input = true;
        size_t c = 0;
        size_t n = 0;
        std::vector<int> tmp_switches;
        while ((n = line.find(' ', c)) != std::string::npos) {
            std::string s = line.substr(c, n - c);
            c = n + 1;

            if (lights_input) {
                int tmp_light = 0;
                for (size_t i = 0; i < s.length(); ++i) {
                    if (s[i] == '#') {
                        // subtract 1 as the first character is '[' (garbage)
                        tmp_light |= (1 << (i - 1));
                    }
                }
                lights.push_back(tmp_light);
                lights_input = false;
            } else {
                int m = 0;
                std::string num = "";
                for (size_t i = 0; i < s.length(); ++i) {
                    if (s[i] == '(') {
                        continue;
                    } else if (s[i] == ')') {
                        m |= (1 << std::stoi(num));
                    } else if (s[i] == ',') {
                        m |= (1 << std::stoi(num));
                        num = "";
                    } else {
                        num += s[i];
                    }
                }
                tmp_switches.push_back(m);
            }

        }
        switches_arr.push_back(tmp_switches);
    }

    for (size_t i = 0; i < lights.size(); ++i) {
        int light = lights[i];
        std::vector<int> switches = switches_arr[i];
        int tmp_result = 100000;

        for (size_t j = 0; j < (1 << switches.size()); ++j) {
            int state = 0;
            int count = 0;
            for (size_t k = 0; k < switches.size(); ++k) {
                if (j & (1 << k)) {
                    state ^= switches[k];
                    count++;

                    if (count >= tmp_result) break;
                }
            }

            if (state == light) {
                tmp_result = std::min(tmp_result, count);
            }
        }

        result += tmp_result;
    }

    return result;
}

int part_two(std::ifstream& input_file) {

    return 0;
}

int main() {
    std::ifstream input_file("day_10.in");

    int part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    int part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
