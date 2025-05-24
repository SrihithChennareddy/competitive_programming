from math import floor, inf, sqrt
import random
import numpy as np
from bots.bot import Bot
from typing import List, Tuple

VIEW_R, SZ = 8, 17
MOVES = [(1, 0), (0, 1), (-1, 0), (0, -1), (1, 1), (-1, 1), (-1, -1), (1, -1)]

EXPLORE = 0
FOLLOW = 1
FIND_TARGET = 2
FOLLOW_FINAL = 3
CHECK_TARGET = 4

PRINT = False
BOARD_BITS = 9
BOARD_SIZE = 2**9
EXTRA_BITS = 32 - 2 * BOARD_BITS - 10

def sign(x: int) -> int:
    if x > 0: return 1
    elif x < 0: return -1
    else: return 0
class SubmissionBot(Bot):
    def __init__(self, index: int, difficulty: int):
        self.index = index
        self.diff = difficulty
        self.turn = 0

        self.max_reachable = -1
        self.best_dist = inf
        self.target = None
        self.mode = FOLLOW
        self.should_print = self.index == 5 and PRINT
        self.should_check_targets = False
        
        if self.diff == 0:
            self.exploration = 200
            self.switches = 1
            self.discovery = 400
            self.threshold = 3
            self.should_check_targets = True
        elif self.diff == 1:
            self.exploration = 200
            self.switches = 1
            self.discovery = 400
            self.threshold = 20
            self.should_check_targets = False
        elif self.diff == 2:
            self.exploration = 200
            self.switches = 1
            self.discovery = 500
            self.threshold = 10

    def check_neighbors(self, to_check: List[Tuple[int,int,int]]) -> float:
        bps, max_reachable, best_dist = [], -1, inf
        for neighbor in to_check:
            m = neighbor[2]
            mh = m // (2**(2*BOARD_BITS)) / (2**EXTRA_BITS)
            if self.should_print: print("got mh: " + str(mh))
            if mh >= max_reachable:
                if mh > max_reachable:
                    bps = []
                    best_dist = inf

                max_reachable = mh
                x, y = neighbor[0], neighbor[1]
                if self.should_print: print("x, y: " + str(x) + ", " + str(y))

                ix, iy = neighbor[2] % (2**BOARD_BITS), neighbor[2] // (2**BOARD_BITS) % (2**BOARD_BITS)
                if self.should_print: print("ix, iy: " + str(ix) + ", " + str(iy))
                pos = np.mod(np.array([x + ix, y + iy]), BOARD_SIZE)
                if self.should_print: print("pos: " + str(pos))

                dist = np.max(np.minimum(pos, BOARD_SIZE - pos))
                if dist < best_dist:
                    best_dist = dist
                    bps = [pos]
                elif dist == best_dist:
                    bps.append(pos)
        
        if max_reachable > self.max_reachable:
            self.max_reachable = max_reachable
            self.best_dist = best_dist
            self.target = random.choice(bps)
        elif max_reachable == self.max_reachable and best_dist < self.best_dist:
            self.best_dist = best_dist
            self.target = random.choice(bps)

    def explore(self, height: np.ndarray, max_idx: np.ndarray, neighbors: List[Tuple[int,int,int]]) -> Tuple[int,int]:
        if self.turn > self.discovery:
            self.mode = FIND_TARGET

        if self.difference > self.threshold and self.diff != 1:
            if self.should_check_targets:
                self.mode = CHECK_TARGET
                return self.find_target(height, True)
            else:
                self.mode = FOLLOW
                return self.follow(height, max_idx)

        if self.exploring_for % (self.exploration // self.switches) == 0:
            self.regen_explore_move()
        x, y = self.explore_move
        i = 0
        while height[x + 8, y + 8] <= self.turn and i < 12:
            self.regen_explore_move()
            x, y = self.explore_move
            i += 1
        self.exploring_for += 1
        if self.exploring_for >= self.exploration:
            self.mode = FOLLOW
        return x, y

    def follow(self, height: np.ndarray, max_idx: np.ndarray, switch_to_explore=True) -> Tuple[int,int,bool]:
        if self.turn > self.discovery:
            self.mode = FIND_TARGET
        
        x, y = max_idx

        if x == 8 and y == 8:
            if switch_to_explore:
                self.mode = EXPLORE
                self.exploring_for = 0
            return 0, 0

        dx, dy = x - 8, y - 8
        found_peak = True
        for x1, y1 in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
            if x1 < 0 or x1 >= SZ or y1 < 0 or y1 >= SZ:
                return sign(dx), sign(dy)
            if height[x1, y1] > height[x, y]:
                found_peak = False
                break
        if found_peak:
            if switch_to_explore:
                self.mode = EXPLORE
                self.exploring_for = 0
            return -sign(dx), -sign(dy)
        else:
            return sign(dx), sign(dy)

    def find_target(self, height: np.ndarray, max_idx: np.ndarray, check=False) -> Tuple[int,int]:
        tx, ty = self.target
        if tx > BOARD_SIZE // 2:
            tx -= BOARD_SIZE
        if ty > BOARD_SIZE // 2:
            ty -= BOARD_SIZE

        sx, sy = sign(tx), sign(ty)
        if sx == 0 and sy == 0:
            if check:
                self.mode = FOLLOW
                return self.follow(height, max_idx)
            else:
                self.mode = FOLLOW_FINAL
                return self.follow(height, max_idx, False)
        
        if height[sx + 8, sy + 8] <= self.turn:
            # find path around the water
            best_score = inf
            best_move = sx, sy
            for x, y in MOVES:
                if height[x + 8, y + 8] > self.turn and abs(sx - x) + abs(sy - y) < best_score:
                    best_score = abs(sx - x) + abs(sy - y)
                    best_move = x, y
                    break
            sx, sy = best_move

        return sx, sy

    def step(self, height: np.ndarray, neighbors: List[Tuple[int,int,int]]) -> Tuple[int,int,int]:
        neighbors = [n for n in neighbors if n[0] != 0 or n[1] != 0]

        max_height = np.max(height)
        idx = np.array(np.unravel_index(np.argmax(height), height.shape))
        index = np.mod(idx - 8, BOARD_SIZE)

        mh_message = index[0] + (2**BOARD_BITS) * index[1] + (2**(2*BOARD_BITS)) * floor(max_height * 2**EXTRA_BITS)

        if self.should_print:
            print("START OF TURN: " + str(self.turn))
            print("max is " + str(max_height))
            print("got index: " + str(index))
            print("got idx: " + str(idx))
            print("val at idx: " + str(height[idx[0], idx[1]]))
            print("current height: " + str(height[8, 8]))
        
        old_max_reachable = self.max_reachable
        self.check_neighbors(neighbors + [(0, 0, mh_message)])
        self.difference = self.max_reachable - old_max_reachable

        if self.should_print:
            print(f"Target: {self.target}, max_reachable: {self.max_reachable}, best_dist: {self.best_dist}")
        
        if self.mode == EXPLORE:
            mx, my = self.explore(height, idx, neighbors)
        elif self.mode == FOLLOW:
            mx, my = self.follow(height, idx)
        elif self.mode == FOLLOW_FINAL:
            mx, my = self.follow(height, idx, False)
        elif self.mode == FIND_TARGET:
            mx, my = self.find_target(height, idx)
        elif self.mode == CHECK_TARGET:
            mx, my = self.find_target(height, idx, True)
        
        if self.should_print: print("move: " + str(mx) + ", " + str(my))
        if self.should_print: print("target before move: " + str(self.target))
        self.target[0] -= mx
        self.target[1] -= my
        self.target = np.mod(self.target, BOARD_SIZE)
        self.best_dist = np.max(np.minimum(self.target, BOARD_SIZE - self.target))
        if self.should_print:
            print("target after move: " + str(self.target))
            print("END OF TURN: " + str(self.turn))
            print()
        actual_message = self.target[0] + (2**BOARD_BITS) * self.target[1] + (2**(2*BOARD_BITS)) * floor(self.max_reachable * 2**EXTRA_BITS)

        self.turn += 1
        return mx, my, actual_message

    def regen_explore_move(self):
        self.explore_move = random.choice(MOVES)
