#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using grid = std::vector<std::vector<int>>;

int part_one(std::vector<grid>& present_shapes,
        std::vector<std::pair<int, int>>& dims_list,
        grid& present_counts)
{
    int result = 0;
    int a = present_shapes[0][0].size();
    int present_area = a * a;

    for (size_t i = 0; i < dims_list.size(); ++i) {
        int region_area = dims_list[i].first * dims_list[i].second;

        int total_present_count = 0;
        for (size_t j = 0; j < present_counts[i].size(); ++j) {
            total_present_count += present_counts[i][j];
        }

        // subtracting 6 as some presents can be fitted inside some parts of
        // another present so taking a extra row and col for such cases
        if ((total_present_count * present_area) - 6 <= region_area) {
            result++;
        }
    }
    return result;
}

int main() {
    std::vector<grid> present_shapes;
    std::vector<std::pair<int, int>> dims_list;
    grid present_counts;

    std::ifstream input_file("day_12.in");
    std::string line;

    grid present_shape;

    while (std::getline(input_file, line)) {
        if (present_shapes.size() < 6) {
            std::vector<int> tmp_shape = {};
            if (line.find(':') != std::string::npos) {
                continue;
            } else if (line.empty()) {
                present_shapes.push_back(present_shape);
                present_shape.clear();
                continue;
            }

            for (size_t i = 0; i < line.length(); ++i) {
                if (line[i] == '#') {
                    tmp_shape.push_back(1);
                } else {
                    tmp_shape.push_back(0);
                }
            }
            present_shape.push_back(tmp_shape);

        } else {
            std::vector<int> tmp_count;
            size_t idx = line.find(':');
            std::string dim = line.substr(0, idx);

            size_t x = dim.find('x');
            int a = std::stoi(dim.substr(0, x));
            int b = std::stoi(dim.substr(x+1));

            dims_list.push_back(std::make_pair(a, b));

            size_t c = idx + 2;
            size_t n = idx + 2;

            while ((n = line.find(' ', c)) != std::string::npos) {
                tmp_count.push_back(std::stoi(line.substr(c, n - c)));
                c = n + 1;
            }
            tmp_count.push_back(std::stoi(line.substr(c)));

            present_counts.push_back(tmp_count);
        }
    }

    int part_one_sol = part_one(present_shapes, dims_list, present_counts);

    std::cout << "Part 1: " << part_one_sol << std::endl;

    return 0;
}
