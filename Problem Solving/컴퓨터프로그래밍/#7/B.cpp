
#include <bits/stdc++.h>
using namespace std;
char tree[100]={}; int N;

void DFS(int X){
    if(X>N) return;
    DFS(2*X); 
    printf("%c ", tree[X]);
    DFS(2*X+1);
}

int main()
{
    scanf("%d", &N);
    scanf("%s", tree+1);
    DFS(1);
    return 0;
}
