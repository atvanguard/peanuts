import random
import networkx as nx
import matplotlib.pyplot as plt

def erdos_renyi(nodes, edges):
    print nodes, edges
    adj_mat = [[0 for i in range(nodes)] for j in range(nodes)]
    p_link_formation = (2.0 * edges) / (nodes * (nodes-1))
    #print p_link_formation
    edge = 0

    G = nx.Graph()
    G.add_nodes_from([i for i in range(nodes)])

    for i in range(nodes):
        for j in range(i+1, nodes):
            r = random.random()
            #print r
            if r <= p_link_formation:
                adj_mat[i][j] = 1
                adj_mat[j][i] = 1
                G.add_edge(i, j)
                edge += 1

    return G, edge

def erdos_renyi2(nodes, edges):
    adj_mat = [[0 for i in range(nodes)] for j in range(nodes)]
    G = nx.Graph()
    G.add_nodes_from([i for i in range(nodes)])

    for i in range(edges):
        while(True):
            n1 = random.randint(0, nodes-1)
            n2 = random.randint(0, nodes-1)
            if n1 != n2 and not adj_mat[n1][n2]:
                adj_mat[n1][n2] = 1
                adj_mat[n2][n1] = 1
                G.add_edge(n1, n2)
                break
    return G

nodes = input("Enter number of nodes: ")
edges = input("Enter number of edges: ")
#G = erdos_renyi2(nodes, edges)
G, edge = erdos_renyi(nodes, edges)
print edge
nx.draw(G)
#plt.show()
plt.savefig("graph.png")