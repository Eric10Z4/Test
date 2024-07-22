import random

class Game2048:
    def __init__(self):
        self.g = [[0] * 4 for _ in range(4)]
        self.s = 0
        self.add_tile()
        self.add_tile()
    
    def add_tile(self):
        e = [(i, j) for i in range(4) for j in range(4) if self.g[i][j] == 0]
        if e:
            i, j = random.choice(e)
            self.g[i][j] = 2 if random.random() < 0.9 else 4
    def display(self):
        print("\nScore:", self.s)
        print("-" * 25)
        for i in range(4):
            print("|", end="")
            for j in range(4):
                if self.g[i][j] == 0:
                    print(" " * 5, end="")
                else:
                    print(f"{self.g[i][j]:5d}", end="")
                print("|", end="")
            print()
            print("-" * 25)
    
    def move_left(self):
        m = False
        for i in range(4):
            r = [c for c in self.g[i] if c != 0]
            for j in range(len(r) - 1):
                if r[j] == r[j + 1] and r[j] != 0:
                    r[j] *= 2
                    r[j + 1] = 0
                    self.s += r[j]
                    m = True
            r = [c for c in r if c != 0]
            r.extend([0] * (4 - len(r)))
            if self.g[i] != r:
                m = True
            self.g[i] = r
        return m
    
    def move_right(self):
        for i in range(4):
            self.g[i] = self.g[i][::-1]
        m = self.move_left()
        for i in range(4):
            self.g[i] = self.g[i][::-1]
        return m
    
    def move_up(self):
        m = False
        for j in range(4):
            col = [self.g[i][j] for i in range(4)]
            c = [cell for cell in col if cell != 0]
            for i in range(len(c) - 1):
                if c[i] == c[i + 1] and c[i] != 0:
                    c[i] *= 2
                    c[i + 1] = 0
                    self.s += c[i]
                    m = True
            c = [cell for cell in c if cell != 0]
            c.extend([0] * (4 - len(c)))
            for i in range(4):
                if self.g[i][j] != c[i]:
                    m = True
                self.g[i][j] = c[i]
        return m
    
    def move_down(self):
        m = False
        for j in range(4):
            col = [self.g[i][j] for i in range(4)]
            col = col[::-1]
            c = [cell for cell in col if cell != 0]
            for i in range(len(c) - 1):
                if c[i] == c[i + 1] and c[i] != 0:
                    c[i] *= 2
                    c[i + 1] = 0
                    self.s += c[i]
                    m = True
            c = [cell for cell in c if cell != 0]
            c.extend([0] * (4 - len(c)))
            c = c[::-1]
            for i in range(4):
                if self.g[i][j] != c[i]:
                    m = True
                self.g[i][j] = c[i]
        return m
    
    def is_game_over(self):
        for i in range(4):
            for j in range(4):
                if self.g[i][j] == 0:
                    return False
        for i in range(4):
            for j in range(3):
                if self.g[i][j] == self.g[i][j + 1]:
                    return False
        for i in range(3):
            for j in range(4):
                if self.g[i][j] == self.g[i + 1][j]:
                    return False
        return True
    
    def play(self):
        print("Welcome to 2048!")
        print("Use WASD to control (W=Up, A=Left, S=Down, D=Right)")
        print("Press Q to quit")
        
        while True:
            self.display()
            
            if self.is_game_over():
                print("Game Over! Final Score:", self.s)
                break
            
            mv = input("Enter move (W/A/S/D/Q): ").strip().lower()
            
            if mv == 'q':
                print("Quit! Final Score:", self.s)
                break
            
            moved = False
            if mv == 'w':
                moved = self.move_up()
            elif mv == 'a':
                moved = self.move_left()
            elif mv == 's':
                moved = self.move_down()
            elif mv == 'd':
                moved = self.move_right()
            else:
                print("Invalid input! Use W/A/S/D to move, Q to quit")
                continue
            
            if moved:
                self.add_tile()
            else:
                print("Can't move in that direction, try another!")

if __name__ == "__main__":
    game = Game2048()
    game.play()