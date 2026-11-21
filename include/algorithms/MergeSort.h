#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "../models/Document.h"
#include <vector>

class MergeSort{
    public:
        //sort the library documents alphabetically by title
        static void sortDocuments(std::vector<Document>& documents); //public entry point that we will call from main()
    
    private:
        //Recursively divide and sort the subarray
        static void mergeSort(
            std::vector<Document>& documents,
            int left,
            int right
        );

        //merge two already sorted arrays
        static void merge(
            std::vector<Document>& documents,
            int left,
            int mid,
            int right
        );
};
#endif