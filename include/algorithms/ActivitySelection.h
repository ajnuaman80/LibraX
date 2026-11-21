#ifndef ACTIVITY_SELECTION_H
#define ACTIVITY_SELECTION_H

#include <vector>

struct Activity {
    int start;
    int finish;
    int id;
};

class ActivitySelection {
public:
    static std::vector<Activity> selectActivities(
        std::vector<Activity> activities
    );
};

#endif