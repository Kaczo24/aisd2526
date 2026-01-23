#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <time.h>
#include <chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::microseconds;

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
int lcsRec(string& s1, string& s2, int m, int n, vector<vector<int>>& memo, vector<vector<int>>& arrows) {

    // Base Case
    if (m == 0 || n == 0)
        return 0;

    // Already exists in the memo table
    if (memo[m][n] != -1)
        return memo[m][n];

    // Match
    if (s1[m - 1] == s2[n - 1]) {
        arrows[m][n] = 3;
        return memo[m][n] = 1 + lcsRec(s1, s2, m - 1, n - 1, memo, arrows);
    }

    // Do not match
    int a = lcsRec(s1, s2, m, n - 1, memo, arrows), b = lcsRec(s1, s2, m - 1, n, memo, arrows);
    if (a > b) {
        arrows[m][n] = 1;
        return memo[m][n] = a;
    }
    arrows[m][n] = 2;
    return memo[m][n] = b;
}
tuple<int, string> lcsRec(string& s1, string& s2) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    vector<vector<int>> arrows(m + 1, vector<int>(n + 1, 0));
    int len = lcsRec(s1, s2, m, n, memo, arrows);

    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        int arr = arrows[i][j];
        if (arr == 3) lcs = s1[i - 1] + lcs;
        if ((arr & 2) == 2) i--;
        if ((arr & 1) == 1) j--;
    }

    return make_tuple(len, lcs);
}

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
tuple<int, string> lcsIter(string& s1, string& s2) {
    int m = s1.size();
    int n = s2.size();

    vector<vector<int>> sizes(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> arrows(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                sizes[i][j] = sizes[i - 1][j - 1] + 1;
                arrows[i][j] = 3;
            }
            else if (sizes[i - 1][j] > sizes[i][j - 1]) {
                sizes[i][j] = sizes[i - 1][j];
                arrows[i][j] = 2;
            }
            else {
                sizes[i][j] = sizes[i][j - 1];
                arrows[i][j] = 1;
            }
        }
    }

    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        int arr = arrows[i][j];
        if (arr == 3) lcs = s1[i - 1] + lcs;
        if ((arr & 2) == 2) i--;
        if ((arr & 1) == 1) j--;
    }

    return make_tuple(sizes[m][n], lcs);
}

void Test() {
    srand(time(NULL));

    int sizes[] = { 10, 50, 100, 250, 400, 750, 1500 };
    int testNumber = 10;

    cout << "Size\t\tMemo\t\tIter\n";

    for (int s = 0; s < sizeof(sizes) / sizeof(sizes[0]); s++)
    {
        double timeR = 0, timeI = 0;

        char* a = new char[sizes[s]], *b = new char[sizes[s]];

        for (int m = 0; m < testNumber; m++) {
            for (int n = 0; n < sizes[s]; n++) {
                a[n] = 65 + (rand() % 2) * 32 + rand() % 26;
                b[n] = 65 + (rand() % 2) * 32 + rand() % 26;
            }
            string A(a), B(b);
            auto t1 = high_resolution_clock::now();
            lcsRec(A, B);
            auto t2 = high_resolution_clock::now();
            lcsIter(A, B);
            auto t3 = high_resolution_clock::now();

            timeR += duration_cast<microseconds>(t2 - t1).count() / 1000.0 / testNumber;
            timeI += duration_cast<microseconds>(t3 - t2).count() / 1000.0 / testNumber;
        }
        
        cout << sizes[s] << "\t\t" << timeR << "\t\t" << timeI << endl;
    }
}

int main() {
    /*
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";

    {
        auto [len, lcs] = lcsIter(s1, s2);
        cout << len << " - " << lcs << endl;
    }

    {
        auto [len, lcs] = lcsRec(s1, s2);
        cout << len << " - " << lcs << endl;
    }
    */
    Test();

    return 0;
}