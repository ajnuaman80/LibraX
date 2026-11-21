#include "../../include/algorithms/ActivitySelection.h"

#include <algorithm>

using namespace std;


// Select maximum number of non-overlapping activities.
vector<Activity> ActivitySelection::selectActivities(
    vector<Activity> activities
) {

    // Sort activities by finishing time.
    sort(
        activities.begin(),
        activities.end(),
        [](const Activity& a, const Activity& b) {
            return a.finish < b.finish;
        }
    );

    vector<Activity> selected;

    if (activities.empty()) {
        return selected;
    }

    // Select the first activity.
    selected.push_back(activities[0]);

    int lastFinish = activities[0].finish;

    // Select activities that don't overlap.
    for (int i = 1; i < static_cast<int>(activities.size()); i++) {

        if (activities[i].start >= lastFinish) {

            selected.push_back(activities[i]);

            lastFinish = activities[i].finish;
        }
    }

    return selected;
}