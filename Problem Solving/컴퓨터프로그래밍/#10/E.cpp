
#include <bits/stdc++.h>
using namespace std;
struct Data{ int val; int ind; int rank; };

bool rankSort(Data& a, Data& b){ return a.val>b.val; }
bool indSort(Data& a, Data& b){ return a.ind<b.ind; }

int main()
{
    vector<Data> Line;
    int N; scanf("%d", &N);
    Line.resize(N);
    for(int i=0; i<N; i++) scanf("%d", &Line[i].val);
    for(int i=0; i<N; i++) Line[i].ind=i;
    
    sort(Line.begin(), Line.end(), rankSort);
    
    Line[0].rank = 1;
    for(int i=1; i<N; i++){
        if(Line[i-1].val == Line[i].val) Line[i].rank=Line[i-1].rank;
        else Line[i].rank=i+1;
    }
    
    sort(Line.begin(), Line.end(), indSort);
    for(int i=0; i<N; i++) printf("%d %d\n", Line[i].val, Line[i].rank);
    return 0;
}
