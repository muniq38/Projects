
#include <bits/stdc++.h>
using namespace std;
int N, width=0, maxDepth;
int Edge[50][50]={};
char Board[50][50];
vector<int> Vis;

void fill(int depth, int X){
    if(Vis[X]) return; Vis[X]=1;
    maxDepth = max(depth, maxDepth);
    
    Board[width][depth*2-1] = X+'a';
    Board[width][depth*2-2] = '-';
    if(depth>1 && Board[width][depth*2-3] == '.'){
        Board[width][depth*2-3] = '+';
        for(int i=width-1; Board[i][depth*2-3] == '.'; i--)
        Board[i][depth*2-3] = '|';
    }
    
    bool leaf = true;
    for(int i=0; i<26; i++) 
    if(Edge[X][i] && !Vis[i]){
        fill(depth+1,i); leaf = false; 
    }if(leaf) width++;
}

int main()
{
    for(int i=0; i<50; i++) for(int j=0; j<50; j++) Board[i][j]='.';
    scanf("%d\n", &N); Vis.resize(N); 
    
    for(int i=0; i<N-1; i++){
        char a, b;
        scanf("%c %c\n", &a, &b);
        Edge[a-'a'][b-'a']=1;
        Edge[b-'a'][a-'a']=1;
    }fill(1,0); // depth 1인 'a'부터 시작
    
    for(int i=0; i<width; i++){
        for(int j=0; j<2*maxDepth; j++) printf("%c", Board[i][j]);
        printf("\n");
    }return 0;
}

