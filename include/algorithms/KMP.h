#ifndef KMP_H
#define KMP_H

#include <string>

class KMP {
public:
    static bool contains(const std::string& text, const std::string& pattern);
};

#endif