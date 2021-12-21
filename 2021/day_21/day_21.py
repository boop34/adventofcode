#!/usr/bin/env python3


def first_puzzle(p1, p2):
    p1_score = 0
    p2_score = 0

    roll = 1
    cnt = 0
    p = True

    while p1_score < 1000 and p2_score < 1000:
        tot_roll, roll = get_tot_roll(roll)
        if p:
            p = False
            p1 = (p1 + tot_roll) % 10
            p1_score += p1 if p1 != 0 else 10
        else:
            p = True
            p2 = (p2 + tot_roll) % 10
            p2_score += p2 if p2 != 0 else 10
        cnt += 1

    return cnt * 3 * min(p1_score, p2_score)


def second_puzzle(p1, p2):
    memo = {}
    return max(dirac_dice_run(p1, p2, 0, 0, memo))


def get_tot_roll(roll):
    if roll == 99:
        return 99 + 100 + 1, 2
    if roll == 100:
        return 100 + 1 + 2, 3

    return 3 * roll + 3, (roll + 3) % 100

# https://github.com/jonathanpaulson/AdventOfCode/blob/master/2021/21.py#L41
def dirac_dice_run(curr, other, curr_score, other_score, memo):
    if curr_score >= 21:
        return (1, 0)
    if other_score >= 21:
        return (0, 1)

    if (curr, other, curr_score, other_score) in memo:
        return memo[(curr, other, curr_score, other_score)]

    uni = (0, 0)
    for first in [1, 2, 3]:
        for second in [1, 2, 3]:
            for third in [1, 2, 3]:
                tot_roll = first + second + third
                new_curr = (curr + tot_roll) % 10
                new_curr = new_curr if new_curr != 0 else 10
                new_curr_score = curr_score + new_curr

                # here we are swapping the order as the games is played by
                # alternative players, so the current player will have the
                # result in the other player section of the recursion call
                # return, that's why names are swapped
                n_other_score, n_curr_score = dirac_dice_run(other,
                                                             new_curr,
                                                             other_score,
                                                             new_curr_score,
                                                             memo)
                uni = (uni[0] + n_curr_score, uni[1] + n_other_score)
    memo[(curr, other, curr_score, other_score)] = uni
    return uni


if __name__ == '__main__':
    # p1 = 4
    # p2 = 8

    p1 = 9
    p2 = 10

    print(first_puzzle(p1, p2))
    print(second_puzzle(p1, p2))

