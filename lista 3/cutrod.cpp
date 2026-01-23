#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>
#include <chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::microseconds;

int cutRodRecur(int i, int prices[]) {
    if (i == 0) return 0;

    int ans = 0;
    for (int j = 1; j <= i; j++)
        ans = max(ans, prices[j - 1] + cutRodRecur(i - j, prices));

    return ans;
}

int cutRodMemo(int i, int prices[], int* memo, int* rods) {

    if (i == 0) return 0;

    if (memo[i - 1] != -1) return memo[i - 1];

    for (int j = 1; j <= i; j++) {
        int newp = prices[j - 1] + cutRodMemo(i - j, prices, memo, rods);
        if (memo[i - 1] < newp) {
            memo[i - 1] = newp;
            rods[i - 1] = j;
        }
    }
    return memo[i - 1];
}
tuple<int, vector<int>> cutRodMemo(int i, int prices[]) {
    int* rods = new int[i];
    int* memo = new int[i];
    memset(memo, -1, sizeof(int) * i);
    cutRodMemo(i, prices, memo, rods);
    vector<int> out;
    out.insert(out.begin(), rods, rods + i);
    int res = memo[i - 1];
    delete[] rods;
    delete[] memo;
    return make_tuple(res, out);
}

tuple<int, vector<int>> cutRodIter(int n, int prices[]) {
    int* r = new int[n + 1]{ 0 };
    vector<int> rods(n, 1);

    for (int i = 1; i <= n; i++) {
        r[i] = prices[0] + r[i - 1];
        for (int j = 2; j <= i; j++)
            if (r[i] < prices[j - 1] + r[i - j]) {
                r[i] = prices[j - 1] + r[i - j];
                rods[i - 1] = j;
            }
    }
    int res = r[n];
    delete[] r;
    return make_tuple(res, rods);
}

void Test() {
    srand(time(NULL));

    int sizes[] = { 5, 10, 15, 20, 35, 50, 75, 150, 350, 700 };
    int testNumber = 25;

    cout << "Size\t\tNaive\t\tMemo\t\tIter\n";

    for (int s = 0; s < sizeof(sizes) / sizeof(sizes[0]); s++)
    {
        double timeN = 0, timeR = 0, timeI = 0;

        int* prices = new int[sizes[s]];
        for (int m = 0; m < testNumber; m++) {
            for (int n = 0; n < sizes[s]; n++)
                prices[n] = rand() % (sizes[s]);

            auto t1 = high_resolution_clock::now();
            if (sizes[s] < 30)
                cutRodRecur(sizes[s], prices);
            auto t2 = high_resolution_clock::now();
            cutRodMemo(sizes[s], prices);
            auto t3 = high_resolution_clock::now();
            cutRodIter(sizes[s], prices);
            auto t4 = high_resolution_clock::now();

            timeN += duration_cast<nanoseconds>(t2 - t1).count() / 1000.0 / testNumber;
            timeR += duration_cast<nanoseconds>(t3 - t2).count() / 1000.0 / testNumber;
            timeI += duration_cast<nanoseconds>(t4 - t3).count() / 1000.0 / testNumber;
        }
        delete[] prices;
        string N = ((sizes[s] < 30) ? to_string(timeN) : "N/A");
        cout << sizes[s] << "\t\t" << N << "\t\t" << timeR << "\t\t" << timeI << endl;
    }
}

int main() {
    /*
    int prices[] = { 1, 5, 8, 9, 10, 17, 17, 20 };

    cout << cutRodRecur(8, prices) << endl;

    {
        auto [len, rods] = cutRodMemo(8, prices);
        cout << len << endl;
        for (int n : rods) cout << n << endl;
    }

    {
        auto [len, rods] = cutRodIter(8, prices);
        cout << len << endl;
        for (int n : rods) cout << n << endl;
    }
    */
    Test();
    getchar();
    return 0;
}