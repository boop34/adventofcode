#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <regex>

class Rect {
    public:
        int lx, ly, rx, ry, op;
        Rect(std::vector<int> points, int o) {
            lx = points[0];
            ly = points[1];
            rx = points[2];
            ry = points[3];
            op = o;
        }

        void update_grid_one(int (*grid)[1000]) {
            int min_rows = std::min(lx, rx);
            int min_cols = std::min(ly, ry);
            int max_rows = std::max(lx, rx);
            int max_cols = std::max(ly, ry);

            for (int i = min_rows; i <= max_rows; ++i) {
                for (int j = min_cols; j <= max_cols; ++j) {
                    switch (op) {
                        case 1:
                            grid[i][j] = 1;
                            break;
                        case 0:
                            grid[i][j] = 0;
                            break;
                        case -1:
                            grid[i][j] ^= 1;
                    }
                }
            }
        }

        void update_grid_two(int (*grid)[1000]) {
            int min_rows = std::min(lx, rx);
            int min_cols = std::min(ly, ry);
            int max_rows = std::max(lx, rx);
            int max_cols = std::max(ly, ry);

            for (int i = min_rows; i <= max_rows; ++i) {
                for (int j = min_cols; j <= max_cols; ++j) {
                    switch (op) {
                        case 1:
                            grid[i][j]++;
                            break;
                        case 0:
                            grid[i][j]--;
                            if (grid[i][j] < 0) grid[i][j] = 0;
                            break;
                        case -1:
                            grid[i][j] += 2;
                    }
                }
            }
        }
};

int part_one(std::vector<Rect>& corners) {
    int result = 0;
    int (*grid)[1000] = new int[1000][1000]();

    for (Rect& r: corners) {
        r.update_grid_one(grid);
    }

    for (size_t i = 0; i < 1000; ++i) {
        for (size_t j = 0; j < 1000; ++j) {
            if (grid[i][j] > 0) {
                result++;
            }
        }
    }

    delete[] grid;

    return result;
}

int part_two(std::vector<Rect>& corners) {
    int result = 0;
    int (*grid)[1000] = new int[1000][1000]();

    for (Rect& r: corners) {
        r.update_grid_two(grid);
    }

    for (size_t i = 0; i < 1000; ++i) {
        for (size_t j = 0; j < 1000; ++j) {
            result += grid[i][j];
        }
    }

    delete[] grid;

    return result;
}

int main() {
    std::vector<Rect> corners;
    std::ifstream input_file("day_6.in");
    std::regex pattern("(\\d+,\\d+)");
    std::smatch matches;

    std::string line;
    while (std::getline(input_file, line)) {
        int op = 1;
        if (line.find("on") != std::string::npos) {
            op = 1;
        } else if (line.find("off") != std::string::npos) {
            op = 0;
        } else {
            op = -1;
        }
        std::sregex_iterator begin = std::sregex_iterator(
                line.begin(),
                line.end(),
                pattern);
        std::sregex_iterator end = std::sregex_iterator();
        std::vector<int> points;
        for (std::sregex_iterator it = begin; it != end; ++it) {
            std::smatch match = *it;
            size_t a = match.str().find(',');
            int x = std::stoi(match.str().substr(0, a));
            int y = std::stoi(match.str().substr(a+1));

            points.push_back(x);
            points.push_back(y);
        }

        Rect r(points, op);
        corners.push_back(r);
    }

    int part_one_sol = part_one(corners);
    int part_two_sol = part_two(corners);

    std::cout << "Part 1: " << part_one_sol << std::endl;
    std::cout << "Part 2: " << part_two_sol << std::endl;

    return 0;
}
