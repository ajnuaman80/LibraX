// Include our Naive Search declarations.
#include "../../include/algorithms/NaiveSearch.h"

// Include string for text and pattern.
#include <string>

// Use the standard namespace.
using namespace std;


// Search for a pattern inside a text.
bool NaiveSearch::contains(
    const string& text,
    const string& pattern
) {

    // An empty pattern is considered found.
    if (pattern.empty()) {
        return true;
    }

    // If the pattern is longer than the text,
    // it cannot exist inside the text.
    if (pattern.length() > text.length()) {
        return false;
    }


    // Calculate the last possible starting position for the pattern.
    int lastPosition =
        static_cast<int>(text.length() - pattern.length());


    // Try every possible starting position in the text.
    for (int i = 0; i <= lastPosition; i++) {

        // Assume the pattern matches at this position initially.
        bool match = true;


        // Compare pattern characters with text characters.
        for (int j = 0; j < static_cast<int>(pattern.length()); j++) {

            // If the characters do not match, stop this comparison.
            if (text[i + j] != pattern[j]) {

                // Mark this position as a mismatch.
                match = false;

                // Stop checking this alignment.
                break;
            }
        }


        // If all characters matched, the pattern was found.
        if (match) {
            return true;
        }
    }


    // The pattern was not found at any position.
    return false;
}