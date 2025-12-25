#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

class Ingredient {
    public:
        int capacity;
        int durability;
        int flavor;
        int texture;
        int calories;

        Ingredient(std::vector<int> l) {
            capacity = l[0];
            durability = l[1];
            flavor = l[2];
            texture = l[3];
            calories = l[4];
        }
};

long long part_one(std::vector<Ingredient>& list) {
    long long result = 0ll;

    for (long long i = 1; i <= 100; ++i) {
        for (long long j = 1; j <= 100-i; ++j) {
            for (long long k = 1; k <= 100-i-j; ++k) {
                long long l = 100-i-j-k;

                long long cap = 0ll;
                long long dur = 0ll;
                long long fla = 0ll;
                long long tex = 0ll;

                long long qty[4] = { i, j, k, l };

                for (size_t idx = 0; idx < 4; ++idx) {
                    cap += qty[idx] * list[idx].capacity;
                    dur += qty[idx] * list[idx].durability;
                    fla += qty[idx] * list[idx].flavor;
                    tex += qty[idx] * list[idx].texture;
                }

                cap = std::max(0ll, cap);
                dur = std::max(0ll, dur);
                fla = std::max(0ll, fla);
                tex = std::max(0ll, tex);

                result = std::max(result, cap * dur * fla * tex);
            }
        }
    }
    return result;
}

long long part_two(std::vector<Ingredient>& list) {
    long long result = 0ll;

    for (long long i = 1; i <= 100; ++i) {
        for (long long j = 1; j <= 100-i; ++j) {
            for (long long k = 1; k <= 100-i-j; ++k) {
                long long l = 100-i-j-k;

                long long cap = 0ll;
                long long dur = 0ll;
                long long fla = 0ll;
                long long tex = 0ll;
                long long cal = 0ll;

                long long qty[4] = { i, j, k, l };

                for (size_t idx = 0; idx < 4; ++idx) {
                    cap += qty[idx] * list[idx].capacity;
                    dur += qty[idx] * list[idx].durability;
                    fla += qty[idx] * list[idx].flavor;
                    tex += qty[idx] * list[idx].texture;
                    cal += qty[idx] * list[idx].calories;
                }

                cap = std::max(0ll, cap);
                dur = std::max(0ll, dur);
                fla = std::max(0ll, fla);
                tex = std::max(0ll, tex);
                cal = std::max(0ll, cal);

                if (cal == 500) {
                    result = std::max(result, cap * dur * fla * tex);
                }
            }
        }
    }
    return result;
}

int main() {
    std::vector<Ingredient> list;
    std::ifstream input_file("day_15.in");

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> tmp;
        std::string num = "";

        for (size_t i = 0; i < line.length(); ++i) {
            if (std::isdigit(line[i]) || (line[i] == '-')) {
                num += line[i];
            } else if (num.length() > 0) {
                tmp.push_back(std::stoi(num));
                num = "";
            }
        }

        tmp.push_back(std::stoi(num));

        list.push_back(Ingredient(tmp));
    }

    long long part_one_sol = part_one(list);
    long long part_two_sol = part_two(list);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
