#!/usr/bin/env python3

from collections import defaultdict


def first_puzzle(steps):
    cnt = 0
    cubes = {}

    for x in range(-50, 51):
        for y in range(-50, 51):
            for z in range(-50, 51):
                cubes[(x, y, z)] = False

    for ins, x1, x2, y1, y2, z1, z2 in steps:
        if x1 < -50 or x2 > 50:
            continue
        state = True if ins == 'on' else False
        for x in range(x1, x2 + 1):
            for y in range(y1, y2 + 1):
                for z in range(z1, z2 + 1):
                    cubes[(x, y, z)] = state

    for cube in cubes:
        if cubes[cube]:
            cnt += 1

    return cnt

# https://www.reddit.com/r/adventofcode/comments/rlxhmg/2021_day_22_solutions/hpizza8/
def second_puzzle(steps):
    tot_cubes = 0
    cubes = defaultdict(int)

    for ins, x1, x2, y1, y2, z1, z2 in steps:
        for old_cubes, val in cubes.copy().items():
            intersect = get_intersection(x1, x2, y1, y2, z1, z2, *old_cubes)
            if intersect:
                cubes[intersect] -= val

        if ins == 'on':
            cubes[(x1, x2, y1, y2, z1, z2)] += 1

    for cubes, val in cubes.items():
        x1, x2, y1, y2, z1, z2 = cubes
        vol = (x2 - x1 + 1) * (y2 - y1 + 1) * (z2 - z1 + 1)
        tot_cubes += vol * val

    return tot_cubes


def get_intersection(x1, x2, y1, y2, z1, z2, ox1, ox2, oy1, oy2, oz1, oz2):
    #
    # intersection explanation with 1D values
    #       ox1--------ox2
    #   x1--|------x2   |         x1---x2  ox1---ox2
    #   |   |       |   |         |     |   |     |
    #   0 1 2 3 4 5 6 7 8 9 10    0 1 2 3 4 5 6 7 8 9 10
    #       INTERSECTION            NO INTEREÎySECTION
    #
    # so in order to see the intersection we have to figire out if the maximum
    # of x1 and ox1 is smaller than minimum of x2 and ox2
    #
    ix1 = max(x1, ox1)
    ix2 = min(x2, ox2)

    iy1 = max(y1, oy1)
    iy2 = min(y2, oy2)

    iz1 = max(z1, oz1)
    iz2 = min(z2, oz2)

    if ix1 <= ix2 and iy1 <= iy2 and iz1 <= iz2:
        return ix1, ix2, iy1, iy2, iz1, iz2


if __name__ == '__main__':
    steps = []

    with open('day_22.in', 'r') as f:
        for line in f.readlines():
            ins, coords = line.strip().split(' ')
            x, y, z = coords.split(',')
            # unpacking a map object as tuple [TIL]
            # unnecessary in this case but reference for future use
            x1, x2 = *map(int, x[2:].split('..')),
            y1, y2 = *map(int, y[2:].split('..')),
            z1, z2 = *map(int, z[2:].split('..')),

            steps.append((ins, x1, x2, y1, y2, z1, z2))

    print(first_puzzle(steps))
    print(second_puzzle(steps))

