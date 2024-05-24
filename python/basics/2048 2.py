import random
rows = 4
cols = 4
maps = [[0 for _ in range(cols)] for _ in range(rows)]
x1 = random.randint(0, 3)
y1 = random.randint(0, 3)
maps[x1][y1] = 2
x2 = random.randint(0, 3)
y2 = random.randint(0, 3)
while not((x2 == x1) and (y2 == y1)):
    x2 = random.randint(0, 3)
    y2 = random.randint(0, 3)
maps[x2][y2] = 4
while True:
    x = random.randint(0, 3)
    y = random.randint(0, 3)
    while maps[x][y] != 0:
        x = random.randint(0, 3)
        y = random.randint(0, 3)
    maps[x][y] = 2
    i = 0
    while i < 4:
        j = 0
        print("-------------------------")
        print("| ", maps[i][0]," | ", maps[i][1], " | ", maps[i][2], " | ", maps[i][3], " |")
        i = i + 1
    print("-------------------------")
    i = 0
    while i < 4:
        j = 0
        while j < 4:
            if(maps[i][j] == 2048):
                print("恭喜你成功通关！")
                exit
            j = j + 1
        i = i + 1
    i = 0
    flag = 0
    while i < 4:
        j = 0
        while j < 4:
            if(maps[i][j] == 0):
                flag = 1
                break
            if(maps[i][j] != 0):
                if(maps[i - 1][j] == maps[i][j] and i != 0):
                    flag = 1
                    break
                if(maps[i][j - 1] == maps[i][j] and j != 0):
                    flag = 1
                    break
                if(maps[i][j + 1] == maps[i][j] and j != 3):
                    flag = 1
                    break
                if(maps[i + 1][j] == maps[i][j] and i != 3):
                    flag = 1
                    break
            j = j + 1
        i = i + 1
        if(flag == 1):
            break
    if flag == 0:
        print("游戏结束！")
        break
    print("请输入W/A/S/D(分别代表上下左右)，或输入Q结束游戏")
    t = input("")
    
    break
    
