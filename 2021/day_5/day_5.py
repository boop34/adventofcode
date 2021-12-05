#!/usr/bin/env python3


def first_puzzle(coords, max2, may2, mix1=0, miy1=0):
    cnt = 0
    surface = [[0 for _ in range(max2 + 1)] for _ in range(may2 + 1)]

    for a, b in coords:
        x1, y1 = a
        x2, y2 = b

        if (x1 != x2) and (y1 != y2):
            continue

        ii = min(x1, x2)
        ij = max(x1, x2)

        ji = min(y1, y2)
        jj = max(y1, y2)

        for x in range(ii, ij + 1):
            for y in range(ji, jj + 1):
                surface[x][y] += 1

    for x in range(max2 + 1):
        for y in range(may2 + 1):
            if surface[x][y] > 1:
                cnt += 1

    return cnt


def second_puzzle(coords, max2, may2, mix1=0, miy1=0):
    cnt = 0
    surface = [[0 for _ in range(max2 + 1)] for _ in range(may2 + 1)]

    for a, b in coords:
        x1, y1 = a
        x2, y2 = b

        if x1 == x2:
            i = min(y1, y2)
            j = max(y1, y2)

            for y in range(i, j + 1):
                surface[x1][y] += 1

        elif y1 == y2:
            i = min(x1, x2)
            j = max(x1, x2)

            for x in range(i, j + 1):
                surface[x][y1] += 1
        else:
            # direction are based on x1, y1 -> x2, y2
            # up left -> bottom right
            if (x1 < x2) and (y1 < y2):
                inx = 1
                iny = 1
            # up right -> bottom left
            elif (x1 < x2) and (y1 > y2):
                inx = 1
                iny = -1
            # bottom left -> up right
            elif (x1 > x2) and (y1 < y2):
                inx = -1
                iny = 1
            # bottom right -> up left
            elif (x1 > x2) and (y1 > y2):
                inx = -1
                iny = -1
            else:
                print('NOT POSSIBLE')
                exit(1)

            surface = fill_diagonal(surface, x1, y1, x2, y2, inx, iny)

    for x in range(max2 + 1):
        for y in range(may2 + 1):
            if surface[x][y] > 1:
                cnt += 1

    return cnt


def fill_diagonal(surface, x1, y1, x2, y2, inx, iny):
    while (x1 != x2) and (y1 != y2):
        surface[x1][y1] += 1
        x1 += inx
        y1 += iny

    surface[x2][y2] += 1

    return surface


if __name__ == '__main__':
    coords = []
    mix1, miy1 = 0, 0   # upper left co-ords
    max2, may2 = 0, 0   # lower right co-ords

    with open('day_5.in', 'r') as f:
        for line in f.readlines():
            a, b = line.strip().split(' -> ')
            x1, y1 = map(int, a.split(','))
            x2, y2 = map(int, b.split(','))
            
            max2 = max(max2, x2)
            may2 = max(may2, y2)

            coords.append([(x1, y1), (x2, y2)])
            
    max2 = max(max2, may2)
    may2 = max(max2, may2)

    print(first_puzzle(coords, max2, may2, mix1, miy1))
    print(second_puzzle(coords, max2, may2, mix1, miy1))

