#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include<algorithm>

using namespace std;

set<int> activitySelectionRec(vector<pair<int, int>>& activities, int i) {
    int k = i + 1;
    while(k < activities.size() && (k == -1 || i == activities.size() || activities[k].first < activities[i].second)) 
        k++;
    
    if(k == activities.size())
        return {};
    
    auto o = activitySelectionRec(activities, k);
    o.insert(k);
    return o;
}
set<int> activitySelectionRec(vector<pair<int, int>>& activities) 
    { return activitySelectionRec(activities, -1); }


set<int> activitySelectionIter(vector<pair<int, int>>& activities) {

    set<int> acts;
    int j = -1;    

    for (int i = 0; i < activities.size(); i++)
        if (i != -1 && j != activities.size() && activities[i].first >= activities[j].second)
            acts.insert(j = i);
            
    return acts;
}

set<int> activitySelectionRecRev(vector<pair<int,int>> activities, int k) {
    int i = k - 1;
    while(i >= 0 && (k == -1 || i == activities.size() || activities[k].first < activities[i].second)) 
        i--;
    
    if(i < 0)
        return {};
    
    auto o = activitySelectionRec(activities, i);
    o.insert(k);
    return o;
}
set<int> activitySelectionRecRev(vector<pair<int, int>>& activities) 
    { return activitySelectionRecRev(activities, activities.size()); }

set<int> activitySelectionIterRev(vector<pair<int,int>> activities) {
    set<int> acts;
    int i = activities.size();    

    for (int j = activities.size() - 1; j >= 0; j--)
        if (i != -1 && j != activities.size() && activities[i].first >= activities[j].second)
            acts.insert(i = j);
            
    return acts;
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
        {8, 9}
    };
    
    sort(activities.begin(), activities.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
    
    cout << activitySelectionRec(activities).size() << endl;
    cout << activitySelectionIter(activities).size() << endl;
    
    sort(activities.begin(), activities.end(), [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; });
    
    cout << activitySelectionRecRev(activities).size() << endl;
    cout << activitySelectionIterRev(activities).size() << endl;
    
    
    
    return 0;
}