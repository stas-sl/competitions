def is_inside(p, poly):
    winding_number = 0
    for i in range(len(poly)):
        if p['x'] == poly[i]['x'] and p['y'] == poly[i]['y']:
            return 0
        j = (i + 1) % n
        if poly[i]['y'] == p['y'] and poly[j]['y'] == p['y']:
            if min(poly[i]['x'], poly[j]['x']) <= p['x'] <= max(poly[i]['x'], poly[j]['x']):
                return 0
        else:
            below = poly[i]['y'] < p['y']
            if below != (poly[j]['y'] < p['y']):
                orientation = (p['x'] - poly[i]['x']) * (poly[j]['y'] - poly[i]['y']) - \
                              (p['y'] - poly[i]['y']) * (poly[j]['x'] - poly[i]['x'])
                if orientation == 0:
                    return 0

                if below == (orientation > 0):
                    winding_number += 1 if below else -1
    return 1 if winding_number == 0 else -1


n = int(input())
polygon = list(map(int, input().split()))
polygon = [dict(x=polygon[2 * i], y=polygon[2 * i + 1]) for i in range(n)]

m = int(input())
segments = []

for i in range(m):
    points = list(map(int, input().split()))
    t = points[0]
    points = [dict(t=points[j * 3 + 1], x=points[j * 3 + 2], y=points[j * 3 + 3])
              for j in range(t)]
    points = sorted(points, key=lambda p: p['t'])

    start = -1
    for j in range(t):
        p = points[j]
        if is_inside(p, polygon) <= 0:
            if start < 0:
                start = p['t']
            if start >= 0 and j == t - 1:
                segments.append(dict(a=start, b=100000000, m=i + 1))
        else:
            if start >= 0:
                segments.append(dict(a=start, b=p['t'], m=i + 1))
                start = -1

segments = sorted(segments, key=lambda s: (s['a'], s['m']))
klist = list(map(int, input().split()))[1:]
used = set()

i = 0
for k in klist:
    x = -1

    while i < len(segments) and segments[i]['a'] <= k:
        s = segments[i]
        i += 1
        if s['m'] not in used and s['b'] > k:
            x = s['m']
            used.add(s['m'])
            break

    print(x, end=' ')
