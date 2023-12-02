constexpr int MAXN=1e5+10;
int a[MAXN],d[4*MAXN],b[4*MAXN];  // tree d, tags b

void build(int s,int t,int p){  // root p, range [s,t]
    if(s==t){
        d[p]=a[s];
        return;
    }
    int m=s+(t-s>>1);
    build(s,m,p*2),build(m+1,t,p*2+1);
    d[p]=d[p*2]+d[p*2+1];
}

int getsum(int s,int t,int p,int l,int r){
    if(l<=s&&t<=r)return d[p];
    int m=s+(t-s>>1),sum=0;
    if(b[p]){
        d[p*2]+=b[p]*(m-s+1),d[p*2+1]+=b[p]*(t-m);
        b[p*2]+=b[p],b[p*2+1]+=b[p];
        b[p]=0;
    }
    if(l<=m)sum+=getsum(l,r,s,m,p*2);
    if(r>m) sum+=getsum(l,r,m+1,t,p*2+1);
    return sum;
}

void update(int s,int t,int p,int l,int r,int c) {  // difference c
    // replace `+=` with `=` to implement modifications
    if(l<=s&&t<=r){
        d[p]+=(t-s+1)*c,b[p]+=c;
        return;
    }
    int m=s+(t-s>>1);
    if(b[p]&&s!=t){
        d[p*2]+=b[p]*(m-s+1),d[p*2+1]+=b[p]*(t-m);
        b[p*2]+=b[p],b[p*2+1]+=b[p];
        b[p]=0;
    }
    if(l<=m)update(l,r,c,s,m,p*2);
    if(r>m) update(l,r,c,m+1,t,p*2+1);
    d[p]=d[p*2]+d[p*2+1];
}
