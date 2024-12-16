import re
import numpy as np

fileName = "input.txt"

# Read and parse the file
with open(fileName, 'r') as data:
    content = data.read()
    pattern = r"(Button \w+|Prize): X[+=](\d+), Y[+=](\d+)"
    matches = re.findall(pattern, content)

machines = []
machine = []

# make into a list of machines with their configs
for match in matches:
    if match[0] == 'Button A':
        machine.append([int(match[1]), int(match[2])])  
    elif match[0] == 'Button B':
        machine.append([int(match[1]), int(match[2])])  
    elif match[0] == 'Prize':
        machine.append([int(match[1]), int(match[2])])  
        machines.append(machine)
        machine = []  


tokens = 0
listr = []

for machine in machines:
    a = machine[0]  
    b = machine[1]  
    prize = machine[2]  

    mat = np.array([a, b]).transpose()  
    vec = np.array([prize]).transpose()  

    try:
        x = np.linalg.solve(mat, vec)
        num_a = round(x[0][0]) 
        num_b = round(x[1][0])

        #check if the solution is integer1
        if np.allclose(x, np.round(x)):  
            tokens += num_a * 3 + num_b * 1
    except np.linalg.LinAlgError:
        continue

print(tokens)
