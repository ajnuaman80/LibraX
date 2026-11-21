#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

// Include our Document structure.
#include "../models/Document.h"

// Include vector to work with a collection of documents.
#include <vector>

// BinarySearch class contains our search algorithm.
class BinarySearch {
public:

    // Search for a document using its ID.
    // The vector must already be sorted by ID.
    static int searchByID(
        const std::vector<Document>& documents,
        int targetID
    );
};

#endif