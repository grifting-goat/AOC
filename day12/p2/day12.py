import copy

#this is wrong i have no clue how to do this

fileName = "ex.txt"

keyx = [0,-1,0,1]
keyy = [-1,0,1,0]


#check if in bounds
def isValid(i,j,mat):
    return 0 <= i < len(mat) and 0 <= j < len(mat[0])

def getAnP(mat, visit, i, j):
    q = []
    sticker = mat[i][j]
    distinctSides = set()  # Set to track distinct sides
    countArea = 1  # Area of the region
    q.append((i, j))
    visit[i][j] = -1

    # BFS traversal
    while q:
        token = q.pop(0)

        for n in range(4):  # Explore the 4 possible directions
            newI = token[0] + keyx[n]
            newJ = token[1] + keyy[n]

            if isValid(newI, newJ, mat):
                if visit[newI][newJ] == 0 and mat[newI][newJ] == sticker:
                    # Add to BFS queue and mark as visited
                    q.append((newI, newJ))
                    visit[newI][newJ] = -1
                    countArea += 1
                elif mat[newI][newJ] != sticker:
                    # Add boundary edge between this cell and the adjacent cell
                    distinctSides.add((min(token[0], newI), min(token[1], newJ), n))
            else:
                # Add boundary edge for grid edge
                distinctSides.add((token[0], token[1], n))

    # The cost is the total area multiplied by the number of distinct sides
    return len(distinctSides) * countArea


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