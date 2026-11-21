#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include <string>

class RabinKarp {
public:
    static bool contains(
        const std::string& text,
        const std::string& pattern
    );
};

#endif