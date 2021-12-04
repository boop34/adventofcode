#!/usr/bin/env python3

class Board:
    def __init__(self, board, n, id_):
        self.id_ = id_
        self.n = n
        self.board = board
        self.state = [[False for _ in range(5)] for _ in range(5)]

    def get_r_c(self, num):
        for i in range(self.n):
            for j in range(self.n):
                if self.board[i][j] == num:
                    return i, j
        return -1, -1

    def mark(self, num):
        r, c = self.get_r_c(num)
        if r != -1 and c != -1:
            self.state[r][c] = True
    
    def bingo(self):
        for i in range(self.n):
            if all(self.state[i]):
                return True
        for j in range(self.n):
            tmp = []
            for i in range(self.n):
                tmp.append(self.state[i][j])
            if all(tmp):
                return True
        return False

    def get_score(self):
        score = 0

        for i in range(self.n):
            for j in range(self.n):
                if not self.state[i][j]:
                    score += self.board[i][j]
        return score

    def get_id(self):
        return self.id_


def first_puzzle(boards, nums):
    for num in nums:
        for board in boards:
            board.mark(num)

            if board.bingo():
                return board.get_score() * num

def second_puzzle(boards, nums):
    a = 1
    arr = [b.get_id() for b in boards]

    for num in nums:
        for board in boards:
            board.mark(num)

            if board.bingo():
                if board.get_id() in arr:
                    arr.remove(board.get_id())
                if len(arr) == 0:
                    return board.get_score() * num


if __name__ == '__main__':
    boards = []
    n = 1

    with open('day_4.in', 'r') as f:
        nums = list(map(int, str(f.readline().strip()).split(',')))
        board = []
        for line in f.readlines()[1:]:
            if line == '\n':
                boards.append(Board(board, 5, n))
                board = []
                n += 1
                continue

            tmp = list(map(int, str(line.strip()).split()))
            board.append(tmp)
    boards.append(Board(board, 5, n))

    print(first_puzzle(boards, nums))
    print(second_puzzle(boards, nums))

