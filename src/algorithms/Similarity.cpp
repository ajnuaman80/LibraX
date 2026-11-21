#include "../../include/algorithms/Similarity.h"

#include <set>
#include <string>

using namespace std;


// Calculate Jaccard similarity between keyword sets.
double Similarity::jaccardSimilarity(
    const Document& a,
    const Document& b
) {

    // Convert keywords into sets to remove duplicates.
    set<string> setA(a.keywords.begin(), a.keywords.end());
    set<string> setB(b.keywords.begin(), b.keywords.end());

    // Count intersection.
    int intersectionCount = 0;

    for (const string& keyword : setA) {
        if (setB.count(keyword)) {
            intersectionCount++;
        }
    }

    // Count union.
    set<string> unionSet = setA;

    unionSet.insert(setB.begin(), setB.end());

    // Avoid division by zero.
    if (unionSet.empty()) {
        return 0.0;
    }

    // Jaccard = intersection / union.
    return static_cast<double>(intersectionCount)
           / unionSet.size();
}