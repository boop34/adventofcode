#!/usr/bin/env python3

line = ''

with open('day_6.in', 'r') as f:
    line = f.readline().strip()

# line = 'zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw'


def get_marker_idx(str, length):
    flag = False
    for c in range(0, len(line) - length):
        sub = line[c: c + length]
        if len(set([i for i in sub])) == length and not flag:
            flag = True
            return c + length


print(get_marker_idx(line, 4))
print(get_marker_idx(line, 14))
