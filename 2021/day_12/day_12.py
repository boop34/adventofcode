#!/usr/bin/env python3

from collections import defaultdict


def first_puzzle(neighbour_dict):
    q = [('start', set(['start']))]
    cnt = 0

    while q:
        pos, path = q.pop()

        if pos == 'end':
            cnt += 1
            continue

        for n in neighbour_dict[pos]:
            # checking if the lowercase nodes are already present cause we are only adding lowercase nodes
            if n not in path:
                # we create a new set everytime cause otherwise all the sets share same memory
                new_path = set(path)
                # only add the current node if it's lower case cause we can add them only once
                if n.islower():
                    new_path.add(n)
                q.append((n, new_path))

    return cnt


def second_puzzle(neighbour_dict):
    q = [('start', set(['start']), False)]
    cnt = 0

    while q:
        # flag is for checking if we already found a lowercase node twice
        pos, path, flag = q.pop()
        
        if pos == 'end':
            cnt += 1
            continue
        
        for n in neighbour_dict[pos]:
            new_path = set(path)
            if n not in path:
                if n.islower():
                    new_path.add(n)
                q.append((n, new_path, flag))
            # as we are adding a duplicate path we have to make sure not to add `start` and `end` nodes
            elif not flag and n not in ['start', 'end']:
                q.append((n, new_path, True))

    return cnt


if __name__ == '__main__':
    neighbour_dict = defaultdict(list)

    with open('day_12.in', 'r') as f:
        for line in f.readlines():
            a, b = line.strip().split('-')
            neighbour_dict[a].append(b)
            neighbour_dict[b].append(a)

    print(first_puzzle(neighbour_dict))
    print(second_puzzle(neighbour_dict))

