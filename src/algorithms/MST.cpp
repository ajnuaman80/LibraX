#include "../../include/algorithms/MST.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;


// Disjoint Set Union (Union-Find).
class DSU {

private:
    vector<int> parent;
    vector<int> rankValue;

public:

    DSU(int n) : parent(n), rankValue(n, 0) {

        // Initially, each vertex is its own parent.
        iota(parent.begin(), parent.end(), 0);
    }


    // Find the representative of a set.
    int find(int x) {

        // Path compression.
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }


    // Merge two sets.
    bool unite(int a, int b) {

        a = find(a);
        b = find(b);

        // Already connected.
        if (a == b) {
            return false;
        }

        // Union by rank.
        if (rankValue[a] < rankValue[b]) {
            swap(a, b);
        }

        parent[b] = a;

        if (rankValue[a] == rankValue[b]) {
            rankValue[a]++;
        }

        return true;
    }
};


// Kruskal's Minimum Spanning Tree algorithm.
vector<Edge> MST::kruskal(
    int vertexCount,
    vector<Edge> edges
) {

    // Sort edges by weight.
    sort(
        edges.begin(),
        edges.end(),
        [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        }
    );

    DSU dsu(vertexCount);

    vector<Edge> result;

    // Select edges without creating cycles.
    for (const Edge& edge : edges) {

        if (dsu.unite(edge.u, edge.v)) {

            result.push_back(edge);

            // An MST contains V - 1 edges.
            if (static_cast<int>(result.size()) == vertexCount - 1) {
                break;
            }
        }
    }

    return result;
}