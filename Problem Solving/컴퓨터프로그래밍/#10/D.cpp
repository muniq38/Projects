
#include <bits/stdc++.h>
#define psh push_back
using namespace std;
unordered_map<string, int> Vis;
vector<vector<int>> mv(10);

int main(){
    
    for(int i=1; i<=9; i++){
        if((i-1)%3 != 0) mv[i].psh(i-1);
        if((i-1)%3 != 2) mv[i].psh(i+1);
        if((i-1)/3 != 0) mv[i].psh(i-3);
        if((i-1)/3 != 2) mv[i].psh(i+3);
    }
    
    string Str = "a";
    for(int i=1; i<=9; i++){
        int X; scanf("%d", &X);
        Str.append(1,X+'0');
    }
    
    queue<string> Q;
    Q.push(Str); Vis[Str]=0;
    while(!Q.empty()){
        string T = Q.front(); Q.pop();
        if(Vis[T]>24) break;
        for(int x=1; x<=9; x++) if(T[x]=='0')
        for(auto y : mv[x]){
            string nT = T;
            nT[y] = T[x]; nT[x] = T[y];
            if(Vis.find(nT) == Vis.end()){
                Q.push(nT); Vis[nT]=Vis[T]+1; 
            }
        }
    }
    
    if(Vis.find("a123456780") == Vis.end()){ printf("-1\n"); return 0; }
    printf("%d\n", Vis["a123456780"]);
}