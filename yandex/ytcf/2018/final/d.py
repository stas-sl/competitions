n, k = map(int, input().split())

nodes = {}
no_parent = set(range(1, n + 1))
for j in range(n):
    i, w, l, r = map(int, input().split())
    if l > 0:
        no_parent.remove(l)
    if r > 0:
        no_parent.remove(r)
    nodes[i] = dict(w=w, l=l, r=r)

root = list(no_parent)[0]
cache = {}


def dp(i, k):
    if i == 0:
        return 0

    if (i, k) in cache:
        return cache[(i, k)]

    n = nodes[i]
    res = max(dp(n['l'], j) + dp(n['r'], k - j) for j in range(k + 1))
    res += nodes[i]['w']

    if k > 0:
        res = max(0, res)

    cache[(i, k)] = res
    return res


print(dp(root, k))
