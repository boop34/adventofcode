#!/usr/bin/env python3


def first_puzzle(hs):
    b = (bin(int(hs, 16))[2:]).zfill(len(hs) * 4)
    n = len(b)
    ver_sum = 0
    idx = 0

    while idx < n and '1' in b[idx:]:
        version = int(b[idx: idx + 3], 2)
        ver_sum += version

        idx += 3
        type_id = int(b[idx: idx + 3], 2)
        idx += 3

        if type_id == 4:
            num = ''

            while b[idx] == '1':
                num += b[idx + 1: idx + 5]
                idx += 5
            num += b[idx + 1: idx + 5]
            idx += 5

            num = int(num, 2)
        else:
            len_type_id = int(b[idx], 2)
            idx += 1

            if len_type_id == 1:
                num = int(b[idx: idx + 11], 2)
                idx += 11
            else:
                num = int(b[idx: idx + 15], 2)
                idx += 15

    return ver_sum


if __name__ == '__main__':
    hs = ''
    with open('day_16.in', 'r') as f:
        hs = f.readline().strip()

    # hs = 'C0015000016115A2E0802F182340'
    # hs = '620080001611562C8802118E34'
    # hs = 'A0016C880162017C3686B18A3D4780'
    # hs = '8A004A801A8002F478'
    # hs = '38006F45291200'

    print(first_puzzle(hs))

