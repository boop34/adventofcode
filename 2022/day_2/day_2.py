#!/usr/bin/env python3

scores = {'win': 6, 'draw': 3, 'loss': 0}

val = {'X': 1, 'Y': 2, 'Z': 3}
win_cond = {('A', 'X'): 'draw', ('A', 'Y'): 'win', ('A', 'Z'): 'loss',
            ('B', 'X'): 'loss', ('B', 'Y'): 'draw', ('B', 'Z'): 'win',
            ('C', 'X'): 'win', ('C', 'Y'): 'loss', ('C', 'Z'): 'draw'}

r_val = {'X': 'loss', 'Y': 'draw', 'Z': 'win'}
r_win_cond = {('A', 'X'): 'Z', ('A', 'Y'): 'X', ('A', 'Z'): 'Y',
              ('B', 'X'): 'X', ('B', 'Y'): 'Y', ('B', 'Z'): 'Z',
              ('C', 'X'): 'Y', ('C', 'Y'): 'Z', ('C', 'Z'): 'X'}

strategy_list = []
score_1 = 0
score_2 = 0

with open('day_2.in', 'r') as f:
    for line in f.readlines():
        strategy_list.append(tuple(line.strip('\n').split(' ')))

for strategy in strategy_list:
    score_1 += scores[win_cond[strategy]] + val[strategy[1]]
    score_2 += val[r_win_cond[strategy]] + scores[r_val[strategy[1]]]

print(score_1)
print(score_2)
