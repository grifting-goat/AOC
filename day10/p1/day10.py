#im not gonna lie this one cooked me, luckily chatGTP saw the error in my code and saved the day(i suck at recursion)
#i accidentlay wrote a code that worked for p2 tho so maybe im not bad at coding i just missunderstood the assignment

fileName = "input.txt"

mat = []

counter = 0

#check if in bounds
def isValid(i,j,rows, cols):
    return 0 <= i < rows and 0 <= j < cols

#find a path from a point
def findPath(mat, i,j,rows,cols,lvl=0, visited=None):
    #make sure we dont go in circles
    if visited is None:
        visited = set()
        
    if (i, j) in visited:
        return 0
    
    visited.add((i, j))

    xoff = [1,0,-1,0]
    yoff = [0,1,0,-1]
    
    if (mat[i][j]==9):
        return 1

    count = 0
    for n in range(4):
        k = n
        if isValid(i+xoff[n],j+yoff[k], rows,cols):
            if mat[i+xoff[n]][j+yoff[k]] == lvl+1:
                count += findPath(mat,i+xoff[n],j+yoff[k],rows,cols,lvl+1,visited)

    visited.remove((i, j))
    return count

#main

with open(fileName, 'r') as file:
    for line in file:
        line = line.strip()
        lit = []
        for i in range(len(line)):
            lit.append(int(line[i]))
        mat.append(lit)

#find all the zeros and go from thier
for i in range(len(mat)):
    for j in range(len(mat[i])):
        if mat[i][j] == 0:
            counter += findPath(mat,i,j,len(mat),len(mat[i]),0,set())

print(mat)
print(counter)