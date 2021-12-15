#!/usr/bin/env python3

import heapq


def first_puzzle(mat, m):
    return get_risk(mat, 0, 0, m)


def second_puzzle(mat, m):
    return first_puzzle(mat, m)


def get_risk(mat, r, c, m):
    n = len(mat)
    q = [(0, r, c)] # starting queue
    visited = set()
    dist_dict = {}

    while q:
        # heappop gives the smallest item from the heap (here based on dist(first element of the tuple))
        dist, r, c = heapq.heappop(q)

        if (r, c) in visited:
            continue

        visited.add((r, c))
        dist_dict[(r, c)] = dist

        if r == n * m - 1 and c == n * m - 1:
            break
        
        for rr, cc in get_neighbours(n * m, r, c):
            heapq.heappush(q, (dist + get_val(mat, rr, cc), rr, cc))

    return dist_dict[(n * m - 1, n * m - 1)]


def get_neighbours(n, r, c):
    n_list = []

    r1, c1 = r + 1, c
    r2, c2 = r - 1, c
    r3, c3 = r, c + 1
    r4, c4 = r, c - 1

    if r1 < n:
        n_list.append((r1, c1))
    if r2 >= 0:
        n_list.append((r2, c2))

    if c3 < n:
        n_list.append((r3, c3))
    if c4 >= 0:
        n_list.append((r4, c4))

    return n_list


def get_val(mat, r, c):
    n = len(mat)
    tmp = mat[r % n][c % n] + (r // n) + (c // n)
    return tmp if tmp < 10 else (tmp % 10) + 1


if __name__ == '__main__':
    mat = []

    with open('day_15.in', 'r') as f:
        for line in f.readlines():
            tmp = [int(i) for i in line.strip()]
            mat.append(tmp)

    print(first_puzzle(mat, 1))
    print(second_puzzle(mat, 5))

