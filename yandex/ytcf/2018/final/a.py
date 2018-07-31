a = input()
b = input()
c = input()

if len(a) + len(b) != len(c):
    print('NO')
    exit(0)

dp = [0] * (len(b) + 1)
for i in range(len(a) + 1):
    for j in range(len(b) + 1):
        dp[j] = i == 0 and j == 0 or \
                i > 0 and dp[j] and c[i + j - 1] == a[i - 1] or \
                j > 0 and dp[j - 1] and c[i + j - 1] == b[j - 1]

print('YES' if dp[len(b)] else 'NO')
