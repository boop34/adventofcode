#!/usr/bin/env python3

supplies = []

with open('day_3.in', 'r') as f:
    for line in f.readlines():
        supplies.append(line.strip())


def common_item_for_two(item_a, item_b):
    for c in item_a:
        if c in item_b:
            return c


def common_item_for_three(item_a, item_b, item_c):
    for c in item_a:
        if c in item_b and c in item_c:
            return c


def get_priority(common):
    priority = 0
    if common.isupper():
        priority = ord(common) - ord('A') + 1 + 26
    else:
        priority = ord(common) - ord('a') + 1

    return priority


total_priority = 0
for item in supplies:
    item_a = item[:len(item) // 2]
    item_b = item[len(item) // 2:]

    common = common_item_for_two(item_a, item_b)
    total_priority += get_priority(common)

print(total_priority)

n = len(supplies)
total_priority = 0

for i in range(0, n, 3):
    common = common_item_for_three(*supplies[i: i + 3])
    total_priority += get_priority(common)

print(total_priority)
