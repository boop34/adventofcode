#!/usr/bin/env python3


def first_puzzle(template, rules, n):
    pair_counter = {}
    counter = {}

    # initially populate the counter for the original template
    for i in range(len(template) - 1):
        pair_counter[template[i: i+2]] = pair_counter.get(template[i: i+2], 0) + 1

    for _ in range(n):
        # creater a new counter to tack of the pairs created in this step
        tmp_counter = {}
        for pair in pair_counter:
            # each initial pair (A, B) creates 2 new pairs {(A, C) , (C, B)} accourding to rules (A, B -> C)
            # so we can keep track of the all the new pairs created beacuse of the current pair in a counter
            #
            # WE DON'T NEED TO GENERATE THE NEW STRING, WE CAN JUST KEEP TRACK OF THE PAIRS CREATED TO GET
            # THE RESULT
            #
            np1 = pair[0] + rules[pair]
            np2 = rules[pair] + pair[1]

            tmp_counter[np1] = tmp_counter.get(np1, 0) + pair_counter[pair]
            tmp_counter[np2] = tmp_counter.get(np2, 0) + pair_counter[pair]

        pair_counter = tmp_counter

    # as per the question when 2 pairs are created {(A, C), (C, B)}, the last element of the first pair is
    # same as the first element of the second pair, so in the final string it should appear only once
    # that's why we are keeping track of the first element of each pair below, as the the second element will
    # be counted from the next pair
    for pair in pair_counter:
        counter[pair[0]] = counter.get(pair[0], 0) + pair_counter[pair]
    # however the very last element of the template doesn't get counted once as we are ignoring the last
    # element of each pair, that's why we incremented the last element of the template by 1
    # note that last element of the original template will also be the last element of the final template
    counter[template[-1]] += 1

    counter = sorted(counter.items(), key=lambda x: x[1])

    '''
    counter = {}

    for k in range(n):
        new_template = ''
        for i in range(len(template) - 1):
            side = template[i: i+2]
            insert = rules[side]
            new_template += side[0] + insert

        new_template += side[1]
        template = new_template
    
    for c in set(template):
        counter[c] = template.count(c)
    
    counter = sorted(counter.items(), key=lambda x: x[1])
    '''

    return counter[-1][1] - counter[0][1]


def second_puzzle(template, rules, n):
    return first_puzzle(template, rules, n)


if __name__ == '__main__':
    template = ''
    rules = {}

    with open('day_14.in', 'r') as f:
        template = f.readline().strip()

        for line in f.readlines()[1:]:
            a, b = line.strip().split(' -> ')
            rules[a] = b

    print(first_puzzle(template, rules, 10))
    print(second_puzzle(template, rules, 40))

