#!/usr/bin/env python3

prev = None
inc = 0
arr = []

with open('day_1.in', 'r') as f:
    for line in f.readlines():
        curr = int(line)
        if not prev:
            prev = curr
        elif prev < curr:
            inc += 1

        prev = curr
        arr.append(curr)

# first puzzle
print(inc)

n = len(arr)
prev = sum(arr[:3])
inc_ = 0

for i in range(1, n - 2):
    curr = sum(arr[i: i + 3])
    if prev < curr:
        inc_ += 1
    prev = curr

# second puzzle
print(inc_)
