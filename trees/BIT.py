# @ref https://oi.wiki/ds/fenwick

n=...
c=[0]*(n+1)

lowbit=lambda x: x&-x

def prep(a):
    res=[0]*(n+1)
    s=0
    for i in range(1,n+1):
        s+=a[i]
        res[i]=s
    return res

def init(a):
    pa=prep(a)
    for i in range(1,n+1):
        c[i]=pa[i]-pa[i-lowbit(i)]

def getsum(x):
    ans=0
    while x:
        ans+=c[x]
        x-=lowbit(x)
    return ans

def add(x,k):
    while x<=n:
        c[x]+=k
        x+=lowbit(x)
