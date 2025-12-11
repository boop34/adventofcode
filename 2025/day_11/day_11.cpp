#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

int dfs(std::unordered_map<std::string, std::vector<std::string>>& map,
        const std::string& source,
        std::unordered_map<std::string, int>& memo)
{
    if (source == "out") {
        return 1;
    }

    if (memo.count(source)) {
        return memo[source];
    }

    int total = 0;

    for (const std::string& next: map[source]) {
        total += dfs(map, next, memo);
    }

    memo[source] = total;

    return total;
}

int part_one(std::unordered_map<std::string, std::vector<std::string>>& map) {
    std::unordered_map<std::string, int> memo;
    int result = dfs(map, "you", memo);

    return result;
}

long long dfs2(std::unordered_map<std::string, std::vector<std::string>>& map,
        const std::string& source,
        std::unordered_map<std::string, std::unordered_map<int, long long>>& memo,
        bool dac, bool fft)
{
    if (source == "out") {
        return (dac && fft) ? 1ll : 0ll;
    }

    // | combined bits
    // 1 -> 01
    // 2 -> 10
    // 1 | 2 -> 01 | 10 -> 11
    int state = (dac ? 1 : 0) | (fft ? 2 : 0);
    if (memo[source].count(state)) {
        return memo[source][state];
    }

    long long total = 0ll;

    for (const std::string& next: map[source]) {
        bool dac_new = dac || (next == "dac");
        bool fft_new = fft || (next == "fft");
        total += dfs2(map, next, memo, dac_new, fft_new);
    }

    memo[source][state] = total;

    return total;
}

long long part_two(std::unordered_map<std::string, std::vector<std::string>>& map) {
    std::unordered_map<std::string, std::unordered_map<int, long long>> memo;
    long long result = dfs2(map, "svr", memo, false, false);

    return result;
}

int main() {
    std::unordered_map<std::string, std::vector<std::string>> map;

    std::ifstream input_file("day_11.in");

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<std::string> dest_arr;
        size_t a = line.find(':');
        std::string source = line.substr(0, a);
        a += 2;

        size_t c = a, n = a;
        while ((n = line.find(' ', c)) != std::string::npos) {
            std::string dest_id = line.substr(c, n - c);
            if (map[source].size() > 0) {
                map[source].push_back(dest_id);
            } else {
                map[source] = { dest_id };
            }
            c = n + 1;
        }
        if (map[source].size() > 0) {
            map[source].push_back(line.substr(c));
        } else {
            map[source] = { line.substr(c) };
        }
    }

    int part_one_sol = part_one(map);
    long long part_two_sol = part_two(map);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 1: " << part_two_sol << std::endl;

    return 0;
}
