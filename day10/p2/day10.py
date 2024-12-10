#this took <30sec to mod form p1 after reading p2
fileName = "input.txt"

mat = []

counter = 0

#check if in bounds
def isValid(i,j,rows, cols):
    return 0 <= i < rows and 0 <= j < cols

#find a path from a point
def findPath(mat, i,j,rows,cols,lvl=0):
    xoff = [1,0,-1,0]
    yoff = [0,1,0,-1]
    
    if (mat[i][j]==9):
        return 1

    count = 0
    for n in range(4):
        k = n
        if isValid(i+xoff[n],j+yoff[k], rows,cols):
            if mat[i+xoff[n]][j+yoff[k]] == lvl+1:
                count += findPath(mat,i+xoff[n],j+yoff[k],rows,cols,lvl+1)
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
            counter += findPath(mat,i,j,len(mat),len(mat[i]),0)



print(mat)
print(counter)