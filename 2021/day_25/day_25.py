#!/usr/bin/env python3


def first_puzzle(grid):
    steps = 0
    n = len(grid)
    m = len(grid[0])
    change = True

    while change:
        change = False
        inter_grid = [['.' for _ in range(m)] for _ in range(n)]
        # first the east facing ones move
        for i in range(n):
            for j in range(m):
                if grid[i][j] == '>':
                    if grid[i][(j + 1) % m] == '.':
                        change = True
                        inter_grid[i][(j + 1) % m] = '>'
                        inter_grid[i][j] = '.'
                    else:
                        inter_grid[i][j] = '>'
                elif grid[i][j] == 'v':
                    inter_grid[i][j] = grid[i][j]

        new_grid = [['.' for _ in range(m)] for _ in range(n)]
        # then the south facing ones move
        for i in range(n):
            for j in range(m):
                if inter_grid[i][j] == 'v':
                    if inter_grid[(i + 1) % n][j] == '.':
                        change = True
                        new_grid[(i + 1) % n][j] = 'v'
                        new_grid[i][j] = '.'
                    else:
                        new_grid[i][j] = 'v'
                elif inter_grid[i][j] == '>':
                    new_grid[i][j] = inter_grid[i][j]
        steps += 1
        grid = new_grid

    return steps


if __name__ == '__main__':
    grid = []

    with open('day_25.in', 'r') as f:
        for line in f.readlines():
            grid.append([i for i in line.strip()])

    print(first_puzzle(grid))
    # last day so no second part

