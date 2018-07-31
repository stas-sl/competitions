#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Segment {
    int a, b, m;

    bool operator<(const Segment& other) const {
        if (a == other.a)
            return m < other.m;
        return a < other.a;
    }
};

struct Point {
    int t;
    long long x, y;

    bool operator<(const Point& other) const {
        return t < other.t;
    }

    int isInside(const vector<Point>& poly) {
      int n = poly.size(), windingNumber = 0;
      for (int i = 0; i < n; ++i) {
        if (x == poly[i].x && y == poly[i].y)
            return 0;
        int j = (i + 1) % n;
        if (poly[i].y == y && poly[j].y == y) {
          if (min(poly[i].x, poly[j].x) <= x &&
              x <= max(poly[i].x, poly[j].x))
              return 0;
        } else {
          bool below = poly[i].y < y;
          if (below != (poly[j].y < y)) {
            auto orientation = (x - poly[i].x) * (poly[j].y - poly[i].y)
                             - (y - poly[i].y) * (poly[j].x - poly[i].x);
            if (orientation == 0)
                return 0;
            if (below == (orientation > 0))
                windingNumber += below ? 1 : -1;
          }
        }
      }
      return windingNumber == 0 ? 1 : -1;
    }
};


int main () {
    int n, m, k;

    cin >> n;
    vector<Point> polygon(n);

    for (int i = 0; i < n; i ++)
        cin >> polygon[i].x >> polygon[i].y;

    cin >> m;

    vector<Segment> segments;

    for (int i = 0; i < m; i ++) {
        int t;
        cin >> t;
        vector<Point> points;
        for (int j = 0; j < t; j ++) {
            Point p;
            cin >> p.t >> p.x >> p.y;
            points.push_back(p);
        }

        sort(points.begin(), points.end());

        for (int j = 0, start = -1; j < t; j ++) {
            auto p = points[j];
            if (p.isInside(polygon) <= 0) {
                if (start < 0)
                    start = p.t;
                if (start >= 0 && j == t - 1)
                    segments.push_back({.a=start, .b=100000000, .m=i + 1});
            } else {
                if (start >= 0) {
                    segments.push_back({.a=start, .b=p.t, .m=i + 1});
                    start = -1;
                }
            }
        }
    }

    sort(segments.begin(), segments.end());

    cin >> k;

    unordered_set<int> used;

    for (int i = 0, j = 0; i < k; i ++) {
        int kk, x = -1;
        cin >> kk;

        for (; j < segments.size() && segments[j].a <= kk; j ++) {
            auto s = segments[j];
            if (used.find(s.m) == used.end() && s.b > kk) {
                x = s.m;
                used.insert(s.m);
                j ++;
                break;
            }
        }

        cout << x << ' ';
    }

    return 0;
}