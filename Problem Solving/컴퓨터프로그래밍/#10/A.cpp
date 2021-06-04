
#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> Line;
    int N; scanf("%d", &N);
    Line.resize(N);
    for(int i=0; i<N; i++) Line[i]=N-i;
    
    int Ans=1;
    for(int i=1; i<=N; i++) Ans *= i;
    printf("%d\n", Ans);
    
    while(1){
        for(int i=0; i<N; i++) printf("%d", Line[i]); printf("\n");
        if(!prev_permutation(Line.begin(),Line.end())) break;
    }
}
