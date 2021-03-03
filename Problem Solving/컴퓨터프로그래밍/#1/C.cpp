
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, a, idx;
    long long Ans=0;
    scanf("%d", &N);
    vector<int> Line(N);
    scanf("%d", &a); 
    Line[0]=a; idx=1;
    for(int i=1; i<N; i++){
        scanf("%d", &a);
        while(idx>0 && Line[idx-1]<=a) idx--;
        Ans += idx;
        Line[idx] = a; idx++;
    }printf("%lld\n", Ans);
    return 0;
}
