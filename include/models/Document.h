#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

struct Document {
    int id;
    std::string title;
    std::string author;
    int year;
    std::vector<std::string> keywords;
    std::string content;
    int readingTime;
    std::vector<int> citations;
};
#endif