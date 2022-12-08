#!/usr/bin/env python3

import re

crates = []
steps = []
flag = False

with open('day_5.in', 'r') as f:
    for line in f.readlines():
        if line == '\n':
            flag = True
        '''
            [D]
        [N] [C]
        [Z] [M] [P]
         1   2   3

        as crates are formated like above, the relevant informaion is in every 3rd index
        '''
        if not flag:
            crates.append(line[1::4])
        else:
            steps.append(tuple(map(int, re.findall(r'\d+', line))))

crates = crates[:-1]
steps = steps[1:]
n = len(crates)                         # rows
m = max(map(lambda x: len(x), crates))  # cols


class Crates:
    def __init__(self, n, m):
        self.n = n
        self.m = m
        self.crates = []

    def print_crates(self):
        for row in self.crates:
            print(*row)

    def fill_crates(self, crates):
        for c in range(m):
            arr = []
            for r in range(n):
                arr.append(crates[r][c])
            self.crates.append(arr)
        for row in range(m):
            self.crates[row] = [i for i in self.crates[row][::-1] if i != ' ']

    def move_9000(self, q, a, b):
        '''
        q -> quantity, a -> source stack, b -> destination stack
        '''
        for _ in range(q):
            source_crate = self.crates[a - 1][-1]
            self.crates[a - 1] = self.crates[a - 1][:-1]
            self.crates[b - 1].append(source_crate)

    def move_9001(self, q, a, b):
        '''
        q -> quantity, a -> source stack, b -> destination stack
        multiple stacks are picked at once
        '''
        source_crates = self.crates[a - 1][-1: -1 - q: -1]
        self.crates[a - 1] = self.crates[a - 1][: -q]
        self.crates[b - 1].extend(source_crates[::-1])

    def top_crates(self):
        top_crates = ''
        for row in self.crates:
            top_crates += row[-1]
        return top_crates


crate1 = Crates(n, m)
crate1.fill_crates(crates)
for step in steps:
    crate1.move_9000(*step)
print(crate1.top_crates())

crate2 = Crates(n, m)
crate2.fill_crates(crates)
for step in steps:
    crate2.move_9001(*step)
print(crate2.top_crates())
