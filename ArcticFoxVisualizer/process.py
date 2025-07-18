import networkx as nx
import matplotlib.pyplot as plt

def parse_log(filename):
    edges = []

    with open(filename, 'r', encoding='utf-16-le') as f:
        for line in f:
            print(line)
            parts = line.strip().split(',')
            if len(parts) != 5:
                continue

            _, parent, child, image, arg = parts
            parent = int(parent)
            child = int(child)

            edges.append((parent, child))
    return edges

def draw_process_tree(edges):
    G = nx.DiGraph()
    G.add_edges_from(edges)

    node_colors = []
    for node in G.nodes():
            node_colors.append('lightgreen')

    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, arrows=True, node_color=node_colors, node_size=800)
    plt.title('ArcticFox Process Graph')
    plt.show()

if __name__ == "__main__":
    edges = parse_log("log.csv")
    draw_process_tree(edges)
