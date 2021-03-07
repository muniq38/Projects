
#include <bits/stdc++.h>
using namespace std;
vector<int> Line;

void LineSwap(int x, int y){
    if(x>y) swap(x,y);
    for(int i=x; i<=(x+y)/2; i++){
        int temp = Line[i];
        Line[i] = Line[x+y-i];
        Line[x+y-i] = temp;
    }
}

int main(){
    int N, A=0, B=0, pA=0, pB=0, i; scanf("%d", &N);
    Line.resize(N+2); Line[N+1]=N+1;
    for(i=1; i<=N; i++) scanf("%d", &Line[i]);
    
    for(i=0; i<=N; i++) if(Line[i]==i && Line[i+1]!=i+1){ A=i+1; break; }
    if(!A){ printf("1 1\n1 1\n"); return 0; }
    
    for(i=1; i<=N; i++) if(Line[i]==A) pA=i;
    LineSwap(A,pA);
    for(i=0; i<=N; i++) if(Line[i]==i && Line[i+1]!=i+1){ B=i+1; break; }
    if(!B){ printf("%d %d\n1 1\n", min(A,pA), max(A,pA)); return 0; }
    for(i=1; i<=N; i++) if(Line[i]==B) pB=i;
    LineSwap(B,pB);
    for(i=1; i<=N; i++){
        if(Line[i]!=i){ LineSwap(B,pB); LineSwap(A,pA); break; }
        if(i==N){ printf("%d %d\n%d %d\n", min(A,pA), max(A,pA), min(B,pB), max(B,pB)); return 0; }
    }
    
    A=0; B=0; pA=0; pB=0;
    for(i=N+1; i>0; i--) if(Line[i]==i && Line[i-1]!=i-1){ A=i-1; break; }
    for(i=1; i<=N; i++) if(Line[i]==A) pA=i;
    LineSwap(A,pA);
    for(i=N+1; i>0; i--) if(Line[i]==i && Line[i-1]!=i-1){ B=i-1; break; }
    for(i=1; i<=N; i++) if(Line[i]==B) pB=i;
    LineSwap(B,pB);
    printf("%d %d\n%d %d\n", min(A,pA), max(A,pA), min(B,pB), max(B,pB));
    return 0; 
}
