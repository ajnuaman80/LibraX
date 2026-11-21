#include "../../include/algorithms/MergeSort.h"
#include <string> // for title comparison
#include <vector>
using namespace std;

void MergeSort::sortDocuments(vector<Document>& documents) {

    // Check whether the vector contains documents to sort.
    if (documents.empty()) {
        return;
    }

    // Start Merge Sort from the first to the last index.
    mergeSort(documents, 0, static_cast<int>(documents.size()) - 1);
}


// Recursively divide the array into smaller subarrays.
void MergeSort::mergeSort(
    vector<Document>& documents,
    int left,
    int right
) {

    // Base case: one element (or no elements) is already sorted.
    if (left >= right) {
        return;
    }

    // Calculate the middle index safely.
    int mid = left + (right - left) / 2;

    // Recursively sort the left half.
    mergeSort(documents, left, mid);

    // Recursively sort the right half.
    mergeSort(documents, mid + 1, right);

    // Merge both sorted halves together.
    merge(documents, left, mid, right);
}


// Merge two sorted subarrays into one sorted subarray.
void MergeSort::merge(
    vector<Document>& documents,
    int left,
    int mid,
    int right
) {

    // Calculate the size of the left subarray.
    int leftSize = mid - left + 1;

    // Calculate the size of the right subarray.
    int rightSize = right - mid;

    // Create temporary vector for the left half.
    vector<Document> leftArray(leftSize);

    // Create temporary vector for the right half.
    vector<Document> rightArray(rightSize);

    // Copy the left half into the temporary vector.
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = documents[left + i];
    }

    // Copy the right half into the temporary vector.
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = documents[mid + 1 + i];
    }

    // i tracks the current element in the left temporary array.
    int i = 0;

    // j tracks the current element in the right temporary array.
    int j = 0;

    // k tracks the position in the original documents vector.
    int k = left;

    // Compare elements from both halves while both have elements.
    while (i < leftSize && j < rightSize) {

        // Compare document titles alphabetically.
        if (leftArray[i].title <= rightArray[j].title) {

            // Place the smaller (or equal) title into the original vector.
            documents[k] = leftArray[i];

            // Move to the next element in the left array.
            i++;
        }
        else {

            // Place the smaller title from the right array.
            documents[k] = rightArray[j];

            // Move to the next element in the right array.
            j++;
        }

        // Move to the next position in the original vector.
        k++;
    }

    // Copy any remaining elements from the left array.
    while (i < leftSize) {

        // Place the remaining left element.
        documents[k] = leftArray[i];

        // Advance both positions.
        i++;
        k++;
    }

    // Copy any remaining elements from the right array.
    while (j < rightSize) {

        // Place the remaining right element.
        documents[k] = rightArray[j];

        // Advance both positions.
        j++;
        k++;
    }
}