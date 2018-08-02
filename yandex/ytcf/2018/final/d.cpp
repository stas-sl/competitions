#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int w, l, r;
};

int main () {
    int n, k;
    cin >> n >> k;

    vector<Node> nodes = {{}};
    vector<bool> isChild(n + 1, false);

    for (int j = 0; j < n; j ++) {
        int i;
        Node node;
        cin >> i >> node.w >> node.l >> node.r;
        nodes.push_back(node);
        if (node.l > 0)
            isChild[node.l] = true;
        if (node.r > 0)
            isChild[node.r] = true;
    }

    int root;
    for (int i = 1; i <= n; i ++)
        if (!isChild[i]) {
            root = i;
            break;
        }

    queue<int> q;
    vector<int> order;
    q.push(root);

    while(q.size() > 0) {
        int x = q.front();
        q.pop();
        order.push_back(x);
        Node node = nodes[x];
        if (node.l > 0)
            q.push(node.l);
        if (node.r > 0)
            q.push(node.r);
    }

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1000000000));
    for (int i = 0; i <= k; i ++)
        dp[0][i] = 0;

    for (int ii = n - 1; ii >= 0; ii --) {
        int i = order[ii];
        Node& node = nodes[i];
        for (int j = 0; j <= k; j ++) {
            for (int l = 0; l <= j; l ++) {
                dp[i][j] = max(dp[i][j], dp[node.l][l] + dp[node.r][j - l] + node.w);

                if (j > 0)
                    dp[i][j] = max(dp[i][j], 0);
            }
        }
    }

    cout << dp[root][k];

    return 0;
}