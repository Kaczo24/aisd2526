#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include<algorithm>
#include <time.h>
#include <chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::microseconds;

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
        if (j == -1 || activities[i].first >= activities[j].second)
            acts.insert(j = i);

    return acts;
}

set<int> activitySelectionRecRev(vector<pair<int, int>> &activities, int k) {
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

set<int> activitySelectionIterRev(vector<pair<int, int>> &activities) {
    set<int> acts;
    int k = activities.size();

    for (int i = activities.size() - 1; i >= 0; i--)
        if (k == activities.size() || activities[k].first >= activities[i].second)
            acts.insert(k = i);

    return acts;
}

set<int> activitySelectionDynamic(int i, int end, vector<pair<int, int>>& activities, vector<map<int, set<int>>>& solution) {
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
set<int> activitySelectionDynamic(vector<pair<int, int>> &activities) {
    vector<map<int, set<int>>> sol(activities.size());
    activitySelectionDynamic(0, 0, activities, sol);
    return sol[0][0];
}

void Test() {
    srand(time(NULL));

    int sizes[] = { 10, 100, 250, 500, 1000 };
    int testNumber = 10;

    cout << "Size\t\tDyna\t\tRec\t\tIter\t\tRecRev\t\tIterRev\n";

    for (int s = 0; s < sizeof(sizes) / sizeof(sizes[0]); s++)
    {
        double timeD = 0, timeR = 0, timeI = 0, Rtime = 0, Itime = 0;

        vector<pair<int, int>> activities(sizes[s]);
        for (int m = 0; m < testNumber; m++) {
            for (int n = 0; n < sizes[s]; n++) {
                int start = rand() % (sizes[s] * 10);
                activities[n] = { start, start + rand() % 40 };
            }
            auto t1 = high_resolution_clock::now();
            if (sizes[s] < 200)
                activitySelectionDynamic(activities);
            auto t2 = high_resolution_clock::now();

            sort(activities.begin(), activities.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });

            auto t3 = high_resolution_clock::now();
            activitySelectionRec(activities);
            auto t4 = high_resolution_clock::now();
            activitySelectionIter(activities);
            auto t5 = high_resolution_clock::now();

            sort(activities.begin(), activities.end(), [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; });

            auto t6 = high_resolution_clock::now();
            activitySelectionRecRev(activities);
            auto t7 = high_resolution_clock::now();
            activitySelectionIterRev(activities);
            auto t8 = high_resolution_clock::now();

            timeD += duration_cast<nanoseconds>(t2 - t1).count() / 1000.0 / testNumber;
            timeR += duration_cast<nanoseconds>(t4 - t3).count() / 1000.0 / testNumber;
            timeI += duration_cast<nanoseconds>(t5 - t4).count() / 1000.0 / testNumber;
            Rtime += duration_cast<nanoseconds>(t7 - t6).count() / 1000.0 / testNumber;
            Itime += duration_cast<nanoseconds>(t8 - t7).count() / 1000.0 / testNumber;
        }
        string D = ((sizes[s] < 200) ? to_string(timeD) : "N/A");
        cout << sizes[s] << "\t\t" << D << "\t\t" << timeR << "\t\t" << timeI << "\t\t" << Rtime << "\t\t" << Itime << endl;
    }
}

int main()
{
    /*
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
    */
    Test();

    return 0;
}