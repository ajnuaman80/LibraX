#include "../../include/algorithms/Knapsack.h"

#include <vector>
#include <algorithm>

using namespace std;


// Recommend books using 0/1 Knapsack DP.
vector<Document> Knapsack::recommend(
    const vector<Document>& documents,
    int timeLimit
) {

    int n = static_cast<int>(documents.size());

    // dp[i][w] represents the maximum value obtainable
    // using the first i documents within time w.
    vector<vector<int>> dp(
        n + 1,
        vector<int>(timeLimit + 1, 0)
    );

    // Define a simple document value score.
    // This score combines keyword count and citation count.
    vector<int> value(n);

    for (int i = 0; i < n; i++) {
        value[i] =
            static_cast<int>(documents[i].keywords.size())
            + static_cast<int>(documents[i].citations.size());
    }

    // Build the DP table.
    for (int i = 1; i <= n; i++) {

        int weight = documents[i - 1].readingTime;
        int score = value[i - 1];

        for (int w = 0; w <= timeLimit; w++) {

            // Exclude the current document.
            dp[i][w] = dp[i - 1][w];

            // Include it if sufficient time is available.
            if (weight <= w) {

                dp[i][w] = max(
                    dp[i][w],
                    dp[i - 1][w - weight] + score
                );
            }
        }
    }

    // Recover selected documents.
    vector<Document> selected;

    int w = timeLimit;

    for (int i = n; i > 0; i--) {

        // If the value changed, this document was selected.
        if (dp[i][w] != dp[i - 1][w]) {

            selected.push_back(documents[i - 1]);

            w -= documents[i - 1].readingTime;
        }
    }

    return selected;
}