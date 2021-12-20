#!/usr/bin/env python3


def first_puzzle(algo, mat, enhance_cnt):
    cnt = 0

    val = '.'
    for i in range(enhance_cnt):
        mat = pad(mat, 1, val)
        mat = enhance(algo, mat, val)
        # as the matrix is being processed simultaneously we have to
        # predetermine the padding value weather it'll be dark (.) or light (#)
        val = algo[int((val * 9).replace('.', '0').replace('#', '1'), 2)]

    for i in mat:
        cnt += i.count('#')

    return cnt


def second_puzzle(algo, mat, enhance_cnt):
    return first_puzzle(algo, mat, enhance_cnt)


def pad(mat, p, val):
    n = len(mat) + (p * 2)
    m = len(mat[0]) + (p * 2)

    new_mat = [[None for _ in range(m)] for _ in range(n)]

    for r in range(n):
        for c in range(m):
            if r < p or c < p or r >= n - p or c >= m - p:
                new_mat[r][c] = val
            else:
                new_mat[r][c] = mat[r - p][c - p]

    return new_mat


def enhance(algo, mat, val):
    n = len(mat)
    m = len(mat[0])
    new_mat = [[None for _ in range(m)] for _ in range(n)]

    for r in range(n):
        for c in range(m):
            s = ''
            for dr in [-1, 0, 1]:
                for dc in [-1, 0, 1]:
                    rr = r + dr
                    cc = c + dc

                    if rr < 0 or rr >= n or cc < 0 or cc >= m:
                        s += val
                    else:
                        s += mat[rr][cc]

            idx = int(s.replace('.', '0').replace('#', '1'), 2)
            new_mat[r][c] = algo[idx]

    return new_mat


if __name__ == '__main__':
    mat = []

    with open('day_20.in', 'r') as f:
        algo = f.readline().strip()
        for line in f.readlines()[1:]:
            mat.append([i for i in line.strip()])

    print(first_puzzle(algo, mat, 2))
    print(second_puzzle(algo, mat, 50))

