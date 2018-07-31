#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

struct Key {
    int i, j;
    ull d;

    bool operator==(const Key &other) const {
        return i == other.i && j == other.j && d == other.d;
    }
};

struct KeyHasher {
  size_t operator () (const Key &key) const {
    return hash<int>()(key.i) ^ hash<int>()(key.j) ^ hash<ull>()(key.d);
  }
};

int n, m, source, target;
ull d[22][5][5], D;
ull maxDist[22][5];
unordered_map<Key, bool, KeyHasher> cache;

bool f(const int i, const int j, const ull dd) {
    if (i == 0)
        return j == source && dd == 0;

    if (dd > maxDist[i][j])
        return false;

    Key key = {.i=i, .j=j, .d=dd};

    if (cache.find(key) != cache.end())
        return cache[key];

    for (int k = 0; k < m; k ++)
        if (dd >= d[i - 1][k][j] && f(i - 1, k, dd - d[i - 1][k][j])) {
            cache[key] = true;
            return true;
        }

    cache[key] = false;
    return false;
}


int main () {
    cin >> n >> m;

    for (int i = 0; i < n - 1; i ++)
        for (int j = 0; j < m; j ++)
            for (int k = 0; k < m; k ++)
                cin >> d[i][j][k];

    cin >> source >> target;
    cin >> D;

    for (int i = 1; i < n; i ++)
        for (int j = 0; j < m; j ++)
            for (int k = 0; k < m; k ++)
                maxDist[i][k] = max(maxDist[i][k], maxDist[i - 1][j] + d[i - 1][j][k]);

    cout << (f(n - 1, target, D) ? "YES" : "NO");
    return 0;
}