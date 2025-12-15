#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool is_number(const std::string& str) {
    return std::all_of(str.begin(), str.end(),
            [](unsigned char c) {
                return std::isdigit(c);
            });
}

unsigned short rec(std::unordered_map<std::string, std::string>& ops_map,
        std::unordered_map<std::string, unsigned short>& memo,
        std::string x) {

    if (memo.count(x)) {
        return memo[x];
    }

    if (is_number(x)) {
        return std::stoi(x) & 0xFFFF;
    }

    if (!ops_map.count(x)) {
        std::cerr << "Illegal wire id:=" << x << "=" << std::endl;
        exit(1);
    }

    std::string ins = ops_map[x];

    size_t a = ins.find(' ');
    std::string first = ins.substr(0, a);
    a++;

    if (first == "NOT") {                        // NOT x -> y
        size_t b = ins.find(' ', a);
        std::string second = ins.substr(a, b-a);
        unsigned int s = 0;
        if (is_number(second)) {
            s = std::stoi(second) & 0xFFFF;
        } else {
            s = rec(ops_map, memo, second);
        }
        unsigned short result = ~s & 0xFFFF;
        memo[x] = result;
        return result;
    } else if (ins.find("AND") != std::string::npos     // x AND y -> d
            || ins.find("OR") != std::string::npos      // x OR y -> e
            || ins.find("LSHIFT") != std::string::npos  // x LSHIFT 2 -> f
            || ins.find("RSHIFT") != std::string::npos) // y RSHIFT 2 -> g
    {
        size_t b = ins.find(' ', a);
        std::string op = ins.substr(a, b-a);
        b++;
        size_t c = ins.find(' ', b);
        std::string second = ins.substr(b, c-b);

        if (op == "AND") {
            unsigned short result = (rec(ops_map, memo, first) & rec(ops_map, memo, second)) & 0xFFFF;
            memo[x] = result;
            return result;
        } else if (op == "OR") {
            unsigned short result = (rec(ops_map, memo, first) | rec(ops_map, memo, second)) & 0xFFFF;
            memo[x] = result;
            return result;
        } else if (op == "LSHIFT") {
            unsigned short result = (rec(ops_map, memo, first) << rec(ops_map, memo, second)) & 0xFFFF;
            memo[x] = result;
            return result;
        } else if (op == "RSHIFT") {
            unsigned short result = (rec(ops_map, memo, first) >> rec(ops_map, memo, second)) & 0xFFFF;
            memo[x] = result;
            return result;
        }
    } else if (is_number(first)) {                      // 123 -> x
        unsigned short result = std::stoi(first) & 0xFFFF;
        memo[x] = result;
        return result;
    } else {                                            // x -> h
        unsigned short result = rec(ops_map, memo, first);
        memo[x] = result;
        return result;
    }

}

unsigned short part_one(std::vector<std::string> ops) {
    std::unordered_map<std::string, std::string> ops_map;
    std::unordered_map<std::string, unsigned short> memo;

    for (std::string op: ops) {
        std::string dest = op.substr(op.rfind(' ')+1);
        ops_map[dest] = op;
    }

    return rec(ops_map, memo, "a");
}

unsigned short part_two(std::vector<std::string> ops) {
    std::unordered_map<std::string, std::string> ops_map;
    std::unordered_map<std::string, unsigned short> tmp_memo;

    for (std::string op: ops) {
        std::string dest = op.substr(op.rfind(' ')+1);
        ops_map[dest] = op;
    }

    unsigned short a_val = rec(ops_map, tmp_memo, "a");
    ops_map["b"] = std::to_string(a_val) + " -> b";
    std::unordered_map<std::string, unsigned short> memo;

    return rec(ops_map, memo, "a");
}

int main() {
    std::vector<std::string> ops;
    std::ifstream input_file("day_7.in");

    std::string line;
    while (std::getline(input_file, line)) {
        ops.push_back(line);
    }

    unsigned short part_one_sol = part_one(ops);
    unsigned short part_two_sol = part_two(ops);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
