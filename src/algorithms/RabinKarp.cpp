// Include the Rabin-Karp header.
#include "../../include/algorithms/RabinKarp.h"

// Include string support.
#include <string>

// Use the standard namespace.
using namespace std;


// Search for a pattern inside a text using Rabin-Karp.
bool RabinKarp::contains(
    const string& text,
    const string& pattern
) {

    // An empty pattern is considered found.
    if (pattern.empty()) {
        return true;
    }

    // If the pattern is longer than the text,
    // it cannot occur inside the text.
    if (pattern.length() > text.length()) {
        return false;
    }


    // d represents the number of possible character values.
    // We use 256 because we are working with character values.
    const int d = 256;


    // q is a prime number used to keep hash values manageable.
    const int q = 101;


    // Store the length of the pattern.
    int m = static_cast<int>(pattern.length());


    // Store the length of the text.
    int n = static_cast<int>(text.length());


    // h represents the highest positional multiplier
    // required for the rolling hash.
    int h = 1;


    // Calculate d^(m-1) % q.
    // This helps remove the outgoing character from the hash.
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }


    // Store the hash value of the pattern.
    int patternHash = 0;


    // Store the hash value of the current text window.
    int textHash = 0;


    // Calculate the initial hash values for:
    // 1. The pattern.
    // 2. The first window of text.
    for (int i = 0; i < m; i++) {

        // Build the pattern hash.
        patternHash = (d * patternHash + pattern[i]) % q;


        // Build the first text-window hash.
        textHash = (d * textHash + text[i]) % q;
    }


    // Slide the pattern across the text.
    for (int i = 0; i <= n - m; i++) {

        // If the hash values match,
        // verify the actual characters.
        if (patternHash == textHash) {

            // Assume the characters match.
            bool match = true;


            // Verify every character in this window.
            for (int j = 0; j < m; j++) {

                // If a character differs,
                // this is a hash collision or non-match.
                if (text[i + j] != pattern[j]) {

                    // The strings are not actually equal.
                    match = false;

                    // Stop checking this window.
                    break;
                }
            }


            // If every character matched,
            // the pattern has been found.
            if (match) {
                return true;
            }
        }


        // Calculate the hash of the next window,
        // if another window exists.
        if (i < n - m) {

            // Remove the contribution of the outgoing character.
            textHash =
                (textHash - text[i] * h) % q;


            // Prevent a negative hash value.
            if (textHash < 0) {
                textHash += q;
            }


            // Add the incoming character
            // and update the rolling hash.
            textHash =
                (d * textHash + text[i + m]) % q;
        }
    }


    // The pattern was not found.
    return false;
}