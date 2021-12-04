#/usr/bin/env python3

def first_puzzle(arr):
    n = len(arr[0])

    gamma_rate = ''
    epsilon_rate = ''

    for i in range(n):
        mcb, lcb = common_bits(arr, i)
        gamma_rate += mcb
        epsilon_rate += lcb
        
    return int(gamma_rate, 2) * int(epsilon_rate, 2)


def second_puzzle(arr):
    n = len(arr[0])

    o2_rates = [num for num in arr]
    co2_rates = [num for num in arr]

    for i in range(n):
        if len(o2_rates) > 1:
            mcb, _ = common_bits(o2_rates, i)
            o2_rates = filter_(o2_rates, mcb, i)
        if len(co2_rates) > 1:
            _, lcb = common_bits(co2_rates, i)
            co2_rates = filter_(co2_rates, lcb, i)

    return int(o2_rates[0], 2) * int(co2_rates[0], 2)


def common_bits(arr, idx = 0):
    z = 0   # count of zeros
    o = 0   # count of ones

    for num in arr:
        if num[idx] == '0':
            z += 1
        else:
            o += 1

    if z > o:
        return '0', '1'
    elif z == o:
        return '1', '0'
    
    return '1', '0'


def filter_(arr, pat, n):
    ret = []

    for num in arr:
        if num[n] == pat:
            ret.append(num)

    return ret


if __name__ == '__main__':

    arr = []

    with open('day_3.in', 'r') as f:
        for line in f.readlines():
            arr.append(line.strip())


    print(first_puzzle(arr))
    print(second_puzzle(arr))

