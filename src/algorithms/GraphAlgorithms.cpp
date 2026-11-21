#include "../../include/algorithms/GraphAlgorithms.h"

#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;


// Find a document's index from its ID.
static int findIndex(const vector<Document>& documents, int id) {

    for (int i = 0; i < static_cast<int>(documents.size()); i++) {
        if (documents[i].id == id) {
            return i;
        }
    }

    return -1;
}


// Breadth-First Search using citation relationships.
void GraphAlgorithms::BFS(
    const vector<Document>& documents,
    int startID
) {

    int start = findIndex(documents, startID);

    if (start == -1) {
        cout << "Starting document not found.\n";
        return;
    }

    queue<int> q;
    unordered_set<int> visited;

    q.push(start);
    visited.insert(start);

    cout << "\nBFS traversal:\n";

    while (!q.empty()) {

        int current = q.front();
        q.pop();

        cout << documents[current].title << " (ID "
             << documents[current].id << ")\n";

        // Explore documents cited by the current document.
        for (int citationID : documents[current].citations) {

            int next = findIndex(documents, citationID);

            if (next != -1 && !visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
}


// Depth-First Search using citation relationships.
void GraphAlgorithms::DFS(
    const vector<Document>& documents,
    int startID
) {

    int start = findIndex(documents, startID);

    if (start == -1) {
        cout << "Starting document not found.\n";
        return;
    }

    stack<int> st;
    unordered_set<int> visited;

    st.push(start);

    cout << "\nDFS traversal:\n";

    while (!st.empty()) {

        int current = st.top();
        st.pop();

        if (visited.count(current)) {
            continue;
        }

        visited.insert(current);

        cout << documents[current].title << " (ID "
             << documents[current].id << ")\n";

        // Push connected documents onto the stack.
        for (int citationID : documents[current].citations) {

            int next = findIndex(documents, citationID);

            if (next != -1 && !visited.count(next)) {
                st.push(next);
            }
        }
    }
}