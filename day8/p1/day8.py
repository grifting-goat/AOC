#i am going crazy this should not have taken so long
#it seemed simple but is was off by 8. this code is a mess. i am sorry 
#im not commenting this you can see p2 if comments are your thing

fileName = "input.txt"

mat = []

def isValid(grid,x,y):
    return 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] != '#'

def write():
    with open("t.txt", 'w') as file:
        for x in range(len(mat)):
            for y in range(len(mat[0])):
                file.write(mat[x][y])
            file.write('\n')


def createRes(grid,x,y,i,j,check):
    dX = int(x-i)
    dY = int(y-j)

    sums = 0

    if isValid(grid, x + dX, y + dY) and not (x + dX, y + dY) in check:
        check.add((x + dX, y + dY))
        if grid[x + dX][y + dY] == '.':
            grid[x + dX][y + dY] = '#'
        sums += 1
    
    if isValid(grid, i - dX, j - dY) and not (i - dX, j - dY) in check:
        check.add((i - dX, j - dY))
        if grid[i - dX][j - dY] == '.':
            grid[i - dX][j - dY] = '#'
        sums += 1

    return sums

with open(fileName, 'r') as file:
    for line in file:
        line = line.strip()
        mat.append(list(line))

counter = 0
check = set()
for i in range(len(mat)):
    for j in range(len(mat[0])):
        if not mat[i][j] == '#' and not mat[i][j] == '.':
            char = mat[i][j]
            for x in range(i,len(mat)):
                for y in range(len(mat[0])):
                    if mat[x][y] == char and not (j == y and i == x):
                        counter += createRes(mat,x,y,i,j,check)
print(counter)

write()