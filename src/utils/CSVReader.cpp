#include "../../include/utils/CSVReader.h"

#include <fstream> //for reading files
#include <sstream> //for string stream operations like ? //process string like streams
#include <stdexcept> //for handling runtime errors
#include <unordered_set> //for detecting duplicate document ID's // stores unique value using hashing

using namespace std;

//Remove unnecessary space from the beginning and the end of the string
static string trim(const string& value) {
    //find the first character that is not blank space
    size_t start = value.find_first_not_of("\t\r\n");  //string_t unsigned integer type commonly used for sizes and indexes

    if(start == string::npos) return ""; //if string contains only whitespace, return empty // strring::npos indicates thta a search didnot find a match

    //find the last character that is not a white space 
    size_t end = value.find_last_not_of("\t\r\n");

    //rr=eturning the string without surrounding whitespace
    return value.substr(start, end - start + 1);
}


//split keywords and citations
vector<string> CSVReader::splitList(const string& value) {
    vector<string> result; // stores the separated items

    stringstream ss(value); // convert the input string into a stream
    
    string item; //temp var for each item

    //Extract characters separated by pipe character 
    while(getline(ss, item, '|')) {
        item = trim(item); // remove unnecessary space

        if(!item.empty()) { //ignoring the empty values
            result.push_back(item); //store the extracted item
        }
    }
    return result; //collection of items
}


//Parse CSV Rows
vector<string> CSVReader::parseCSVLine(const string& line) {
    // store all extracted columns
    vector<string> fields;
    string field; //stores the current column being processed

    bool insideQuotes = false; //tracks whetehr we are inside quotation marks

    //visit every character in csv line
    for(size_t i = 0; i < line.size(); i++) {
        char ch = line[i]; //get the current character

        if(ch == '"') {
            //handle escaped quotation marks("")
            if(insideQuotes &&
                i+1 < line.size() &&
                line[i+1] == '"') {
                    field += '"'; //add one quotation mark
                    i++;// skip the second quottation mark
            } else {
                //Enter or exit quotated text
                insideQuotes = !insideQuotes;
            }
        } else if(ch == ',' && !insideQuotes) { //A comma separatess fields only outside quotes
            //save the completed field
            fields.push_back(field);

            //prepare for next field
            field.clear();
        } else {
            //add the character to current field
            field += ch;
        }
    }
    //Check for unclosed quotation marks
    if(insideQuotes) {
        throw runtime_error("Unclosed quotation in CSV row.");
    }
    fields.push_back(field); //saving the final field
    return fields; //return all columns
}


//Load documents function.. combines in the previously made functions
vector<Document> CSVReader::loadDocuments(const string& filePath) {
    //open the CSV filr
    ifstream file(filePath);

    //checking if the file is opened successfully
    if(!file.is_open()) {
        throw runtime_error("Could not open the file: " + filePath);
    }
    
    //Stores all the loaded document
    vector<Document> documents;

    //Track ID's to prevent duplicates
    unordered_set<int> usedIds;

    string line; //stores each line read from the file

    //Read the header row
    if(!getline(file, line)) {
        throw runtime_error("CSV file is empty..");
    }

    //Parse the header
    vector<string> header = parseCSVLine(line);
    //removing UTF-8 BOM if it exists at the start of the file
    // Remove UTF-8 BOM if it exists at the start of the file.
    if (!header.empty() && header[0].size() >= 3 &&
        static_cast<unsigned char>(header[0][0]) == 0xEF &&
        static_cast<unsigned char>(header[0][1]) == 0xBB &&
        static_cast<unsigned char>(header[0][2]) == 0xBF) {

        header[0].erase(0, 3);
    }

    // Remove surrounding whitespace from every header field.
    for (string& field : header) {
        field = trim(field);
    }

    //Dfining the expected columnn names and order
    const vector<string> expectedHeader = {
        "id", "title", "author", "year", "keywords", 
        "content", "reading_time", "citations"
    };

    //Reject the unexpected CSV structrue
    if(header != expectedHeader) {
        throw runtime_error("Invalid CSV header..");
    }

    int lineNumber = 1; //first line was the header

    //Read each remaining document record
    while(getline(file, line)) {
        lineNumber++; //update the current line lineNumber
        if(trim(line).empty()) continue; //skip empty lines
        
        //Handling error for current records
        try {
            //Split csv rows into column
            vector<string> fields = parseCSVLine(line);

            if(fields.size() != 8) {
                throw runtime_error("Expected 8 columns..");
            }

            //Create a new document object 
            Document doc;

            //Convert the ID from string to integer
            doc.id = stoi(trim(fields[0]));
            doc.title = trim(fields[1]); //store the title
            doc.author = trim(fields[2]);
            doc.year = stoi(trim(fields[3]));
            doc.keywords = splitList(fields[4]); 
            doc.content = trim(fields[5]);
            doc.readingTime = stoi(trim(fields[6]));            
            vector<string> citationStrings = splitList(fields[7]); //spliting citation ids

            //conver every citation id to integer
            for(const string& citation : citationStrings) doc.citations.push_back(stoi(citation));
             
            //validate every essential documnet field
            if(doc.id <= 0 ||
                doc.title.empty() ||
                doc.author.empty() ||
                doc.year <= 0 ||
                doc.readingTime <= 0) {
                    throw runtime_error("Invalid document data..");
                }
            
                //Insert the document id into the hash set
                //If insertion fails, that ID already exists
                if(!usedIds.insert(doc.id).second) {
                    throw runtime_error("Duplicate document ID..");
                }
                //Add the vallidated document to the library
                documents.push_back(doc);
        }
        //Caatch errors from parsing, conversion or validation
        catch(const exception& e) {
            //report the exact CSV line contsianing the error
            throw runtime_error(
                "Error on CSV line " + 
                to_string(lineNumber) + ": " + e.what());
        }
    }
    //Return all successful documents
    return documents;
}