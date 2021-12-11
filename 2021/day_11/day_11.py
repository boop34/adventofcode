#!/usr/bin/env python3


def first_puzzle(mat, x):
    n = len(mat)
    m = len(mat[0])
    glow = 0

    for _ in range(x):
        mat_mask = [[False for _ in range(m)] for _ in range(n)]
        for r in range(n):
            for c in range(m):
                make_glow(mat, r, c, mat_mask)

        for r in range(n):
            for c in range(m):
                if mat[r][c] == 0:
                    glow += 1

    return glow


def second_puzzle(mat):
    n = len(mat)
    m = len(mat[0])
    step = 1

    while True:
        flag = True
        mat_mask = [[False for _ in range(m)] for _ in range(n)]

        for r in range(n):
            for c in range(m):
                make_glow(mat, r, c, mat_mask)
        
        for r in range(n):
            for c in range(m):
                if mat[r][c] != 0:
                    flag = False
        
        if flag:
            break

        step += 1

    return step


def get_neighbours(mat, r, c, n, m):
    dir_R = [1, 0, -1, 0]
    dir_C = [0, 1, 0, -1]

    n_list = set()

    for i in range(4):
        for j in range(4):
            if dir_R[i] == 0 and dir_C[j] == 0:
                continue
            rr = r + dir_R[i]
            cc = c + dir_C[j]

            if 0 <= rr < n and 0 <= cc < m:
                n_list.add((rr, cc))

    return n_list


def make_glow(mat, r, c, mat_mask):
    n = len(mat)
    m = len(mat[0])

    if mat_mask[r][c]:
        return

    mat[r][c] += 1

    if mat[r][c] > 9:
        mat_mask[r][c] = True
        mat[r][c] = 0

        for rr, cc in get_neighbours(mat, r, c, n, m):
            make_glow(mat, rr, cc, mat_mask)

    return


if __name__ == '__main__':
    mat1 = []
    mat2 = []

    with open('day_11.in', 'r') as f:
        for line in f.readlines():
            mat1.append([int(i) for i in line.strip()])
            mat2.append([int(i) for i in line.strip()])
            
    print(first_puzzle(mat1, 100))
    # or print(second_puzzle(mat1) + 100) as the original matrix is already processed for 100 steps in the first puzzle
    print(second_puzzle(mat2))

