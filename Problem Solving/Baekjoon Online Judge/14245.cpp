
#include <bits/stdc++.h>
#define MAX 2000000
using namespace std;
vector<int> Line, Tree(MAX), Lazy(MAX);

int Init(int X, int xl, int xr){
    int xm = (xl+xr)/2;
    if(xl == xr) return Tree[X] = Line[xm]; 
    else return Tree[X] = Init(X*2,xl,xm) ^ Init(X*2+1,xm+1,xr); 
}

void Prop(int X, int xl, int xr){ // lazy 한칸 내리기
    Tree[X] ^= ((xr-xl+1)&1)?Lazy[X]:0;
    if(xl != xr){ Lazy[2*X] ^= Lazy[X]; Lazy[2*X+1] ^= Lazy[X]; }
    Lazy[X] = 0;
}

void Update(int X, int xl, int xr, int L, int R, int Q){
    Prop(X, xl, xr); int xm = (xl+xr)/2;
    if(xl > R || xr < L) return;
    if(L <= xl && xr <= R){ Lazy[X] = Q; Prop(X, xl, xr); return; }
    Update(2*X, xl, xm, L, R, Q); Update(2*X+1, xm+1, xr, L, R, Q);
    Tree[X] = Tree[2*X] ^ Tree[2*X+1];
}

int Xor(int X, int xl, int xr, int Y){
    Prop(X, xl, xr); int xm = (xl+xr)/2;
    if(xl==xr) return Tree[X];
    return (Y<=xm) ? Xor(2*X, xl, xm, Y) : Xor(2*X+1, xm+1, xr, Y);
}

int main()
{
    int N; scanf("%d", &N);
    Line.resize(N+1);
    for(int i=1; i<=N; i++) scanf("%d", &Line[i]);
    Init(1,1,N);
    
    int Q; scanf("%d", &Q);
    for(int i=0; i<Q; i++){
        int X, a, b, c;
        scanf("%d", &X);
        if(X==1){ scanf("%d %d %d", &a, &b, &c); Update(1,1,N,a+1,b+1,c); }
        else{ scanf("%d", &a); printf("%d\n", Xor(1,1,N,a+1)); }
    }
}
