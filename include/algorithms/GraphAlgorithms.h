#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "../models/Document.h"
#include <vector>

class GraphAlgorithms {
public:
    static void BFS(
        const std::vector<Document>& documents,
        int startID
    );

    static void DFS(
        const std::vector<Document>& documents,
        int startID
    );
};

#endif