#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include<algorithm>

using namespace std;

set<int> activitySelectionRec(vector<pair<int, int>>& activities, int i) {
    int k = i + 1;
    while (k < activities.size() && (i != -1 && activities[k].first < activities[i].second))
        k++;

    if (k == activities.size())
        return {};

    auto o = activitySelectionRec(activities, k);
    o.insert(k);
    return o;
}
set<int> activitySelectionRec(vector<pair<int, int>>& activities)
{
    return activitySelectionRec(activities, -1);
}


set<int> activitySelectionIter(vector<pair<int, int>>& activities) {

    set<int> acts;
    int j = -1;

    for (int i = 0; i < activities.size(); i++)
        if (j == -1 ||  activities[i].first >= activities[j].second)
            acts.insert(j = i);

    return acts;
}

set<int> activitySelectionRecRev(vector<pair<int, int>> activities, int k) {
    int i = k - 1;
    while (i >= 0 && (k != activities.size() && activities[k].first < activities[i].second))
        i--;

    if (i < 0)
        return {};

    auto o = activitySelectionRecRev(activities, i);
    o.insert(i);
    return o;
}
set<int> activitySelectionRecRev(vector<pair<int, int>>& activities)
{
    return activitySelectionRecRev(activities, activities.size());
}

set<int> activitySelectionIterRev(vector<pair<int, int>> activities) {
    set<int> acts;
    int k = activities.size();

    for (int i = activities.size() - 1; i >= 0; i--)
        if (k == activities.size() || activities[k].first >= activities[i].second)
            acts.insert(k = i);

    return acts;
}

set<int> activitySelectionDynamic(int i, int end, vector<pair<int, int>> &activities, vector<map<int, set<int>>> &solution) {
    int n = activities.size();
    if (i == n) return {};
    set<int> v1, v2;
    if (solution[i].contains(end)) return solution[i][end];

    v1 = activitySelectionDynamic(i + 1, end, activities, solution);
    if (activities[i].first >= end) {
        v2 = activitySelectionDynamic(i + 1, activities[i].second, activities, solution);
        v2.insert(i);
    }
    return solution[i][end] = v1.size() > v2.size() ? v1 : v2;
}
set<int> activitySelectionDynamic(vector<pair<int, int>> activities) {
    vector<map<int, set<int>>> sol(activities.size());
    activitySelectionDynamic(0, 0, activities, sol);
    return sol[0][0];
}

int main()
{
    vector<pair<int, int>> activities = {
        {1, 2},
        {2, 4},
        {0, 6},
        {5, 7},
        {7, 8},
        {5, 9},
        {8, 9},
        {1, 4},
        {3, 5},
        {0, 6},
        {5, 7},
        {3, 9},
        {5, 9},
        {6, 10},
        {8, 11},
        {8, 12},
        {2, 14},
        {12, 16}
    };

    
    cout << activitySelectionDynamic(activities).size() << endl;

    sort(activities.begin(), activities.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });

    cout << activitySelectionRec(activities).size() << endl;
    cout << activitySelectionIter(activities).size() << endl;

    sort(activities.begin(), activities.end(), [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; });

    cout << activitySelectionRecRev(activities).size() << endl;
    cout << activitySelectionIterRev(activities).size() << endl;


    return 0;
}