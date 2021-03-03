
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, K, T;
    cin >> N >> K;
    vector<int> Vis(100001);
    
    queue<int> Q;
    Q.push(N); Vis[N]=1;
    while(!Q.empty()){
        T=Q.front(); Q.pop();
        if(2*T <= 100000 && !Vis[2*T]){
            Vis[2*T] = Vis[T]+1; Q.push(2*T); 
        }if(T+1 <= 100000 && !Vis[T+1]){
            Vis[T+1] = Vis[T]+1; Q.push(T+1);
        }if(T-1 >= 0 && !Vis[T-1]){
            Vis[T-1] = Vis[T]+1; Q.push(T-1);
        } 
    }
    
    cout << Vis[K]-1 << endl;
    return 0;
}