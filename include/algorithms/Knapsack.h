#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "../models/Document.h"
#include <vector>

class Knapsack {
public:
    static std::vector<Document> recommend(
        const std::vector<Document>& documents,
        int timeLimit
    );
};

#endif