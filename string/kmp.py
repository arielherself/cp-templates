def kmp(s, t):  # find all occurrences of t in s
    n = len(s)
    m = len(t)
    next = [-1]
    j = -1
    i = 0
    while i < m:
        if j == -1 or t[i] == t[j]:
            i += 1
            j += 1
            if i != m and t[j] == t[i]:
                next.append(next[j])
            else:
                next.append(j)
        else:
            j = next[j]
    res = []
    i = 0
    j = 0
    while i < n and j < m:
        if j == -1 or s[i] == t[j]:
            i += 1
            j += 1
            if j == m:
                res.append(i - j)
                j = next[j]
        else:
            j = next[j]
    return res
