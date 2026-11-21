#ifndef CSV_READER_H
#define CSV_READER_H

#include "../models/Document.h"
#include <string>
#include <vector>

class CSVReader {
    public: 
        //Load the Document from a csv file
        //Take the file path as input
        //Return all loaded documents as vector
        static std::vector<Document> loadDocuments(   //static? it allows us to call the function without creating an object
            const std::string& filePath  //& passes the string by reference, avoiding unnecessary copy and const prevents the function from modifying the supplied string
        );

    private:
        //Separate one CSV row into individual columns
        static std::vector<std::string> parseCSVLine(
            const std::string& line
        );

        //separate pipe delimited values // eg: AI|ML|Algorithms
        static std::vector<std::string> splitList(
            const std::string& value
        );
};

#endif