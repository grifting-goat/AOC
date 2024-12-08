#this was stupid, i got so close in like 5 minutes then spent 30 debugging 2 stupid errors.
#i dont want to every have to become a software engineer. stay in school

fileName = "input.txt"

mat = []

#check for out of bounds
def isValid(grid,x,y):
    return 0 <= x < len(grid) and 0 <= y < len(grid[0])

#more of a debugging thing
def write():
    with open("t.txt", 'w') as file:
        for x in range(len(mat)):
            for y in range(len(mat[0])):
                file.write(mat[x][y])
            file.write('\n')

#create a resonate frequencey for two towers
def createRes(grid,x,y,i,j,check):

    #vector from a to b = b - a
    xx = int(x-i)
    yy = int(y-j)

    #out of the bounds flags
    f1 = True
    f2 = True

    sums = 0

    n = 0

    #go till both are out of bounds
    while f1 or f2:
        dX = xx * n
        dY = yy * n

        f1 = False
        f2 = False

        if isValid(grid, x + dX, y + dY):
            f1 = True
            if not (x + dX, y + dY) in check and grid[x + dX][y + dY] != '#':
                check.add((x + dX, y + dY))
                if grid[x + dX][y + dY] == '.':
                    grid[x + dX][y + dY] = '#'
                sums += 1
        
        if isValid(grid, i - dX, j - dY):
            f2 = True
            if not (i - dX, j - dY) in check and grid[i - dX][j - dY] != '#':
                check.add((i - dX, j - dY))
                if grid[i - dX][j - dY] == '.':
                    grid[i - dX][j - dY] = '#'
                sums += 1
        n+=1

    return sums

#parse file
with open(fileName, 'r') as file:
    for line in file:
        line = line.strip()
        mat.append(list(line))

counter = 0
check = set() #coords that have already been frequ-ed

#this looks unhealthy #but trust me this is how the pros do it
for i in range(len(mat)):
    for j in range(len(mat[0])):
        if not mat[i][j] == '#' and not mat[i][j] == '.':
            char = mat[i][j]
            for x in range(i,len(mat)):
                for y in range(len(mat[0])):
                    if mat[x][y] == char and not (j == y and i == x):
                        counter += createRes(mat,x,y,i,j,check)
print(counter)


#so you can see what it looks like
write()