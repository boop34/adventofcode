#!/usr/bin/env python3


def first_puzzle(nums, days):
    for j in range(days + 1):
        n = len(nums)
        for i in range(n):
            if nums[i] == 0:
                nums.append(8)
                nums[i] = 6
            else:
                nums[i] -= 1

    return n


def second_puzzle(nums, days):
    '''
    as the number of states are fixed (0,1,2,3,4,5,6,7,8) we can use memoization to keep track of the total
    number fishes currently in a certain stage, so we can process all the fish that share the same state at
    once.
    '''
    memo = {}

    for n in nums:
        memo[n] = memo.get(n, 0) + 1

    for d in range(days):
        tmp = {}
        for n, cnt in memo.items():
            if n == 0:
                tmp[6] = tmp.get(6, 0) + cnt
                tmp[8] = tmp.get(8, 0) + cnt
            else:
                tmp[n - 1] = tmp.get(n - 1, 0) + cnt
        memo = tmp

    return sum(memo.values())


if __name__ == '__main__':
    with open('day_6.in', 'r') as f:
        nums = list(map(int, f.readline().strip().split(',')))

    # first puzzle -> second_puzzle(nums.copy(), days=80)
    print(first_puzzle(nums.copy(), days=80))
    print(second_puzzle(nums.copy(), days=256))
