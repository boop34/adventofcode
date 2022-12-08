#!/usr/bin/env python3

sections = []

with open('day_4.in', 'r') as f:
    for line in f.readlines():
        first, second = map(lambda l: l.strip(), line.split(','))
        id_a1, id_a2 = map(int, first.split('-'))
        id_b1, id_b2 = map(int, second.split('-'))
        sections.append([(id_a1, id_a2), (id_b1, id_b2)])


count = 0
for (a1, a2), (b1, b2) in sections:
    if a1 <= b1 and a2 >= b2:
        count += 1
    elif b1 <= a1 and b2 >= a2:
        count += 1

print(count)

count = 0
for (a1, a2), (b1, b2) in sections:
    if a1 > b1 and a2 > b2 and a1 > b2 and a2 > b1:
        count += 1
    elif a1 < b1 and a2 < b2 and a1 < b2 and a2 < b1:
        count += 1

print(len(sections) - count)
