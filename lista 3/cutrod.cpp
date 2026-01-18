#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int cutRodRecur(int i, int prices[]) {
    if (i==0) return 0;
    
    int ans = 0;
    for (int j=1; j<=i; j++) 
        ans = max(ans, prices[j-1]+cutRodRecur(i-j, prices));
        
    return ans;
}

tuple<int, vector<int>> cutRodMemo(int i, int prices[], vector<int> memo, vector<int> &rods) {
    
    if (i==0) return make_tuple(0, rods);
    
    if (memo[i-1]!=-1) return make_tuple(memo[i-1], rods);
    
    for (int j=1; j<=i; j++) {
        int newp = prices[j-1] + get<0>(cutRodMemo(i-j, prices, memo, rods));
        if(memo[i-1] < newp) {
            memo[i-1] = newp;
            rods[i-1] = j;
        }
    }
    return make_tuple(memo[i-1], rods);
}
tuple<int, vector<int>> cutRodMemo(int i, int prices[]) {
    vector<int> rods(i);
    return cutRodMemo(i, prices, vector<int>(i, -1), rods);
}

tuple<int, vector<int>> cutRodIter(int n, int prices[]) {
    int r[n+1] = {0};
    vector<int> rods(n, 1);
    
    for (int i=1; i<=n; i++) {
        r[i] = prices[0]+r[i-1];
        for (int j=2; j<=i; j++)  
            if(r[i] < prices[j-1]+r[i-j]) {    
                r[i] = prices[j-1]+r[i-j];
                rods[i-1] = j;
            }
    }

    return make_tuple(r[n], rods);
}


int main() {
    int prices[] =  { 1, 5, 8, 9, 10, 17, 17, 20};
    
    cout << cutRodRecur(8, prices) << endl;
    
    {
        auto [len, rods] = cutRodMemo(8, prices);
        cout << len << endl;
        for(int n : rods) cout << n << endl;
    }
    
    {
        auto [len, rods] = cutRodIter(8, prices);
        cout << len << endl;
        for(int n : rods) cout << n << endl;
    }
    return 0;
}