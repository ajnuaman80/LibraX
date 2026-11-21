#ifndef MST_H
#define MST_H

#include "../models/Document.h"
#include <vector>

struct Edge {
    int u;
    int v;
    double weight;
};

class MST {
public:
    static std::vector<Edge> kruskal(
        int vertexCount,
        std::vector<Edge> edges
    );
};

#endif