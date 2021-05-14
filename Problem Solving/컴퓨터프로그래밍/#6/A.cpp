
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
typedef long long lint;

int main()
{
    int N, M, K;
    queue<lint> Q;
    vector<lint> Line;
    scanf("%d %d %d", &N, &M, &K);
    Q.push((lint)N); Q.push((lint)M);
    while(Line.size()<K){
        lint X = Q.front(); Q.pop();
        Line.push_back(X); 
        Q.push((X*N)%MOD);
        Q.push((X*M)%MOD);
    }printf("%lld\n", Line[K-1]);
    return 0;
}
