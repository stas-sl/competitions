#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <limits>

using namespace std;

struct Node {
    int w, l, r;
};

vector<Node> nodes = {{}};
unordered_map<int, int> cache;

int dp(int i, int k) {
    if (i == 0)
        return 0;

    int key = k * 100000 + i;
    if (cache.count(key) > 0)
        return cache[key];

    auto& n = nodes[i];
    int res = numeric_limits<int>::min();

    for (int j = 0; j <= k; j ++)
        res = max(res, dp(n.l, j) + dp(n.r, k - j));

    res += n.w;

    if (k > 0)
        res = max(0, res);

    cache[key] = res;
    return res;
}

int main () {
    int n, k;

    cin >> n >> k;
    unordered_set<int> noParent;
    for (int i = 1; i < n; i ++)
        noParent.insert(i);

    for (int j = 0; j < n; j ++) {
        int i;
        Node node;
        cin >> i >> node.w >> node.l >> node.r;
        nodes.push_back(node);
        if (node.l > 0)
            noParent.erase(node.l);
        if (node.r > 0)
            noParent.erase(node.r);
    }

    int root = *noParent.begin();
    cout << dp(root, k);

    return 0;
}