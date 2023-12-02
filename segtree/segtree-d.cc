constexpr int MAXN=1e5+10;
int n,cnt,root;
int d[MAXN*2],ls[MAXN*2],rs[MAXN*2];

void update(int s,int t,int &p,int x,int c){  // add constant c to #x
    if(!p)p=++cnt;  // create node
    if(s==t){
        d[p]+=c;
        return;
    }
    int m=s+(t-s>>1);
    if(x<=m)update(ls[p],s,m,x,c);
    else    update(rs[p],m+1,t,x,c);
    d[p]=d[ls[p]]+d[rs[p]];
}

int query(int s,int t,int p,int l,int r){  // query range [l,r]
    if(!p)return 0;
    if(l<=s&&t<=r)return d[p];
    int m=s+(t-s>>1),sum=0;
    if(l<=m)sum+=query(ls[p],s,m,l,r);
    if(r>m) sum+=query(rs[p],m+1,t,l,r);
    return sum;
}
