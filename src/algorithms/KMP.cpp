#include "../../include/algorithms/KMP.h"
#include <string>
#include <vector>

using namespace std;

// Build the Longest Prefix Suffix (LPS) array.
static vector<int> buildLPS(const string& pattern) {

    // LPS[i] stores the longest proper prefix
    // which is also a suffix for pattern[0...i].
    vector<int> lps(pattern.length(), 0);

    // Length of the current matching prefix.
    int len = 0;

    // Start from the second character.
    int i = 1;

    while (i < static_cast<int>(pattern.length())) {

        // If characters match, extend the prefix.
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {

            // If a previous prefix exists, use it.
            if (len != 0) {
                len = lps[len - 1];
            }
            else {

                // No prefix matched.
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}


// Perform KMP pattern matching.
bool KMP::contains(const string& text, const string& pattern) {

    if (pattern.empty()) return true;
    if (pattern.length() > text.length()) return false;

    // Build the LPS array.
    vector<int> lps = buildLPS(pattern);

    // Index for text.
    int i = 0;

    // Index for pattern.
    int j = 0;

    while (i < static_cast<int>(text.length())) {

        // If characters match, move both indexes.
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        // Pattern completely matched.
        if (j == static_cast<int>(pattern.length())) {
            return true;
        }

        // Mismatch occurs.
        else if (i < static_cast<int>(text.length())
                 && text[i] != pattern[j]) {

            // Use LPS to avoid rechecking matched characters.
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    return false;
}