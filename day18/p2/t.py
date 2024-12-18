import sys
import networkx as nx
import matplotlib.pyplot as plt
import time
from utils import read_input,execution_time,save_output

n = 71

def plot_graph(G, path = None):
    pos = {node: (node[0], -node[1]) for node in G.nodes()}
    nx.draw(G, pos, with_labels=True, node_size=20, node_color='lightblue', font_size=1, font_weight='bold')

    if path:
        edges = list(zip(path, path[1:]))
        nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='r', width=5)

    plt.show()                    

def print_grid(grid):
    for i in range(n):
        for j in range(n):
            print(grid[(j,i)], end = ' ')
        print()

def build_graph(bytes):
    grid = {(j, i): 0 for i in range(n) for j in range(n)} 

    for b in bytes:
        grid[b] = 1

    G = nx.Graph()

    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    for i in range(n):
        for j in range(n):
            for dx, dy in directions:
                tail = (j + dx, i + dy)
                if (j, i) in grid and tail in grid and grid[(j, i)] == 0 and grid[tail] == 0:
                    G.add_edge((j, i), tail)

    #plot_graph(G)

    return G

def part1():
    data = read_input('input.txt')
    bytes = [tuple(map(int,el.split(','))) for el in data]

    grid = {(j, i): 0 for i in range(n) for j in range(n)} 
    for b in bytes[:1024]:
        grid[b] = 1

    G = nx.Graph()

    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    for i in range(n):
        for j in range(n):
            for dx, dy in directions:
                tail = (j + dx, i + dy)
                if (j, i) in grid and tail in grid and grid[(j, i)] == 0 and grid[tail] == 0:
                    G.add_edge((j, i), tail)


    path = nx.shortest_path(G, (0, 0), (70, 70))
    #print(f'Path: {path}')
    print(f'Length: {len(path) - 1}')

    #plot_graph(G, path)

def part2():
    data = read_input('input.txt')
    bytes = [tuple(map(int,el.split(','))) for el in data]

    for i in range(len(bytes)):
        G = build_graph(bytes[:i])

        if i % 100 == 0:
            print(f'Iter: {i}')

        if not nx.has_path(G, source=(0, 0), target=(70,70)):
            print(bytes[i-1])
            break

if __name__ == "__main__":
    part1_time = execution_time(part1)
    
    stard = time.time()
    part2()
    end = time.time()

    save_output(new_row=[part1_time, end - stard])