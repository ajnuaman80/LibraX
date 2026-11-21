#ifndef NAIVE_SEARCH_H
#define NAIVE_SEARCH_H

// Include string for text and pattern.
#include <string>

// NaiveSearch class contains our string-matching algorithm.
class NaiveSearch {
public:

    // Search for a pattern inside a text.
    // Return true if the pattern is found.
    static bool contains(
        const std::string& text,
        const std::string& pattern
    );
};

#endif