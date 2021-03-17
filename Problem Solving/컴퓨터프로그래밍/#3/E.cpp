
#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> Line;

int Max(int n, int m){
    if(n>=N) return 0;
    if(n==N-1) return m+Line[n];
    if(n==N-2) return m+Line[n]+Line[n+1];
    return m+max({Line[n]+Max(n+2,0), Line[n]+Line[n+1]+Max(n+3,0), Max(n+1,0)});
}

int main(){
   scanf("%d", &N);
   Line.resize(N);
   for(int i=0; i<N; i++) scanf("%d", &Line[i]);
   printf("%d\n", Max(0,0));
   return 0;
}
