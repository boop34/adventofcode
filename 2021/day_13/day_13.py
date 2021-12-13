#!/usr/bin/env python3


def first_puzzle(dots, folds):
    max_x = max(dots)[0]
    max_y = max(dots, key=lambda x: x[1])[1]
    cnt = 0

    grid = [['.' for _ in range(max_x + 1)] for _ in range(max_y + 1)]

    for x, y in dots:
        grid[y][x] = '#'

    for pos, val in folds:
        if pos == 'x':
            grid = fold_x(grid, pos, val)
        else:
            grid = fold_y(grid, pos, val)
        break

    for i in range(len(grid)):
        cnt += grid[i].count('#')

    return cnt


def second_puzzle(dots, folds):
    max_x = max(dots)[0]
    max_y = max(dots, key=lambda x: x[1])[1]

    grid = [['.' for _ in range(max_x + 1)] for _ in range(max_y + 1)]

    for x, y in dots:
        grid[y][x] = '#'

    for pos, val in folds:
        if pos == 'x':
            grid = fold_x(grid, pos, val)
        else:
            grid = fold_y(grid, pos, val)

    for i in range(len(grid)):
        print(*grid[i])

    return '↑↑ SEE THE CODE ABOVE ↑↑'


def fold_x(grid, pos, val):
    max_x = len(grid[0])
    max_y = len(grid)
    new_grid = []

    for y in range(max_y):
        for x in range(max_x):
            if x > val and grid[y][x] == '#':
                grid[y][val + val - x] = '#'
    
    for y in range(max_y):
        new_grid.append(grid[y][:val])

    return new_grid


def fold_y(grid, pos, val):
    max_x = len(grid[0])
    max_y = len(grid)
    new_grid = []

    for y in range(max_y):
        for x in range(max_x):
            if y > val and grid[y][x] == '#':
                grid[val + val - y][x] = '#'

    for y in range(val):
        new_grid.append(grid[y])

    return new_grid


if __name__ == '__main__':
    dots = []
    folds = []

    with open('day_13.in', 'r') as f:
        for line in f.readlines():
            l = line.strip()
            if not l:
                continue

            if 'fold' in l:
                tmp, b = l.split('=')
                a = tmp[-1]
                folds.append((a, int(b)))
                continue

            a, b = map(int, l.split(','))
            dots.append((a, b))

    print(first_puzzle(dots, folds))
    print(second_puzzle(dots, folds))

