#!/usr/bin/env python3

calories_list = []

with open('day_1.in', 'r') as f:
    calories = []
    for line in f.readlines():
        if line == '\n':
            calories = []
            calories_list.append(calories)
        else:
            calories.append(int(line))

total_calories = sorted(list(map(lambda l: sum(l), calories_list)))

print(total_calories[-1])
print(sum(total_calories[-1: -4: -1]))
