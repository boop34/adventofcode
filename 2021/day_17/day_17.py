#!/usr/bin/env python3


def first_puzzle(source, target):
    y = target[1][1]

    # as we are looking for maximum height possible so that the the probe lands in the area of the target,
    # we want to make the prpbe land in the last possible `y`. Then from there we can just take sum of n
    # numbers to get the maxmum height possible as it decreases by 1 every step (or increases if looked from
    # reverse direction i.e from target to max height)
    # so after `y` number of steps we want it to reach velocity of 1 and in each step the velocity increases 
    # by 1 so it becomes
    # 1 + 2 + 3 + 4 + ... + y = (y * (y + 1)) // 2
    return (y * (y + 1)) // 2

def second_puzzle(source, target):
    # https://www.reddit.com/r/adventofcode/comments/ri9kdq/comment/how671p/?utm_source=reddit&utm_medium=web2x&context=3
    x1, x2 = target[0][0], target[1][0]
    y1, y2 = target[1][1], target[0][1]
    return sum([sim(x,y, x1, x2, y1, y2) for x in range(1, 1+x2) for y in range(y1, -y1)])


# brute force by recursion
def sim(vx, vy, x1, x2, y1, y2, px=0, py=0):
    if px > x2 or py < y1: return 0
    if px >= x1 and py <= y2: return 1
    # vx > 0 evaluates to a boolean result i.e True(1) or False(0)
    # if vx is positive ( > 0), in every step it'll decrease by 1 so (vx > 0) evalutes to 1 to decrease it
    # if vx is 0 or negative(impossible), it doesn't change so (vx > 0) evaluates to False(0) i.e no change
    return sim(vx-(vx>0), vy-1, x1, x2, y1, y2, px+vx, py+vy)


if __name__ == '__main__':
    # target area: x=20..30, y=-10..-5
    # target = [(20, -5), (30, -10)]

    # target area: x=137..171, y=-98..-73
    target = [(137, -73), (171, -98)]

    print(first_puzzle((0, 0), target))
    print(second_puzzle((0, 0), target))

