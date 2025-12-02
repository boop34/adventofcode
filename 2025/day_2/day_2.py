s = 0

with open("day_2.in") as f:
    for line in f.readlines():
        for token in line.strip().split(','):
            start, end = map(lambda x: int(x), token.split('-'))
            for i in range(start, end + 1):
                num_str = str(i)
                num_len = len(num_str)

                first = num_str[:num_len // 2]
                second = num_str[num_len // 2:]

                if first == second:
                    s += i


print(s)

