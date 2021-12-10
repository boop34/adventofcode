#!/usr/bin/env python3


def first_puzzle(lines):
    il = ''
    sum_ = 0
    matched_p = {'(': ')', '{': '}', '[': ']', '<': '>'}
    score_d = {')': 3, '}': 1197, ']': 57, '>': 25137}

    for l in lines:
        x = []
        for c in l:
            if c in ['(', '{', '[', '<']:
                x.append(c)
            elif c in [')', '}', ']', '>']:
                xx = x.pop()
                if c != matched_p[xx]:
                    il += c
                    break

    for c in il:
        sum_ += score_d[c]

    return sum_


def second_puzzle(lines):
    scores = []
    matched_p = {'(': ')', '{': '}', '[': ']', '<': '>'}
    score_d = {')': 1, '}': 3, ']': 2, '>': 4}

    for l in lines:
        il = ''
        x = []
        for c in l:
            if c in ['(', '{', '[', '<']:
                x.append(c)
            elif c in [')', '}', ']', '>']:
                xx = x.pop()
                if c != matched_p[xx]:
                    il += c

        if il:
            continue

        score = 0

        for i in x[::-1]:
            score *= 5
            xx = matched_p[i]
            score += score_d[xx]

        scores.append(score)

    scores.sort()

    # as per question the length is always odd
    return scores[len(scores) // 2]



if __name__ == '__main__':
    lines = []
    with open('day_10.in', 'r') as f:
        for line in f.readlines():
            lines.append(line.strip())

    print(first_puzzle(lines))
    print(second_puzzle(lines))

