#ifndef SIMILARITY_H
#define SIMILARITY_H

#include "../models/Document.h"

class Similarity {
public:
    static double jaccardSimilarity(
        const Document& a,
        const Document& b
    );
};

#endif