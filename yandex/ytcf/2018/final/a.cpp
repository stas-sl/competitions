#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main () {
    string a, b, c;
    cin >> a >> b >> c;

    if (a.size() + b.size() != c.size()) {
        cout << "NO";
        return 0;
    }

    vector<int> dp(b.size() + 1);

    for (int i = 0; i <= a.size(); i ++)
        for (int j = 0; j <= b.size(); j ++)
            dp[j] = (i == 0 && j == 0) ||
                    (i > 0 && dp[j] && c[i + j - 1] == a[i - 1]) ||
                    (j > 0 && dp[j - 1] && c[i + j - 1] == b[j - 1]);

    cout << (dp[b.size()] ? "YES" : "NO");

    return 0;
}