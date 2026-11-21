#include "../../include/algorithms/LCS.h"

#include <vector>
#include <algorithm>

using namespace std;


// Calculate the length of the Longest Common Subsequence.
int LCS::length(const string& a, const string& b) {

    int m = static_cast<int>(a.length());
    int n = static_cast<int>(b.length());

    // DP table.
    vector<vector<int>> dp(
        m + 1,
        vector<int>(n + 1, 0)
    );

    // Build the table.
    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (a[i - 1] == b[j - 1]) {

                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {

                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    return dp[m][n];
}


// Reconstruct an actual LCS sequence.
string LCS::sequence(const string& a, const string& b) {

    int m = static_cast<int>(a.length());
    int n = static_cast<int>(b.length());

    vector<vector<int>> dp(
        m + 1,
        vector<int>(n + 1, 0)
    );

    // Build the DP table.
    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    // Backtrack to recover the sequence.
    string result;

    int i = m;
    int j = n;

    while (i > 0 && j > 0) {

        if (a[i - 1] == b[j - 1]) {

            result.push_back(a[i - 1]);

            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {

            i--;
        }
        else {

            j--;
        }
    }

    // Backtracking produces the sequence in reverse.
    reverse(result.begin(), result.end());

    return result;
}