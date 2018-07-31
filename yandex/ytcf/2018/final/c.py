n = int(input())
m = int(input())
d = [[list(map(int, input().split())) for j in range(m)] for i in range(n - 1)]
source, target = map(int, input().split())
D = int(input())

cache = {}


def f(i, j, dd):
    if i == 0:
        return j == source and dd == 0

    if dd > max_dist[i][j]:
        return False

    key = (i, j, dd)
    if key in cache:
        return cache[key]

    for k in range(m):
        if dd >= d[i - 1][k][j] and f(i - 1, k, dd - d[i - 1][k][j]):
            cache[key] = True
            return True

    cache[key] = False
    return False


max_dist = [[0 for j in range(m)] for i in range(n)]
for i in range(1, n):
    for j in range(m):
        for k in range(m):
            max_dist[i][k] = max(max_dist[i][k],
                                 max_dist[i - 1][j] + d[i - 1][j][k])

print('YES' if f(n - 1, target, D) else 'NO')
