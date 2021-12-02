#!/usr/bin/env python3


def first_puzzle(f):
    x, y = 0, 0

    for line in f.readlines():
        cmd, val = line.strip()[:-1].strip(), int(line.strip()[-1])
        if cmd == 'forward':
            x += val
        elif cmd == 'down':
            y += val
        else:
            y -= val
    return x * y

def second_puzzle(f):
    x, y, a = 0, 0, 0

    for line in f.readlines():
        cmd, val = line.strip()[:-1].strip(), int(line.strip()[-1])

        if cmd == 'down':
            a += val
        elif cmd == 'up':
            a -= val
        else:
            x += val
            y += a * val

    return x * y

with open('day_2.in', 'r') as f:
    print(first_puzzle(f))

with open('day_2.in', 'r') as f:
    print(second_puzzle(f))

