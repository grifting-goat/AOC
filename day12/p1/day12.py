import copy


fileName = "input.txt"

keyx = [0,1,0,-1]
keyy = [1,0,-1,0]


#check if in bounds
def isValid(i,j,mat):
    return 0 <= i < len(mat) and 0 <= j < len(mat[0])
    
def getAnP(mat, visit, i,j):
    q = []
    sticker = mat[i][j]
    countPer = 0
    countArea = 1
    q.append([i,j])
    visit[i][j] = -1

    #BFS
    while(len(q) > 0):
        token = q.pop()

        for n in range(4):
            newI = token[0] + keyx[n]
            newJ = token[1] + keyy[n]
            if isValid(newI, newJ, mat):
                if visit[newI][newJ] == 0 and mat[newI][newJ] == sticker:
                    q.append([newI,newJ])
                    visit[newI][newJ] = -1
                    countArea += 1
                elif mat[newI][newJ] != sticker:
                    countPer += 1
            else:
                countPer += 1

    return countPer * countArea

def calculateCost(mat, visit, i, j):
    #check if the spot has been visited
    if visit[i][j] == -1:
        return 0
    
    #if not return the cost to fence the attached area
    return getAnP(mat,visit,i,j)

#main

map = []
with open(fileName, 'r') as file:
    for line in file:
        listr = []
        line = line.strip()
        for char in line:
            listr.append(char)
        map.append(listr)

#make zeros
visited = [[0] * len(map[0]) for _ in range(len(map))]

#loop through all the spots
sum = 0
for i in range(len(map)):
    for j in range(len(map[0])):
        sum += calculateCost(map, visited, i, j)


print(sum)