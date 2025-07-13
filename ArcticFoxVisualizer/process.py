import networkx as nx
import matplotlib.pyplot as plt

def parse_log(filename):
    edges = []
    deleted = set()

    with open(filename, 'r', encoding='utf-16-le') as f:
        for line in f:
            parts = line.strip().split(',')
            if len(parts) != 4:
                continue

            _, parent, child, action = parts
            parent = int(parent)
            child = int(child)
            action = int(action)

            if action == 1:
                edges.append((parent, child))
            elif action == 0:
                deleted.add(child)
    return edges, deleted

def draw_process_tree(edges, deleted):
    G = nx.DiGraph()
    G.add_edges_from(edges)

    node_colors = []
    for node in G.nodes():
        if node in deleted:
            node_colors.append('lightcoral')
        else:
            node_colors.append('lightgreen')

    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, arrows=True, node_color=node_colors, node_size=800)
    plt.title('ArcticFox Process Graph')
    plt.show()

if __name__ == "__main__":
    edges, deleted = parse_log("log.csv")
    draw_process_tree(edges, deleted)
