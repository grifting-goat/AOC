#part 2- this is a very slow and greedy algorthim 
#it kinda of feels like it was written by a government
example = "ex.txt"
fileName = "input.txt"

#check the to see if the operations produce the correct value
def preformCalcs(ans, vals, ops):
    value = int(vals[0])
    for n in range(len(ops)):
        if ops[n] == 0: #+
            value += int(vals[n+1])
        elif ops[n] == 1: #*  
            value *= int(vals[n+1])
        else: #append new value to the end of the running total
            value = (value * 10 ** len(vals[n+1])) + int(vals[n+1])

    return ans == value

#im not gonna lie i definatly had to look this up, what in the world is this i dont know python very well
def validOps(n):
    if n == 0:
        return [[]]
    rec = validOps(n - 1)
    return [op + [0] for op in rec] + [op + [1] for op in rec] +  [op + [2] for op in rec]


#main

count = 0
with open(fileName, 'r') as file:
    for line in file:
        #grab data from line
        ans, values = line.split(":")
        ans = int(ans.strip())
        values = values.strip().split()
        nOps = len(values) - 1

        #make a giant list of valid operations
        operations = validOps(nOps)

        #check each of them
        for ops in operations:
            if preformCalcs(ans,values,ops):
                count += ans
                break
#print answer
print(count)
