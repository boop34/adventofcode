#!/usr/bin/env python3

'''
consider both of the possibilities for both of the puzzles
for first puzzle: consider n to be both odd or even
for second puzzle: consider both floor and ceiling of the average
'''

def first_puzzle(pos):
    n = len(pos)
    cost1 = 0
    pos.sort()

    mid = pos[n // 2]

    for i in range(n):
        cost1 += abs(pos[i] - mid)

    if n % 2 == 0:
        cost2 = 0
        mid = pos[n // 2 - 1]

        for i in range(n):
            cost2 += abs(pos[i] - mid)

        cost1 = min(cost1, cost2)
    
    return cost1


def second_puzzle(pos):
    n = len(pos)
    cost1, cost2 = 0, 0
    avg1, avg2 = sum(pos) // n, round(sum(pos) / n)

    foo = lambda x: sum([i + 1 for i in range(x)])

    for i in range(n):
        cost1 += foo(abs(pos[i] - avg1))
        cost2 += foo(abs(pos[i] - avg2))

    return min(cost1, cost2)


if __name__ == '__main__':
    pos = []

    with open('day_7.in', 'r') as f:
        pos = list(map(int, f.readline().strip().split(',')))

    print(first_puzzle(pos))
    print(second_puzzle(pos))

