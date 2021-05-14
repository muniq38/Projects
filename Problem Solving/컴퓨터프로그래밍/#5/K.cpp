
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int main()
{
    int N, Max=0, Check=1; lint Sum=0; cin >> N;
    vector<int> Line(N+1), Ans; 
    for(int i=1; i<=N; i++) scanf("%d", &Line[i]);
    for(int i=1; i<=N; i++){
        Sum += Line[i]; Max=max(Max,Line[i]);
        if(Max==i && Sum==(lint)i*(i+1)/2) Ans.push_back(i);
    }cout << Ans.size() << endl; 
    for(int i=0; i<Ans.size(); i++){
        cout << Ans[i]-Check+1 << " ";
        for(;Check<=Ans[i]; Check++) cout << Check << " ";
        cout << endl;
    }return 0;
}

