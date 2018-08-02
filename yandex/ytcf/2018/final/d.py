from collections import deque

n, k = map(int, input().split())

nodes = {}
is_child = [False] * (n + 1)
for j in range(n):
    i, w, l, r = map(int, input().split())
    if l > 0:
        is_child[l] = True
    if r > 0:
        is_child[r] = True
    nodes[i] = dict(w=w, l=l, r=r)

root = is_child.index(False, 1)

q = deque()
q.append(root)
order = []

while len(q) > 0:
    x = q.popleft()
    order.append(x)
    node = nodes[x]
    if node['l'] > 0:
        q.append(node['l'])
    if node['r'] > 0:
        q.append(node['r'])

dp = [[-10 ** 18] * (k + 1) for i in range(n + 1)]
dp[0] = [0] * (k + 1)
for i in reversed(order):
    node = nodes[i]
    for j in range(k + 1):
        dp[i][j] = max(dp[node['l']][l] + dp[node['r']][j - l] for l in range(j + 1))
        dp[i][j] += node['w']

        if j > 0:
            dp[i][j] = max(0, dp[i][j])

print(dp[root][k])
