#!/usr/bin/env python3

'''
  0:      1:      2:      3:      4:
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....


  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg

1 -> 2 segments (unique)
4 -> 4 segments (unique)
7 -> 3 segments (unique)
8 -> 7 segments (unique)

0, 6, 9 -> 6 segments
2, 3, 5 -> 5 segmetns

7 - 1 -> seg_a
4 - 1 -> seg_b&d
8 - 7 - seg_b&d -> seg_e&g

for all 6 length digits (0, 6, 9)
    contains seg_b&d + seg_e&g -> 6
    contains only seg_b&d -> 9
    contains only seg_e&g -> 0

6 - seg_a - seg_b&d - seg_e&g -> seg_f
1 - seg_f -> seg_c
9 - seg_a - 4 -> seg_g
seg_e&g - seg_g -> seg_e
8 - 0 -> seg_d
seg_b&d - seg_d -> seg_b
'''

def first_puzzle(entries):
    cnt = 0

    for pats, outs in entries:
        for out in outs:
            if len(out) in [7, 4, 3, 2]:
                cnt += 1

    return cnt


def second_puzzle(entries):
    sum_ = 0

    for pats, outs in entries:
        sum_ += helper(pats, outs)

    return sum_


def helper(pats, outs):
    sum_ = 0
    digi_dict = {i: '' for i in range(10)}
    seg_dict = {chr(i): '' for i in range(ord('a'), ord('g') + 1)}
    com_dict = {}
    len_6_arr = []

    for pat in pats:
        n = len(pat)
        if n == 2:
            digi_dict[1] = pat
        elif n == 3:
            digi_dict[7] = pat
        elif n == 4:
            digi_dict[4] = pat
        elif n == 7:
            digi_dict[8] = pat
        elif n == 6:
            len_6_arr.append(pat)

    seg_dict['a'] = subtract(digi_dict[7], digi_dict[1])
    com_dict['b&d'] = subtract(digi_dict[4], digi_dict[1])
    tmp = digi_dict[7] + com_dict['b&d']
    com_dict['e&g'] = subtract(digi_dict[8], tmp)

    for pat in len_6_arr:
        segment1 = com_dict['b&d'] + com_dict['e&g']
        segment2 = com_dict['b&d']
        segment3 = com_dict['e&g']

        if contains(pat, segment1):
            digi_dict[6] = pat
        elif contains(pat, segment2):
            digi_dict[9] = pat
        elif contains(pat, segment3):
            digi_dict[0] = pat
    
    tmp = seg_dict['a'] + com_dict['b&d'] + com_dict['e&g']
    seg_dict['f'] = subtract(digi_dict[6], tmp)
    seg_dict['c'] = subtract(digi_dict[1], seg_dict['f'])
    tmp = seg_dict['a'] + digi_dict[4]
    seg_dict['g'] = subtract(digi_dict[9], tmp)
    seg_dict['e'] = subtract(com_dict['e&g'], seg_dict['g'])
    seg_dict['d'] = subtract(digi_dict[8], digi_dict[0])
    seg_dict['b'] = subtract(com_dict['b&d'], seg_dict['d'])

    digi_dict[2] = seg_dict['a'] + seg_dict['c'] + seg_dict['d'] + seg_dict['e'] + seg_dict['g']
    digi_dict[3] = seg_dict['a'] + seg_dict['c'] + seg_dict['d'] + seg_dict['f'] + seg_dict['g']
    digi_dict[5] = seg_dict['a'] + seg_dict['b'] + seg_dict['d'] + seg_dict['f'] + seg_dict['g']

    vals = list(map(lambda s: ''.join(sorted(s)), digi_dict.values()))

    digit = ''
    for out in outs:
        tmp = ''.join(sorted(out))
        digit += str(vals.index(tmp))

    return int(digit)


def subtract(s1, s2):
    ret = ''
    for s in s1:
        if s not in s2:
            ret += s
    return ret


def contains(s1, s2):
    return set(s2) <= set(s1)


if __name__ == '__main__':
    entries = []

    with open('day_8.in', 'r') as f:
        for line in f.readlines():
            a, b = line.strip().split(' | ')
            pats = a.split()
            outs = b.split()

            entries.append([pats, outs])


    print(first_puzzle(entries))
    print(second_puzzle(entries))

