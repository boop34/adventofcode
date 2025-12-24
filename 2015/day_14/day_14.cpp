#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

class Reindeer {
    public:
        int speed;
        int active_time;
        int resting_time;
        int score = 0;

        Reindeer(const std::vector<int> l) {
            speed = l[0];
            active_time = l[1];
            resting_time = l[2];
        }
};

long long traveled_dist(Reindeer& r, long long t) {
    long long dist = r.speed * r.active_time;
    long long time = r.active_time + r.resting_time;

    long long traveled = (dist * (t / time));

    long long remaining = t % time;
    traveled += r.speed * std::min(remaining, (long long)r.active_time);

    return traveled;
}

long long part_one(std::vector<Reindeer>& list, long long t) {
    long long result = 0ll;

    for (auto r: list) {
        long long traveled = traveled_dist(r, t);
        result = std::max(result, traveled);
    }

    return result;
}

long long part_two(std::vector<Reindeer>& list, long long t) {
    long long result = 0ll;

    for (long long i = 1; i <= t; ++i) {
        long long max_dist = 0;
        size_t max_idx = 0;
        for (size_t j = 0; j < list.size(); ++j) {
            long long traveled = traveled_dist(list[j], i);

            if (traveled > max_dist) {
                max_dist = traveled;
                max_idx = j;
            }
        }
        list[max_idx].score++;
    }

    for (auto r: list) {
        if (r.score > result) {
            result = r.score;
        }
    }

    return result;
}

int main() {
    std::vector<Reindeer> l;
    std::ifstream input_file("day_14.in");

    std::regex pattern(R"(\d+)");
    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> tmp;
        auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            tmp.push_back(std::stoi(it->str()));
        }

        l.push_back(Reindeer(tmp));
    }

    long long part_one_sol = part_one(l, 2503);
    long long part_two_sol = part_two(l, 2503);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
