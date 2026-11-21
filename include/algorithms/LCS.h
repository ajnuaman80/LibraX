#ifndef LCS_H
#define LCS_H

#include <string>

class LCS {
public:
    static int length(const std::string& a, const std::string& b);

    static std::string sequence(
        const std::string& a,
        const std::string& b
    );
};

#endif