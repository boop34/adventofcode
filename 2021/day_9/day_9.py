#!/usr/bin/env python3


def first_puzzle(mat):
    n = len(mat)
    m = len(mat[0])
    sum_ = 0
    pos = []

    for r in range(n):
        for c in range(m):
            num = mat[r][c]
            nums = []
            for rn, cn in get_neighbours(mat, r, c):
                nums.append(mat[rn][cn])

            nums.append(num)

            if min_(nums) == num:
                sum_ += num + 1
                pos.append((r, c))

    return sum_, pos


def second_puzzle(mat):
    _, pos = first_puzzle(mat)
    size_ = []

    for r, c in pos:
        size_.append(get_size(mat, r, c))

    size_ = sorted(size_, reverse=True)

    return size_[0] * size_[1] * size_[2]


def min_(arr):
    m = min(arr)

    if arr.count(m) > 1:
        return 10
    return m


def get_neighbours(mat, r, c):
    n = len(mat)
    m = len(mat[0])

    n_list = []

    r1, c1 = r + 1, c
    r2, c2 = r - 1, c
    r3, c3 = r, c + 1
    r4, c4 = r, c - 1

    if r1 < n:
        n_list.append((r1, c1))
    if r2 >= 0:
        n_list.append((r2, c2))

    if c3 < m:
        n_list.append((r3, c3))
    if c4 >= 0:
        n_list.append((r4, c4))

    return n_list


def get_size(mat, r, c):
    n = len(mat)
    m = len(mat[0])
    mat_mask = [[False for _ in range(m)] for _ in range(n)]

    q = [(r, c)]
    mat_mask[r][c] = True
    size_ = 0

    while q:
        x, y = q.pop(0)
        mat_mask[x][y] = True
        size_ += 1

        for rn, cn in get_neighbours(mat, x, y):
            if not mat_mask[rn][cn] and mat[rn][cn] != 9:
                if mat[rn][cn] > mat[x][y]:
                    q.append((rn, cn))
                    mat_mask[rn][cn] = True

    return size_


if __name__ == '__main__':
    mat = []

    with open('day_9.in', 'r') as f:
        for line in f.readlines():
            tmp = [int(i) for i in line.strip()]
            mat.append(tmp)
    
    print(first_puzzle(mat)[0])
    print(second_puzzle(mat))

