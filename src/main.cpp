#include <iostream>
#include <vector>
#include "../include/models/Document.h"
#include "../include/utils/CSVReader.h" // CSV Reader class
#include "../include/algorithms/MergeSort.h"
#include "../include/algorithms/BinarySearch.h"
#include "../include/algorithms/NaiveSearch.h"
#include "../include/algorithms/RabinKarp.h"
#include "../include/algorithms/KMP.h"
#include "../include/algorithms/Similarity.h"
#include "../include/algorithms/GraphAlgorithms.h"
#include "../include/algorithms/Knapsack.h"
#include "../include/algorithms/ActivitySelection.h"
#include "../include/algorithms/LCS.h"
#include "../include/algorithms/MST.h"
#include <limits>
#include <algorithm>

using namespace std;


// Display all documents in the library.
void displayCatalog(const vector<Document>& documents) {

    cout << "\n-----------------LIBRARY CATALOG--------------------\n";

    //Loop throigh each document in the vector
    // doc is a reference to the current document object
    //Const prevents us from modifyuying it inside this loop
    for(const Document& doc : documents) {
        cout << "\nID: " << doc.id;
        cout << "\nTitle: " << doc.title;
        cout << "\nAuthor: " << doc.author;
        cout << "\nYear: " << doc.year;
        cout << "\nReading Time: " << doc.readingTime << " minutes";
        cout <<"\nKeywords: ";
        for(const string& keyword : doc.keywords) cout << keyword << " ";
        cout << "\nCitations: ";
        for(int citation : doc.citations) cout << citation << " ";
        cout << "\n-----------------------------------------------\n";
    }
}


// Search using a selected string matching algorithm.
void textSearch(const vector<Document>& documents, int algorithm) {

    string query;

    cout << "\nEnter search phrase: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, query);

    bool foundDocument = false;

    for(const Document& doc : documents) {

        bool titleMatch = false;
        bool contentMatch = false;

        if(algorithm == 1) {
            titleMatch = NaiveSearch::contains(doc.title, query);
            contentMatch = NaiveSearch::contains(doc.content, query);
        }
        else if(algorithm == 2) {
            titleMatch = RabinKarp::contains(doc.title, query);
            contentMatch = RabinKarp::contains(doc.content, query);
        }
        else if(algorithm == 3) {
            titleMatch = KMP::contains(doc.title, query);
            contentMatch = KMP::contains(doc.content, query);
        }

        if(titleMatch || contentMatch) {

            foundDocument = true;

            cout << "\n-------------------------------\n";
            cout << "MATCH FOUND!\n";
            cout << "ID: " << doc.id << "\n";
            cout << "Title: " << doc.title << "\n";
            cout << "Author: " << doc.author << "\n";

            if(titleMatch) {
                cout << "Matched in title.\n";
            }

            if(contentMatch) {
                cout << "Matched in content.\n";
            }
        }
    }

    if(!foundDocument) {
        cout << "\nNo matching documents found.\n";
    }
}


// Recommend similar documents using Jaccard similarity.
void recommendSimilarDocuments(const vector<Document>& documents) {

    int targetID;

    cout << "\nEnter document ID: ";
    cin >> targetID;

    int targetIndex = -1;

    for(int i = 0; i < static_cast<int>(documents.size()); i++) {
        if(documents[i].id == targetID) {
            targetIndex = i;
            break;
        }
    }

    if(targetIndex == -1) {
        cout << "Document not found.\n";
        return;
    }

    vector<pair<double, int>> scores;

    for(int i = 0; i < static_cast<int>(documents.size()); i++) {

        if(i == targetIndex) {
            continue;
        }

        double score = Similarity::jaccardSimilarity(
            documents[targetIndex],
            documents[i]
        );

        scores.push_back({score, i});
    }

    sort(
        scores.begin(),
        scores.end(),
        [](const pair<double, int>& a, const pair<double, int>& b) {
            return a.first > b.first;
        }
    );

    cout << "\nSimilar documents:\n";

    for(int i = 0; i < static_cast<int>(scores.size()); i++) {

        cout << "\nTitle: " << documents[scores[i].second].title;
        cout << "\nSimilarity: " << scores[i].first;
        cout << "\n";
    }
}


// Recommend documents using a reading-time constraint.
void readingPlan(const vector<Document>& documents) {

    int timeLimit;

    cout << "\nEnter available reading time in minutes: ";
    cin >> timeLimit;

    if(timeLimit < 0) {
        cout << "Reading time cannot be negative.\n";
        return;
    }

    vector<Document> selected =
        Knapsack::recommend(documents, timeLimit);

    cout << "\nRecommended reading plan:\n";

    int totalTime = 0;

    for(const Document& doc : selected) {

        cout << "\nTitle: " << doc.title;
        cout << "\nReading time: " << doc.readingTime << " minutes\n";

        totalTime += doc.readingTime;
    }

    cout << "\nTotal reading time: " << totalTime << " minutes\n";
}


// Explore citation relationships using graph traversal.
void exploreGraph(const vector<Document>& documents) {

    int targetID;
    int choice;

    cout << "\nEnter document ID: ";
    cin >> targetID;

    cout << "\n1. BFS";
    cout << "\n2. DFS";
    cout << "\nChoice: ";

    cin >> choice;

    if(choice == 1) {
        GraphAlgorithms::BFS(documents, targetID);
    }
    else if(choice == 2) {
        GraphAlgorithms::DFS(documents, targetID);
    }
    else {
        cout << "Invalid choice.\n";
    }
}


// Run Activity Selection using sample activities.
void runActivitySelection() {

    vector<Activity> activities = {
        {1, 3, 1},
        {2, 5, 2},
        {4, 7, 3},
        {6, 8, 4},
        {8, 10, 5},
        {9, 11, 6}
    };

    vector<Activity> selected =
        ActivitySelection::selectActivities(activities);

    cout << "\nSelected non-overlapping activities:\n";

    for(const Activity& activity : selected) {

        cout << "Activity " << activity.id
             << ": Start = " << activity.start
             << ", Finish = " << activity.finish << "\n";
    }
}


// Compare two document contents using LCS.
void compareDocuments(const vector<Document>& documents) {

    int id1, id2;

    cout << "\nEnter first document ID: ";
    cin >> id1;

    cout << "Enter second document ID: ";
    cin >> id2;

    int index1 = -1;
    int index2 = -1;

    for(int i = 0; i < static_cast<int>(documents.size()); i++) {

        if(documents[i].id == id1) {
            index1 = i;
        }

        if(documents[i].id == id2) {
            index2 = i;
        }
    }

    if(index1 == -1 || index2 == -1) {
        cout << "One or both documents were not found.\n";
        return;
    }

    string a = documents[index1].content;
    string b = documents[index2].content;

    cout << "\nLCS length: " << LCS::length(a, b) << "\n";

    cout << "LCS sequence: " << LCS::sequence(a, b) << "\n";
}


// Run a demonstration of Kruskal's algorithm.
void runMST() {

    // Vertices are represented by integer indexes.
    int vertices = 6;

    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 4},
        {1, 2, 2},
        {1, 3, 5},
        {2, 3, 8},
        {2, 4, 10},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 3}
    };

    vector<Edge> result = MST::kruskal(vertices, edges);

    cout << "\nMinimum Spanning Tree:\n";

    double totalWeight = 0;

    for(const Edge& edge : result) {

        cout << edge.u << " -- " << edge.v
             << " : " << edge.weight << "\n";

        totalWeight += edge.weight;
    }

    cout << "\nTotal MST weight: " << totalWeight << "\n";
}


int main() {
    //We will use a try block cuz it helps us to handle errors which might occur
    try {
        cout << "====================================================\n";
        cout << "               LibraX DIGITAL LIBRARY               \n";
        cout << "====================================================\n";

        //LoAD documents from the CSV file
        vector<Document> documents = CSVReader::loadDocuments("data/documents.csv"); //returns a vector containing Document objects

        //sort documents aplhabetically
        MergeSort::sortDocuments(documents);

        //Creating a separate copy of the documents for ID based searching
        vector<Document> documentsById = documents;
        //Sort copied documents by ID
        for(int i = 0; i < static_cast<int>(documentsById.size()); i++) {
            for(int j = i + 1; j < static_cast<int>(documentsById.size()); j++) {
                if(documentsById[i].id > documentsById[j].id) {
                    swap(documentsById[i], documentsById[j]);
                }
            }
        }

        cout << "\nDocuments loaded successfully..." << endl;
        cout << "Total documents: " << documents.size() << "\n";

        int choice;

        do {

            cout << "\n====================================================\n";
            cout << "                     LIBRAX MENU                    \n";
            cout << "====================================================\n";

            cout << "1. Search document by ID (Binary Search)\n";
            cout << "2. Search using Naive String Matching\n";
            cout << "3. Search using Rabin-Karp\n";
            cout << "4. Search using KMP\n";
            cout << "5. Display library catalog\n";
            cout << "6. Recommend similar documents (Jaccard)\n";
            cout << "7. Explore citation graph (BFS/DFS)\n";
            cout << "8. Reading planner (0/1 Knapsack)\n";
            cout << "9. Activity Selection demonstration\n";
            cout << "10. Compare documents using LCS\n";
            cout << "11. Minimum Spanning Tree (Kruskal)\n";
            cout << "0. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch(choice) {

                case 1: {

                    //Search document by ID using Binary Search.
                    int targetID;

                    cout << "Enter document ID to search: ";
                    cin >> targetID;

                    int result = BinarySearch::searchByID(
                        documentsById,
                        targetID
                    );

                    if(result != -1) {
                        cout << "\nDocument found!!!\n";
                        cout << "Title: " << documentsById[result].title << "\n";
                        cout << "Author: " << documentsById[result].author << "\n";
                        cout << "ID: " << documentsById[result].id << "\n";
                    } else {
                        cout << "\nDocument not found..\n";
                    }

                    break;
                }

                case 2:
                    textSearch(documents, 1);
                    break;

                case 3:
                    textSearch(documents, 2);
                    break;

                case 4:
                    textSearch(documents, 3);
                    break;

                case 5:
                    displayCatalog(documents);
                    break;

                case 6:
                    recommendSimilarDocuments(documents);
                    break;

                case 7:
                    exploreGraph(documents);
                    break;

                case 8:
                    readingPlan(documents);
                    break;

                case 9:
                    runActivitySelection();
                    break;

                case 10:
                    compareDocuments(documents);
                    break;

                case 11:
                    runMST();
                    break;

                case 0:
                    cout << "\nExiting LibraX. Goodbye!\n";
                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }

        } while(choice != 0);

    }

    //Catch exceptions if error occurs
    catch(const exception& e) {
        cerr << "\nERROR: " << e.what() << "\n"; //dispaly error msg
        return 1; //to indicate that our program failed
    }

    return 0; //successful excecution
}