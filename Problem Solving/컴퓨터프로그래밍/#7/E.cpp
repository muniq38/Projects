
#include <bits/stdc++.h>
using namespace std;
int tree[150]={}; int N;

void DFS(int X){
    if(X>N) return;
    DFS(2*X); 
    printf("%d ", tree[X]);
    DFS(2*X+1);
}

int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; i++)
    scanf("%d", &tree[i]);
    DFS(1);
    return 0;
}

