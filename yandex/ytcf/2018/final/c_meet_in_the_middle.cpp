#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long ull;

using namespace std;

int main () {
    int n, m, source, target, i, j, k;
    ull d[22][5][5], D;

    cin >> n >> m;

    for (i = 0; i < n - 1; i ++)
        for (j = 0; j < m; j ++)
            for (k = 0; k < m; k ++)
                cin >> d[i][j][k];

    cin >> source >> target;
    cin >> D;

    vector<ull> dp[n + 1][m];
    dp[0][source].push_back(0);
    dp[n][target].push_back(0);

    int mid = n / 2;

    for (i = 1; i < mid; i ++)
        for (j = 0; j < m; j ++)
            for (k = 0; k < m; k ++)
                for (ull dd : dp[i - 1][j])
                    if (dd + d[i - 1][j][k] <= D)
                        dp[i][k].push_back(dd + d[i - 1][j][k]);

    for (i = n - 1; i >= mid; i --)
        for (j = 0; j < m; j ++)
            for (k = 0; k < m; k ++)
                for (ull dd : dp[i + 1][j])
                    if (dd + d[i - 1][k][j] <= D)
                        dp[i][k].push_back(dd + d[i - 1][k][j]);

    for (i = 0; i < m; i ++) {
        sort(dp[mid][i].begin(), dp[mid][i].end());
        for (ull x : dp[mid - 1][i])
            if (binary_search(dp[mid][i].begin(), dp[mid][i].end(), D - x)) {
                cout << "YES";
                return 0;
            }
    }

    cout << "NO";

    return 0;
}