// Include our Binary Search declarations.
#include "../../include/algorithms/BinarySearch.h"

// Include vector for our document collection.
#include <vector>

// Use the standard namespace.
using namespace std;


// Search for a document using its ID.
int BinarySearch::searchByID(
    const vector<Document>& documents,
    int targetID
) {

    // Set the left boundary to the first index.
    int left = 0;

    // Set the right boundary to the last index.
    int right = static_cast<int>(documents.size()) - 1;


    // Continue searching while a valid search range exists.
    while (left <= right) {

        // Calculate the middle index of the current search range.
        int mid = left + (right - left) / 2;

        // Retrieve the ID at the middle position.
        int currentID = documents[mid].id;


        // If the middle document has the target ID, return its index.
        if (currentID == targetID) {
            return mid;
        }


        // If the middle ID is smaller than the target,
        // the target must be in the right half.
        if (currentID < targetID) {

            // Discard the left half and move the left boundary.
            left = mid + 1;
        }

        // If the middle ID is greater than the target,
        // the target must be in the left half.
        else {

            // Discard the right half and move the right boundary.
            right = mid - 1;
        }
    }


    // If the loop finishes, the target ID was not found.
    return -1;
}