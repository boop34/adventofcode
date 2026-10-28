#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> dirs = { { -1, -1 },{ -1, 0 },{ -1, 1 },
									   { 0  , -1 },{ 0, 1 },
									   { 1, -1 } ,{ 1, 0 },{ 1, 1 } };

static int part_one(const std::vector<std::vector<int>> grid, int steps) {
	int result = 0;
	int rows = grid.size();
	int cols = grid[0].size();
	std::vector<std::vector<int>> grid_copy = grid;

	for (int z = 0; z < steps; ++z) {
		std::vector<std::vector<int>> tmp_grid = grid_copy;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				int n = 0;
				for (int k = 0; k < dirs.size(); ++k) {
					int ii = i + dirs[k][0];
					int jj = j + dirs[k][1];

					if ((ii < 0) || (ii >= rows) || (jj < 0) || (jj >= cols)) continue;

					if (grid_copy[ii][jj] == 1) n++;
				}

				if ((grid_copy[i][j] == 1) && ((n != 2) && (n != 3))) {
					tmp_grid[i][j] = 0;
				}
				else if ((grid_copy[i][j] == 0) && (n == 3)) {
					tmp_grid[i][j] = 1;
				}
			}
		}
		grid_copy = tmp_grid;
	}

	for (auto a : grid_copy) {
		for (auto b : a) {
			if (b == 1) result++;
		}
	}

	return result;
}

static int part_two(std::vector<std::vector<int>> grid, int steps) {
	int result = 0;
	int rows = grid.size();
	int cols = grid[0].size();
	grid[0][0] = 1;
	grid[rows - 1][cols - 1] = 1;
	grid[0][cols - 1] = 1;
	grid[rows - 1][0] = 1;

	std::vector<std::vector<int>> grid_copy = grid;

	for (int z = 0; z < steps; ++z) {
		std::vector<std::vector<int>> tmp_grid = grid_copy;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (((i == 0) && (j == 0)) || ((i == 0) && (j == cols - 1)) || ((i == rows - 1) && (j == 0)) || ((i == rows - 1) && (j == cols - 1))) continue;
				int n = 0;
				for (int k = 0; k < dirs.size(); ++k) {
					int ii = i + dirs[k][0];
					int jj = j + dirs[k][1];

					if ((ii < 0) || (ii >= rows) || (jj < 0) || (jj >= cols)) continue;

					if (grid_copy[ii][jj] == 1) n++;
				}

				if ((grid_copy[i][j] == 1) && ((n != 2) && (n != 3))) {
					tmp_grid[i][j] = 0;
				}
				else if ((grid_copy[i][j] == 0) && (n == 3)) {
					tmp_grid[i][j] = 1;
				}
			}
		}
		grid_copy = tmp_grid;
	}

	for (auto a : grid_copy) {
		for (auto b : a) {
			if (b == 1) result++;
		}
	}

	return result;
}

int main() {
	std::vector<std::vector<int>> grid;
	std::string line;

	std::ifstream input_file("day_18.in");

	while (std::getline(input_file, line)) {
		std::vector<int> tmp;
		for (char c : line) {
			if (c == '#') tmp.push_back(1);
			else if (c == '.') tmp.push_back(0);
		}
		grid.push_back(tmp);
	}

	int part_one_sol = part_one(grid, 100);

	int part_two_sol = part_two(grid, 100);

	std::cout << "Part 1: " << part_one_sol << std::endl;
	std::cout << "Part 2: " << part_two_sol << std::endl;

	input_file.close();

	return 0;
}
