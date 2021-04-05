
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, X, I=1; scanf("%d", &N);
    stack<int> St;
    vector<int> Ans; 
    for(int i=0; i<N; i++){
        scanf("%d", &X);
        if(I<=X) for(I; I<=X; I++){ St.push(I); Ans.push_back(1); }
        if(St.empty()){ printf("NO\n"); return 0; }
        if(St.top()==X){ St.pop(); Ans.push_back(0); }
        else{ printf("NO\n"); return 0; }
    }for(int i=0; i<2*N; i++){
        if(Ans[i]) printf("+\n");
        else printf("-\n");
    }return 0;
}
