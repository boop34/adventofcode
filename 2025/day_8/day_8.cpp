#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>

double distance (const std::vector<int>& p1, const std::vector<int>& p2) {
    return sqrt(
            pow(p1[0]-p2[0], 2) + pow(p1[1]-p2[1], 2) + pow(p1[2]-p2[2], 2)
           );
}

long long my_part_one(std::ifstream& input_file) {
    std::vector<std::vector<int>> arr;
    std::vector<std::vector<double>> dist_arr;
    std::unordered_map<double, std::vector<double>> graph;
    std::unordered_map<double, bool> seen;
    std::vector<double> circuits_count;

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> point;
        size_t last = 0;
        size_t next = 0;

        while ((next = line.find(',', last)) != std::string::npos) {
            point.push_back(std::stoi(line.substr(last, next-last)));
            last = next + 1;
        }
        point.push_back(std::stoi(line.substr(last)));
        arr.push_back(point);
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            double len = distance(arr[i], arr[j]);

            std::vector<double> tmp_arr = { len, static_cast<double>(i), static_cast<double>(j) };
            dist_arr.push_back(tmp_arr);
        }
    }

    for (double i = 0; i < arr.size(); ++i) {
        graph[i] = {};
        seen[i] = false;
    }

	std::sort(dist_arr.begin(), dist_arr.end(),
			  [](const std::vector<double>& a,
				 const std::vector<double>& b) {
				  return a[0] < b[0];   // sort by distance
			  });

    for (size_t i = 0; i < 1000; ++i) {
        graph[dist_arr[i][1]].push_back(dist_arr[i][2]);
        graph[dist_arr[i][2]].push_back(dist_arr[i][1]);
    }

    for (const auto &pair: graph) {
        double s = pair.first;
        long long count = 0;

        std::queue<double> q;
        q.push(s);

        while (!q.empty()) {
            double c = q.front();
            q.pop();
            if (!seen[c]) count++;

            seen[c] = true;

            for (size_t i = 0; i < graph[c].size(); ++i) {
                if (seen[graph[c][i]]) {
                    continue;
                }
                q.push(graph[c][i]);
            }
        }

        circuits_count.push_back(count);
    }

    std::sort(circuits_count.begin(), circuits_count.end(), std::greater<double>());

    return circuits_count[0] * circuits_count[1] * circuits_count[2];
}

// finds the root of the set contain
long long find(long long x, std::unordered_map<long long, long long>& uf) {
    if (x == uf[x]) return x;

    uf[x] = find(uf[x], uf);
    return uf[x];
}

// merges the sets containg x and y
void merge(long long x, long long y, std::unordered_map<long long, long long>& uf) {
    uf[find(x, uf)] = find(y, uf);
}

long long part_one(std::ifstream& input_file) {
    std::vector<std::vector<int>> arr;
    std::vector<std::vector<long long>> dist_arr;
    std::unordered_map<long long, long long> uf;
    std::unordered_map<long long, long long> circuits_map;

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> point;
        size_t last = 0;
        size_t next = 0;

        while ((next = line.find(',', last)) != std::string::npos) {
            point.push_back(std::stoi(line.substr(last, next-last)));
            last = next + 1;
        }
        point.push_back(std::stoi(line.substr(last)));
        arr.push_back(point);
    }

    for (long long i = 0; i < (long long) arr.size(); ++i) {
        for (long long j = i + 1; j < arr.size(); ++j) {
            long long dist = pow(arr[i][0] - arr[j][0], 2)
                        + pow(arr[i][1] - arr[j][1], 2)
                        + pow(arr[i][2] - arr[j][2], 2);

            std::vector<long long> tmp_arr = { dist, i, j };
            dist_arr.push_back(tmp_arr);
        }
    }

	std::sort(dist_arr.begin(), dist_arr.end(),
			  [](const std::vector<long long>& a,
				 const std::vector<long long>& b) {
				  return a[0] < b[0];   // sort by distance
			  });

    for (long long i = 0; i < (long long) arr.size(); ++i) {
        uf[i] = i;
        circuits_map[i] = 0ll;
    }

    for (size_t i = 0; i < 1000; ++i) {
        long long x = dist_arr[i][1];
        long long y = dist_arr[i][2];

        merge(x, y, uf);
    }

    for (long long i = 0; i < (long long) arr.size(); ++i) {
        circuits_map[find(i, uf)]++;
    }

    std::vector<long long> circuits_count;
    for (const auto &pair: circuits_map) {
        circuits_count.push_back(pair.second);
    }

    std::sort(circuits_count.begin(), circuits_count.end(), std::greater<int>());

    return circuits_count[0] * circuits_count[1] * circuits_count[2];
}

long long part_two(std::ifstream& input_file) {
    int connections = 0;
    std::vector<std::vector<int>> arr;
    std::vector<std::vector<long long>> dist_arr;
    std::unordered_map<long long, long long> uf;

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<int> point;
        size_t last = 0;
        size_t next = 0;

        while ((next = line.find(',', last)) != std::string::npos) {
            point.push_back(std::stoi(line.substr(last, next-last)));
            last = next + 1;
        }
        point.push_back(std::stoi(line.substr(last)));
        arr.push_back(point);
    }

    for (long long i = 0; i < (long long) arr.size(); ++i) {
        for (long long j = i + 1; j < arr.size(); ++j) {
            long long dist = pow(arr[i][0] - arr[j][0], 2)
                        + pow(arr[i][1] - arr[j][1], 2)
                        + pow(arr[i][2] - arr[j][2], 2);

            std::vector<long long> tmp_arr = { dist, i, j };
            dist_arr.push_back(tmp_arr);
        }
    }

	std::sort(dist_arr.begin(), dist_arr.end(),
			  [](const std::vector<long long>& a,
				 const std::vector<long long>& b) {
				  return a[0] < b[0];   // sort by distance
			  });

    for (long long i = 0; i < (long long) arr.size(); ++i) {
        uf[i] = i;
    }

    for (size_t i = 0; i < dist_arr.size(); ++i) {
        long long x = dist_arr[i][1];
        long long y = dist_arr[i][2];

        if (find(x, uf) != find(y, uf)) {
            connections++;
            if (connections == (arr.size() - 1)) {
                return arr[x][0] * arr[y][0];
            }
            merge(x, y, uf);
        }
    }

    return 0ll;
}

int main() {
    std::ifstream input_file("day_8.in");

    long long part_one_sol = part_one(input_file);
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    long long part_two_sol = part_two(input_file);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
